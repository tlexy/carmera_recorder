#include "video_frame/nv12_buffer.h"
#include <libyuv/convert.h>
#include "video_frame/i420_buffer.h"

Nv12Buffer::Nv12Buffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType)
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

Nv12Buffer::Nv12Buffer(int width, int height, DeviceColorOuput videoSubType)
	:YuvBuffer(width, height, videoSubType)
{}

std::shared_ptr<YuvBuffer> Nv12Buffer::toI420()
{
	auto i420_buffer = std::make_shared<I420Buffer>(_width, _height, DeviceColorOuput::MF_I420);
	libyuv::NV12ToI420(DataY(), StrideY(), DataU(), StrideU(),
		i420_buffer->MutableDataY(), i420_buffer->StrideY(),
		i420_buffer->MutableDataU(), i420_buffer->StrideU(),
		i420_buffer->MutableDataV(), i420_buffer->StrideV(),
		Width(), Height());
	return i420_buffer;
}

const uint8_t* Nv12Buffer::DataY() const
{
	return _pp_buffer;
}

const uint8_t* Nv12Buffer::DataU() const
{
	return _pp_buffer + StrideY() * _height;
}

const uint8_t* Nv12Buffer::DataV() const
{
	return _pp_buffer + StrideY() * _height + StrideU() * _height;
}

int Nv12Buffer::StrideY() const
{
	return _width;
}

int Nv12Buffer::StrideU() const
{
	return _width; //等价于Stride_UV
}

int Nv12Buffer::StrideV() const
{
	return _width;//等价于Stride_UV
}