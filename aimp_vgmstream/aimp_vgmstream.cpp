#include "aimp_vgmstream.h"
#include "aimp_vgmstream_core.h"
#include <comdef.h>

HRESULT __declspec(dllexport) WINAPI AIMPPluginGetHeader(IAIMPPlugin** Header) 
{
	(*Header) = new Plugin();
	(*Header)->AddRef();
	return S_OK;
}

// Plugin ------------------------------------------------------------------------------------------------------------------------------------------------------------

HRESULT __stdcall Plugin::Initialize(IAIMPCore* Core)
{
	Core->RegisterExtension(IID_IAIMPServiceAudioDecoders, new DecoderExtension(Core));
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

	FILE* file = _wfopen(const_cast<wchar_t *>(filename->GetData()), L"rb");
	if (file == nullptr)
		return E_FAIL;

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	_bstr_t ansiFileName(filename->GetData());
	VGMSTREAM* vgmstream = vgmstream_open_file(file, ansiFileName);
	if (vgmstream == nullptr)
	{
		fclose(file); 
		return E_FAIL;
	}
	if (vgmstream->num_samples == 0 || vgmstream->sample_rate == 0)
	{
		vgmstream_close(vgmstream);
		return E_FAIL;
	}

	(*decoder) = new Decoder(core, vgmstream, fileSize);
	(*decoder)->AddRef();
	return S_OK;
}

// Decoder ------------------------------------------------------------------------------------------------------------------------------------------------------------

Decoder::Decoder(IAIMPCore* core, VGMSTREAM* stream, INT64 fileSize)
	: CoreBasedObj(core)
{
	this->stream = stream;
	this->bytesPerFrame = stream->channels * sizeof(sample_t);
	this->fileSize = fileSize;
}

Decoder::~Decoder()
{
	vgmstream_close(stream);
}

BOOL __stdcall Decoder::GetFileInfo(IAIMPFileInfo* info)
{
	double duration = (double)stream->num_samples / (double)stream->sample_rate;
	double bitrate = vgmstream_get_average_bitrate(stream);
	info->SetValueAsInt32(AIMP_FILEINFO_PROPID_BITDEPTH, 16);
	info->SetValueAsInt32(AIMP_FILEINFO_PROPID_BITRATE, (int)(bitrate / 1000.0));
	info->SetValueAsInt32(AIMP_FILEINFO_PROPID_CHANNELS, stream->channels);
	info->SetValueAsInt32(AIMP_FILEINFO_PROPID_SAMPLERATE, stream->sample_rate);
	info->SetValueAsInt64(AIMP_FILEINFO_PROPID_FILESIZE, fileSize);
	info->SetValueAsFloat(AIMP_FILEINFO_PROPID_DURATION, duration);

	char buffer[128];
	vgmstream_get_coding_description(stream, buffer, sizeof(buffer));
	_bstr_t buffer_str(buffer);
	IAIMPString* codec = makeString(buffer_str);
	info->SetValueAsObject(AIMP_FILEINFO_PROPID_CODEC, codec);
	if (codec != nullptr) codec->Release();

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
	return vgmstream_read((sample_t*)Buffer, samples_read, stream) * bytesPerFrame;
}
