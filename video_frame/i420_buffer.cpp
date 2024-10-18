#include "video_frame/i420_buffer.h"

I420Buffer::I420Buffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType)
	:YuvBuffer(buffer, width, height, videoSubType)
{
	HRESULT hr = _win_buffer->Lock(&_pp_buffer, (DWORD*)&_max_length, (DWORD*)&_curr_length);
	if (hr != S_OK)
	{
		_pp_buffer = nullptr;
		_max_length = 0;
		_curr_length = 0;
	}
}

I420Buffer::I420Buffer(int width, int height, DeviceColorOuput videoSubType)
	:YuvBuffer(width, height, videoSubType)
{}

const uint8_t* I420Buffer::DataY() const
{
	return _pp_buffer;
}

const uint8_t* I420Buffer::DataU() const
{
	return _pp_buffer + StrideY() * _height;
}

const uint8_t* I420Buffer::DataV() const
{
	return _pp_buffer + StrideY() * _height + StrideU() * _height;
}

int I420Buffer::StrideY() const
{
	return _width;
}

int I420Buffer::StrideU() const
{
	return _width / 2;
}

int I420Buffer::StrideV() const
{
	return _width / 2;
}