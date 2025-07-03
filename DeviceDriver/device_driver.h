#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void checkPostcondition(int& ret, long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};