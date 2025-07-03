#include "device_driver.h"
#include <iostream>
class ReadFiveTimeFail : public std::exception {};
class WriteWhenRead0xFF : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int ret = (int)(m_hardware->read(address));
    checkPostcondition(ret, address);
    return ret;
}

void DeviceDriver::checkPostcondition(int& ret, long address)
{
    int cmp;
    for (int i = 0; i < 4; i++) {
        cmp = (int)(m_hardware->read(address));
        if (cmp != ret)
            throw std::exception();
    }
    return;
}

void DeviceDriver::write(long address, int data)
{
    int testValue = (int)(m_hardware->read(address));
    if (testValue != 0xFF) {
        throw WriteWhenRead0xFF();
    }
    m_hardware->write(address, (unsigned char)data);
}
