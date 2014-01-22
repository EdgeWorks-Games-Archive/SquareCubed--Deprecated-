#include "SharedMemoryHelper.h"

void* SharedMemoryHelper::Map(Coherent::UI::CoherentHandle handle, size_t sizeInBytes) {
	return ::MapViewOfFile(handle, FILE_MAP_READ, 0, 0, sizeInBytes);
}

void SharedMemoryHelper::Unmap(const void* handle, size_t sizeInBytes) {
	::UnmapViewOfFile(handle);
}

Coherent::UI::CoherentHandle SharedMemoryHelper::CreateSegment(size_t sizeInBytes) {
	return Coherent::UI::CoherentHandle(::CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, static_cast<DWORD>(sizeInBytes), nullptr));
}

void SharedMemoryHelper::DestroySegment(Coherent::UI::CoherentHandle handle) {
	::CloseHandle(handle);
}