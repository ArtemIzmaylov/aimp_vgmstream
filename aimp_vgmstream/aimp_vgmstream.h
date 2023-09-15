#pragma once
#include <apiDecoders.h>
#include <apiPlugin.h>
#include <vgmstream.h>
#include "IUnknownInterfaceImpl.h"

static const wchar_t Name[] = L"VGMStream for AIMP";
static const wchar_t Author[] = L"Artem Izmaylov";
static const wchar_t Description[] = L"Provides ability to play video game music";
static const wchar_t Extensions[] = L"*.04sw;*.208;*.2dx9;*.2pfs;*.3do;*.4;*.8;*.800;*.9tav;*.aa3;*.aax;*.abc;*.abk;*.acb;*.acm;*.acx;*.ad;*.adc;*.adm;*.adp;*.adpcm;*.adpcmx;*.ads;*.adw;*.adx;*.afc;*.afs2;*.agsc;*.ahx;*.ahv;*.ai;*.aif;*.aifc;*.aifcl;*.aiffl;*.aix;*.akb;*.al;*.al2;*.ams;*.amts;*.ao;*.ap;*.apc;*.as4;*.asd;*.asf;*.asr;*.ass;*.ast;*.at3;*.at9;*.atsl;*.atsl3;*.atsl4;*.atx;*.aud;*.audio;*.aus;*.awb;*.awc;*.b1s;*.baf;*.baka;*.bank;*.bar;*.bcstm;*.bcwav;*.bd3;*.bdsp;*.bfstm;*.bfwav;*.bfwavnsmbu;*.bg00;*.bgm;*.bgw;*.bh2pcm;*.bik;*.bika;*.bik2;*.bk2;*.blk;*.bmdx;*.bms;*.bnk;*.bnm;*.bns;*.bnsf;*.bo2;*.brstm;*.brstmspm;*.bsnd;*.btsnd;*.bvg;*.bwav;*.caf;*.capdsp;*.cbd2;*.ccc;*.cd;*.cfn;*.chk;*.ckb;*.ckd;*.cks;*.cnk;*.cpk;*.cps;*.csa;*.csmp;*.cvs;*.cwav;*.cxs;*.da;*.data;*.dax;*.dbm;*.dct;*.dcs;*.ddsp;*.de2;*.dec;*.diva;*.dmsg;*.ds2;*.dsb;*.dsf;*.dsp;*.dspw;*.dtk;*.dvi;*.dxh;*.e4x;*.eam;*.eas;*.eda;*.emff;*.enm;*.eno;*.ens;*.exa;*.ezw;*.fag;*.fda;*.ffw;*.filp;*.flx;*.fsb;*.fsv;*.fwav;*.fwse;*.g1l;*.gbts;*.gca;*.gcm;*.gcub;*.gcw;*.genh;*.gin;*.gms;*.grn;*.gsb;*.gsf;*.gtd;*.gwm;*.h4m;*.hab;*.hca;*.hdr;*.hgc1;*.his;*.hps;*.hsf;*.hwx;*.hx2;*.hx3;*.hxc;*.hxd;*.hxg;*.hxx;*.hwas;*.iab;*.iadp;*.idmsf;*.idsp;*.idvi;*.idwav;*.idx;*.idxma;*.ifs;*.ikm;*.ild;*.ilv;*.ima;*.imc;*.imx;*.int;*.is14;*.isb;*.isd;*.isws;*.itl;*.ivaud;*.ivag;*.ivb;*.ivs;*.joe;*.jstm;*.kat;*.kces;*.kcey;*.km9;*.kovs;*.kno;*.kns;*.kraw;*.ktac;*.ktsl2asbin;*.ktss;*.kvs;*.kwa;*.l00;*.laac;*.laif;*.laiff;*.laifc;*.lac3;*.lasf;*.lbin;*.leg;*.lep;*.lflac;*.lin;*.lm0;*.lm1;*.lm2;*.lm3;*.lm4;*.lm5;*.lm6;*.lm7;*.lmp2;*.lmp3;*.lmp4;*.lmpc;*.logg;*.lopus;*.lp;*.lpcm;*.lpk;*.lps;*.lrmb;*.lse;*.lsf;*.lstm;*.lwav;*.lwma;*.mab;*.mad;*.map;*.matx;*.mc3;*.mca;*.mcadpcm;*.mcg;*.mds;*.mdsp;*.med;*.mjb;*.mi4;*.mib;*.mic;*.mihb;*.mnstr;*.mogg;*.mpdsp;*.mpds;*.mpf;*.mps;*.ms;*.msa;*.msb;*.msd;*.msf;*.mss;*.msv;*.msvp;*.mta2;*.mtaf;*.mul;*.mups;*.mus;*.musc;*.musx;*.mvb;*.mwa;*.mwv;*.mxst;*.myspd;*.n64;*.naac;*.nds;*.ndp;*.nlsd;*.nop;*.nps;*.npsf;*.nsopus;*.nub;*.nub2;*.nus3audio;*.nus3bank;*.nwa;*.nwav;*.nxa;*.ogl;*.ogv;*.oma;*.omu;*.opusx;*.otm;*.oto;*.ovb;*.p04;*.p16;*.p1d;*.p2a;*.p2bt;*.p3d;*.past;*.pcm;*.pdt;*.pk;*.pnb;*.pona;*.pos;*.ps2stm;*.psf;*.psh;*.psnd;*.psw;*.rac;*.rad;*.rak;*.ras;*.raw;*.rda;*.rkv;*.rnd;*.rof;*.rpgmvo;*.rrds;*.rsd;*.rsf;*.rsm;*.rsp;*.rstm;*.rvws;*.rwar;*.rwav;*.rws;*.rwsd;*.rwx;*.rxw;*.rxx;*.s14;*.s3v;*.sab;*.sad;*.saf;*.sap;*.sb0;*.sb1;*.sb2;*.sb3;*.sb4;*.sb5;*.sb6;*.sb7;*.sbk;*.sbr;*.sbv;*.sm0;*.sm1;*.sm2;*.sm3;*.sm4;*.sm5;*.sm6;*.sm7;*.sbin;*.sc;*.scd;*.sch;*.sd9;*.sdf;*.sdt;*.seb;*.sed;*.seg;*.sf0;*.sfl;*.sfs;*.sfx;*.sgb;*.sgd;*.sgx;*.sl3;*.slb;*.sli;*.smc;*.smk;*.smp;*.smpl;*.smv;*.snd;*.snds;*.sng;*.sngw;*.snr;*.sns;*.snu;*.snz;*.sod;*.son;*.spd;*.spm;*.sps;*.spsd;*.spw;*.ss2;*.ssd;*.ssm;*.sss;*.ster;*.sth;*.stm;*.stma;*.str;*.stream;*.strm;*.sts;*.sts_cp3;*.stx;*.svag;*.svs;*.svg;*.swag;*.swav;*.swd;*.switch_audio;*.sx;*.sxd;*.sxd2;*.sxd3;*.tec;*.tgq;*.thp;*.tk5;*.tmx;*.tra;*.tun;*.txth;*.txtp;*.tydsp;*.ue4opus;*.ulw;*.um3;*.utk;*.uv;*.v0;*.va3;*.vag;*.vai;*.vam;*.vas;*.vawx;*.vb;*.vbk;*.vbx;*.vds;*.vdm;*.vgm;*.vgs;*.vgv;*.vid;*.vig;*.vis;*.vms;*.vmu;*.voi;*.vp6;*.vpk;*.vs;*.vsf;*.vsv;*.vxn;*.waa;*.wac;*.wad;*.waf;*.wam;*.was;*.wavc;*.wave;*.wavebatch;*.wavm;*.wavx;*.way;*.wb;*.wb2;*.wbd;*.wd;*.wem;*.wii;*.wip;*.wlv;*.wmus;*.wp2;*.wpd;*.wsd;*.wsi;*.wua;*.wv2;*.wv6;*.wve;*.wvs;*.wvx;*.x;*.x360audio;*.xa;*.xa2;*.xa30;*.xag;*.xau;*.xav;*.xb;*.xen;*.xma;*.xma2;*.xmu;*.xnb;*.xsf;*.xse;*.xsew;*.xss;*.xvag;*.xvas;*.xwav;*.xwb;*.xmd;*.xopus;*.xps;*.xwc;*.xwm;*.xwma;*.xws;*.xwv;*.ydsp;*.ymf;*.zic;*.zsd;*.zsm;*.zss;*.zwdsp;*.zwv;";

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
        *S = makeString(L"Game Music (vgmstream)");
        return S_OK;
    };

    virtual HRESULT WINAPI GetExtList(IAIMPString** S)
    {
        *S = makeString(Extensions);
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
                return const_cast<PWCHAR>(Description);
        }
        return nullptr;
    }

    DWORD WINAPI InfoGetCategories()
    {
        return AIMP_PLUGIN_CATEGORY_DECODERS;
    }

    HRESULT WINAPI Initialize(IAIMPCore* Core);
    HRESULT WINAPI Finalize();

    void WINAPI SystemNotification(int NotifyID, IUnknown* Data) { }
};