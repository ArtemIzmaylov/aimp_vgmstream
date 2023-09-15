#include "aimp_vgmstream.h"
#include "aimp_vgmstream_core.h"
#include <comdef.h>

HRESULT __declspec(dllexport) WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header) 
{
	*Header = new Plugin();
	(*Header)->AddRef();
	return S_OK;
}

// Plugin ------------------------------------------------------------------------------------------------------------------------------------------------------------

HRESULT __stdcall Plugin::Initialize(IAIMPCore* Core)
{
	Core->RegisterExtension(IID_IAIMPServiceAudioDecoders, new DecoderExtension());
	Core->RegisterExtension(IID_IAIMPServiceFileFormats, new FileFormatsExtension(Core));
	return S_OK;
}

HRESULT __stdcall Plugin::Finalize()
{
	return S_OK;
}

// DecoderExtension ------------------------------------------------------------------------------------------------------------------------------------------------------------

HRESULT __stdcall DecoderExtension::CreateDecoder(IAIMPString* filename, DWORD flags, IAIMPErrorInfo* errorInfo, IAIMPAudioDecoder** decoder)
{
	if (decoder == nullptr)
		return E_POINTER;

	FILE* file = _wfopen(const_cast<wchar_t *>(filename->GetData()), L"r");
	if (file == nullptr)
		return E_FAIL;

	_bstr_t ansiFileName(filename->GetData());
	VGMSTREAM* vgmstream = vgmstream_open_file(file, ansiFileName);
	if (vgmstream == nullptr)
	{
		fclose(file); // TODO: проверить, не надо ли это делать декодеру самому?
		return E_FAIL;
	}

	(*decoder) = new Decoder(vgmstream);
	(*decoder)->AddRef();
	return S_OK;
}

// Decoder ------------------------------------------------------------------------------------------------------------------------------------------------------------

Decoder::Decoder(VGMSTREAM* stream)
{
	this->stream = stream;
	this->bytesPerFrame = stream->channels * sizeof(sample);
}

Decoder::~Decoder()
{
	vgmstream_close(stream);
}

BOOL __stdcall Decoder::GetFileInfo(IAIMPFileInfo* FileInfo)
{
	return true;
}

BOOL __stdcall Decoder::GetStreamInfo(int* SampleRate, int* Channels, int* SampleFormat)
{
	*SampleRate = stream->sample_rate;
	*SampleFormat = AIMP_DECODER_SAMPLEFORMAT_16BIT;
	*Channels = stream->channels;
	return true;
}

INT64 __stdcall Decoder::GetAvailableData()
{
	return GetSize() - GetPosition();
}

INT64 __stdcall Decoder::GetSize()
{
	return (INT64)stream->num_samples * bytesPerFrame;
}

INT64 __stdcall Decoder::GetPosition()
{
	return (INT64)stream->current_sample * bytesPerFrame;
}

BOOL __stdcall Decoder::SetPosition(const INT64 Value)
{
	vgmstream_seek(stream, Value / bytesPerFrame);
	return true;
}

int __stdcall Decoder::Read(void* Buffer, int Count)
{
	int max_samples = Count / bytesPerFrame;
	int samples_read = max_samples;
	if (stream->current_sample + max_samples > stream->num_samples)
		samples_read = stream->num_samples - stream->current_sample;
	return vgmstream_read((sample*)Buffer, samples_read, stream) * bytesPerFrame;
}
