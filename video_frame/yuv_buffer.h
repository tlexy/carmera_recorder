#ifndef YUV_BUFFER_H
#define YUV_BUFFER_H

#include <stdint.h>
#include <mfobjects.h>
#include "base/mf_device_def.h"
#include <memory>

class YuvBuffer 
{
public:
	YuvBuffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType);
	YuvBuffer(int width, int height, DeviceColorOuput videoSubType);
	//4:2:0格式的，统一转为i420格式使用
	virtual std::shared_ptr<YuvBuffer> toI420();
	//4:2:2格式的，统一转为？格式使用（根据ffmpeg编码器（硬件or软件）支持而确定）
	virtual std::shared_ptr<YuvBuffer> toX422();

	void unlock();

	virtual int StrideY() const = 0;
	virtual int StrideU() const = 0;
	virtual int StrideV() const = 0;

	int Width();
	int Height();

protected:
	IMFMediaBuffer* _win_buffer{ nullptr };
	uint8_t* _inner_buffer{ nullptr };
	int _width;
	int _height;
	DeviceColorOuput _subtype;
};

#endif