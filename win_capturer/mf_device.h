#ifndef MF_DEVICE_H
#define MF_DEVICE_H

#include <memory>
#include <vector>
#include <mfapi.h>

#include "win_capturer/mf_device_def.h"

class MfDevice
{
public:
	MfDevice();
	~MfDevice();

	static std::vector<std::shared_ptr<DeviceUnit>> get_video_devices();
	static IMFAttributes* video_attribute();

public:
	static std::vector<std::shared_ptr<DeviceUnit>> video_devices;
	static IMFAttributes* video_attri;
};

#endif