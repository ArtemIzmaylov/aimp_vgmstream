#pragma once

#include <Unknwn.h>


//! Helper implements IUnknown interface.
template <typename T>
class IUnknownInterfaceImpl : public T
{
public:

    IUnknownInterfaceImpl(): counter(0) {}

    virtual ~IUnknownInterfaceImpl() {}

    virtual BOOL isOurRIID(REFIID riid) 
    {
        return false;        
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObj) 
    {
        if (!ppvObj)
            return E_POINTER;

        if (IID_IUnknown == riid || isOurRIID(riid))
        {
            *ppvObj = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    virtual ULONG WINAPI AddRef(void)
    { 
        return ++counter; 
    }

    virtual ULONG WINAPI Release(void) 
    {
        ULONG reference_count = --counter;
        if (reference_count == 0)
            delete this;
        return reference_count;
    }

private:

    ULONG counter;
};
