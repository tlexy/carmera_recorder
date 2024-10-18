#ifndef MF_DEVICE_H
#define MF_DEVICE_H

#include <memory>
#include <vector>
#include <mfapi.h>

#include "base/mf_device_def.h"
#include "win_capturer/win_capturer_helper.h"

class MfDevice
{
public:
	MfDevice();
	~MfDevice();

	static std::vector<std::shared_ptr<DeviceUnit>> get_video_devices();
	static IMFAttributes* video_attribute();
	static HRESULT get_video_abilities(int index, IMFActivate** imf, std::shared_ptr<DeviceUnit> ptr);
	static DeviceColorOuput to_std_color(const GUID& guid);

public:
	static std::vector<std::shared_ptr<DeviceUnit>> video_devices;
	static IMFAttributes* video_attri;
};

#endif