#pragma once

#include "StackAllocator.h"

class DoubleBufferedFrameAllocated
{
private:
	FrameAllocator buffers[2];
	char currentBufferID = 0;

public:
	DoubleBufferedFrameAllocated()
	{
		buffers[0].reserve(100);
		buffers[1].reserve(100);
	}

	void swapBuffers()
	{
		currentBufferID ^= 1;
		getWriteBuffer().clearFront();
	}

	FrameAllocator& getWriteBuffer()
	{
		return buffers[currentBufferID];
	}

	char getBufferID()
	{
		return currentBufferID;
	}

	template<typename T>
	T* write()
	{
		return getWriteBuffer().push<T>();
	}
};

