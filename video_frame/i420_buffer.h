#ifndef I420_BUFFER_H
#define I420_BUFFER_H

#include <stdint.h>
#include "video_frame/yuv_buffer.h"

class I420Buffer : public YuvBuffer
{
public:
	I420Buffer(IMFMediaBuffer* buffer, int width, int height, DeviceColorOuput videoSubType);
	I420Buffer(int width, int height, DeviceColorOuput videoSubType);

	const uint8_t* DataY() const;
	const uint8_t* DataU() const;
	const uint8_t* DataV() const;

	virtual int StrideY() const;
	virtual int StrideU() const;
	virtual int StrideV() const;

private:
	uint8_t* _pp_buffer;
	int _max_length;
	int _curr_length;
};

#endif