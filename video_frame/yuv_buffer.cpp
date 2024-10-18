#include "video_frame/yuv_buffer.h"

YuvBuffer::YuvBuffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType)
	:_win_buffer(buffer),
	_width(width),
	_height(height),
	_subtype(videoSubType)
{}

YuvBuffer::YuvBuffer(int width, int height, DeviceColorOuput videoSubType)
	:_width(width),
	_height(height),
	_subtype(videoSubType)
{

}

void YuvBuffer::unlock()
{
	if (_win_buffer) {
		_win_buffer.unlock();
	}
}

std::shared_ptr<YuvBuffer> YuvBuffer::toI420()
{
	return nullptr;
}

std::shared_ptr<YuvBuffer> YuvBuffer::toX422()
{
	return nullptr;
}

int YuvBuffer::Width()
{
	return _width;
}

int YuvBuffer::Height()
{
	return _height;
}