#include "win_capturer/color_helper.h"

int ConvertVideoType(DeviceColorOuput ouput_type) {
    switch (ouput_type) {
    case DeviceColorOuput::MF_NONE:
        return libyuv::FOURCC_ANY;
    case DeviceColorOuput::MF_I420:
        return libyuv::FOURCC_I420;
    case VideoType::kIYUV:  // same as VideoType::kYV12
    case VideoType::kYV12:
        return libyuv::FOURCC_YV12;
    case VideoType::kRGB24:
        return libyuv::FOURCC_24BG;
    case VideoType::kRGB565:
        return libyuv::FOURCC_RGBP;
    case VideoType::kYUY2:
        return libyuv::FOURCC_YUY2;
    case VideoType::kUYVY:
        return libyuv::FOURCC_UYVY;
    case VideoType::kMJPEG:
        return libyuv::FOURCC_MJPG;
    case VideoType::kARGB:
        return libyuv::FOURCC_ARGB;
    case VideoType::kBGRA:
        return libyuv::FOURCC_BGRA;
    }
    //RTC_DCHECK_NOTREACHED();
    return libyuv::FOURCC_ANY;
}