#include "win_capturer/color_helper.h"

#include <libyuv.h>

int ConvertVideoType(DeviceColorOuput ouput_type) {
    switch (ouput_type) {
    case DeviceColorOuput::MF_NONE:
        return libyuv::FOURCC_ANY;
    case DeviceColorOuput::MF_I420:
        return libyuv::FOURCC_I420;
    case DeviceColorOuput::MF_IYUV:
        return libyuv::FOURCC_IYUV;
    case DeviceColorOuput::MF_YUY2:
        return libyuv::FOURCC_YUY2;
    //case DeviceColorOuput::MF_YVYU:
    //    return libyuv::FOURCC_UYVY;
    case DeviceColorOuput::MF_MJPG:
        return libyuv::FOURCC_MJPG;
    case DeviceColorOuput::MF_NV12:
        return libyuv::FOURCC_NV12;
    }
    //RTC_DCHECK_NOTREACHED();
    return libyuv::FOURCC_ANY;
}