#ifndef MF_DEVICE_DEF_H
#define MF_DEVICE_DEF_H

#include <string>

struct DeviceUnit
{
	int index;
	std::wstring name;
};

enum class DeviceColorOuput
{
	MF_NONE = 0,
	MF_YUY2 = 1,
	MF_NV12 = 2,
	MF_MJPG = 3,
	MF_I420 = 4,
	MF_YVYU = 5
};

struct VideoDeviceAbility
{
	int fps_num;
	int fps_den;
	int width;
	int height;
	DeviceColorOuput color;
};

#endif