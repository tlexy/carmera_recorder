#include <Windows.h>
#include "win_capturer/mf_device.h"
//#include <mfapi.h>
#include <mfreadwrite.h>
#include <mfidl.h>
#include <mferror.h>
#include <stdint.h>
#include <iostream>

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
            //获取设备能力
            hr = get_video_abilities(i, ppDevices, ptr);
            if (hr == S_OK)
            {
                video_devices.push_back(ptr);
                ppDevices[i]->Release();
            }
            else
            {
                std::wcerr << "index " << i << " device not available: " << str << std::endl;
            }
            CoTaskMemFree(szFriendlyName);
        }
        
    }
    CoTaskMemFree(ppDevices);
    return video_devices;
}

HRESULT MfDevice::get_video_abilities(int index, IMFActivate** imf, std::shared_ptr<DeviceUnit> ptr)
{
    IMFMediaSource* source = NULL;
    HRESULT hr = imf[index]->ActivateObject(IID_PPV_ARGS(&source));
    if (!SUCCEEDED(hr))
    {
        return hr;
    }
    auto attri = video_attribute();
    IMFSourceReader* videoReader = NULL;
    hr = MFCreateSourceReaderFromMediaSource(
        source,
        attri,
        &videoReader);
    if (!SUCCEEDED(hr))
    {
        return hr;
    }
    DWORD dwMediaTypeIndex = 0;
    int limit = 0;
    while (true) {
        IMFMediaType* nativeTypes = NULL;
        hr = videoReader->GetNativeMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            dwMediaTypeIndex, &nativeTypes);
        if (hr == MF_E_NO_MORE_TYPES)
        {
            break;
        }
        if (!SUCCEEDED(hr))
        {
            break;
        }
        if (limit > 10000)
        {
            std::cout << "limitation too big, something error." << std::endl;
            break;
        }
        ++limit;
        ++dwMediaTypeIndex;
        VideoDeviceAbility ability;
        ability.color = DeviceColorOuput::MF_NONE;

        GUID subType;
        WCHAR* pGuidName = NULL;
        hr = nativeTypes->GetGUID(MF_MT_SUBTYPE, &subType);
        if (SUCCEEDED(hr))
        {
            ability.color = to_std_color(subType);
        }
        GetGUIDName(subType, &pGuidName);

        UINT32 width = 0, height = 0, fpsNum = 0, fpsDen = 0;
        MFGetAttributeSize(nativeTypes, MF_MT_FRAME_SIZE, &width, &height);
        MFGetAttributeRatio(nativeTypes, MF_MT_FRAME_RATE, &fpsNum, &fpsDen);
        
        ability.fps_den = fpsDen;
        ability.fps_num = fpsNum;
        ability.width = width;
        ability.height = height;
        //颜色转换
        ptr->video_abilities.push_back(ability);
    }
    return S_OK;
}

DeviceColorOuput MfDevice::to_std_color(const GUID& guid)
{
    if (guid == MFVideoFormat_I420)
    {
        return DeviceColorOuput::MF_I420;
    }
    if (guid == MFVideoFormat_IYUV)
    {
        return DeviceColorOuput::MF_IYUV;
    }
    if (guid == MFVideoFormat_MJPG)
    {
        return DeviceColorOuput::MF_MJPG;
    }
    if (guid == MFVideoFormat_NV12)
    {
        return DeviceColorOuput::MF_NV12;
    }
    if (guid == MFVideoFormat_YUY2)
    {
        return DeviceColorOuput::MF_YUY2;
    }
    if (guid == MFVideoFormat_YVYU)
    {
        return DeviceColorOuput::MF_YVYU;
    }
    return DeviceColorOuput::MF_NONE;
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