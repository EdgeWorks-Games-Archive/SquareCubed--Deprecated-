#pragma once

#include "CoherentUI.h"

class SharedMemoryHelper
{
public:
	static void* Map(Coherent::UI::CoherentHandle handle, size_t sizeInBytes);

	static void Unmap(const void* handle, size_t sizeInBytes);

	static Coherent::UI::CoherentHandle CreateSegment(size_t sizeInBytes);

	static void DestroySegment(Coherent::UI::CoherentHandle handle);

private:
	SharedMemoryHelper();
};