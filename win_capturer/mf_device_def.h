#ifndef MF_DEVICE_DEF_H
#define MF_DEVICE_DEF_H

#include <string>
#include <vector>

enum class DeviceColorOuput
{
	MF_NONE = 0,
	MF_YUY2 = 1,
	MF_NV12 = 2,
	MF_MJPG = 3,
	MF_I420 = 4,
	MF_YVYU = 5,
	MF_IYUV = 6
};

struct VideoDeviceAbility
{
	int fps_num;
	int fps_den;
	int width;
	int height;
	DeviceColorOuput color;
};

struct DeviceUnit
{
	int index;
	std::wstring name;
	std::vector<VideoDeviceAbility> video_abilities;
};

#endif