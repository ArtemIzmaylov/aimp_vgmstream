#pragma once
#include <apiDecoders.h>
#include <apiPlugin.h>
#include <vgmstream.h>
#include "IUnknownInterfaceImpl.h"

static const wchar_t Name[] = L"VGMStream for AIMP";
static const wchar_t Author[] = L"Artem Izmaylov";
static const wchar_t ShortDesc[] = L"Provides ability to play video game music";

class Decoder : public IUnknownInterfaceImpl<IAIMPAudioDecoder> 
{
private:

    int bytesPerFrame;
    VGMSTREAM* stream;

public:

    Decoder(VGMSTREAM* stream);
    ~Decoder();

    virtual BOOL WINAPI GetFileInfo(IAIMPFileInfo* FileInfo);
    virtual BOOL WINAPI GetStreamInfo(int* SampleRate, int* Channels, int* SampleFormat);

    virtual BOOL WINAPI IsSeekable()
    {
        return true;
    };

    virtual BOOL WINAPI IsRealTimeStream() 
    {
        return false;
    };

    virtual INT64 WINAPI GetAvailableData();
    virtual INT64 WINAPI GetSize();
    virtual INT64 WINAPI GetPosition();
    virtual BOOL WINAPI SetPosition(const INT64 Value);

    virtual int WINAPI Read(void* Buffer, int Count);

    virtual BOOL isOurRIID(REFIID riid)
    {
        return riid == IID_IAIMPAudioDecoder;
    }
};

class DecoderExtension : public IUnknownInterfaceImpl<IAIMPExtensionAudioDecoderOld>
{
    virtual HRESULT WINAPI CreateDecoder(IAIMPString* filename, DWORD flags,
        IAIMPErrorInfo* errorInfo, IAIMPAudioDecoder** decoder);

    virtual BOOL isOurRIID(REFIID riid)
    {
        return riid == IID_IAIMPExtensionAudioDecoderOld;
    }
};

class FileFormatsExtension : public IUnknownInterfaceImpl<IAIMPExtensionFileFormat> 
{
private:

    IAIMPCore* fCore;

public:

    FileFormatsExtension(IAIMPCore* core) 
    {
        fCore = core;
    }

    virtual HRESULT WINAPI GetDescription(IAIMPString** S) 
    {
        *S = makeString(L"VGMStream file formats");
        return S_OK;
    };

    virtual HRESULT WINAPI GetExtList(IAIMPString** S)
    {
        *S = makeString(L"*.aifc;");
        return S_OK;
    };
    
    virtual HRESULT WINAPI GetFlags(DWORD* S) 
    {
        *S = AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO;
        return S_OK;
    };

    IAIMPString* makeString(const wchar_t* text)
    {
        IAIMPString* string;
        if (SUCCEEDED(fCore->CreateObject(IID_IAIMPString, reinterpret_cast<void**>(&string))))
        {
            string->SetData(const_cast<wchar_t*>(text), wcslen(text));
            return string;
        }
        return nullptr;        
    }

    virtual BOOL isOurRIID(REFIID riid)
    {
        return riid == IID_IAIMPExtensionFileFormat;
    }
};

class Plugin : public IUnknownInterfaceImpl<IAIMPPlugin>
{
    PWCHAR WINAPI InfoGet(int Index)
    {
        switch (Index)
        {
            case AIMP_PLUGIN_INFO_NAME:
                return const_cast<PWCHAR>(Name);
            case AIMP_PLUGIN_INFO_AUTHOR:
                return const_cast<PWCHAR>(Author);
            case AIMP_PLUGIN_INFO_SHORT_DESCRIPTION:
                return const_cast<PWCHAR>(ShortDesc);
        }
        return nullptr;
    }

    DWORD WINAPI InfoGetCategories()
    {
        return AIMP_PLUGIN_CATEGORY_ADDONS;
    }

    HRESULT WINAPI Initialize(IAIMPCore* Core);
    HRESULT WINAPI Finalize();

    void WINAPI SystemNotification(int NotifyID, IUnknown* Data) { }
};