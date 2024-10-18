#include "win_capturer/video_capturer.h"

VideoCapturer::VideoCapturer(int width, int height, int fps, int device_id)
	:_width(width),
	_height(height),
	_fps(fps),
	_device_id(device_id)
{

}

int VideoCapturer::start_capture()
{
	auto devices = MfDevice::get_video_devices();
	if (_device_id >= devices.size())
	{
		return -1;
	}
	//
	std::vector<VideoDeviceAbility> usable_ability;
	for (int i = 0; i < devices[_device_id]->video_abilities.size(); ++i)
	{
		auto& ab = devices[_device_id]->video_abilities[i];
		if (ab.width == _width && ab.height == _height && (ab.fps_num / ab.fps_den) == _fps)
		{
			usable_ability.push_back(ab);
		}
	}
	if (usable_ability.size() < 1)
	{
		return -2;
	}

	//对颜色空间进行排序
	//轮询每一种颜色空间进行录制

	return 0;
}