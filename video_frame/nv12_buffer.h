#ifndef NV12_BUFFER_H
#define NV12_BUFFER_H

#include <stdint.h>
#include "video_frame/yuv_buffer.h"

class Nv12Buffer : public YuvBuffer
{
public:
	Nv12Buffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType);
	Nv12Buffer(int width, int height, DeviceColorOuput videoSubType);

	const uint8_t* DataY() const;
	const uint8_t* DataU() const;
	const uint8_t* DataV() const;

	virtual std::shared_ptr<YuvBuffer> toI420();

	virtual int StrideY() const;
	virtual int StrideU() const;
	virtual int StrideV() const;

private:
	uint8_t* _pp_buffer;
	int _max_length;
	int _curr_length;
};

#endif