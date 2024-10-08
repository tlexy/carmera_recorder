#include "win_capturer/mf_device.h"
#include <Windows.h>
//#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <stdint.h>

std::vector<std::shared_ptr<DeviceUnit>> MfDevice::video_devices;
IMFAttributes* MfDevice::video_attri = NULL;

MfDevice::MfDevice()
{
    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (!SUCCEEDED(hr))
    {
        abort();
    }
    hr = MFStartup(MF_VERSION);
    if (!SUCCEEDED(hr))
    {
        abort();
    }
}

std::vector<std::shared_ptr<DeviceUnit>> MfDevice::get_video_devices()
{
    if (video_devices.size() > 0) 
    {
        return video_devices;
    }
    auto attri = video_attribute();
    if (!attri)
    {
        return video_devices;
    }

    IMFActivate** ppDevices = NULL;
    uint32_t count = 0;
    HRESULT hr = MFEnumDeviceSources(attri, &ppDevices, &count);
    if (!SUCCEEDED(hr))
    {
        return video_devices;
    }
    //
    video_devices.clear();
    for (DWORD i = 0; i < count; i++)
    {
        WCHAR* szFriendlyName = NULL;
        UINT32 cchName;
        hr = ppDevices[i]->GetAllocatedString(
            MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME,
            &szFriendlyName, &cchName);

        if (SUCCEEDED(hr))
        {
            std::wstring str(szFriendlyName, cchName);
            auto ptr = std::make_shared<DeviceUnit>();
            ptr->index = i;
            ptr->name = str;
            video_devices.push_back(ptr);
        }
        CoTaskMemFree(szFriendlyName);
    }
    return video_devices;
}

IMFAttributes* MfDevice::video_attribute()
{
    if (!video_attri)
    {
        HRESULT hr = MFCreateAttributes(&video_attri, 1);

        // Request video capture devices.
        if (SUCCEEDED(hr))
        {
            hr = video_attri->SetGUID(
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
                MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
            );
            if (!SUCCEEDED(hr))
            {
                video_attri = NULL;
            }
        }
        else
        {
            video_attri = NULL;
        }
    }
    return video_attri;
}

MfDevice::~MfDevice()
{
    MFShutdown();
    CoUninitialize();
}