#ifndef VIDEO_CAPTURER_H
#define VIDEO_CAPTURER_H

#include "win_capturer/mf_device.h"

class VideoCapturer
{
public:
	VideoCapturer(int width, int height, int fps, int device_id);

	int start_capture();

private:
	int _width;
	int _height;
	int _fps;
	int _device_id;
};

#endif