#include "smart_meter_device.hpp"

#include "../include/smart_meter_ioctl.h"

#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

SmartMeterDevice::SmartMeterDevice()
    : file_descriptor_(-1)
{
}

SmartMeterDevice::~SmartMeterDevice()
{
    closeDevice();
}

bool SmartMeterDevice::openDevice()
{
    if (isOpen())
        return true;

    file_descriptor_ = ::open("/dev/smart_meter", O_RDWR | O_CLOEXEC);
    if (file_descriptor_ < 0) {
        perror("Could not open /dev/smart_meter");
        return false;
    }

    return true;
}

bool SmartMeterDevice::injectPulses(std::uint32_t pulses)
{
    if (!isOpen()) {
        std::cerr << "Device is not open.\n";
        return false;
    }

    if (pulses == 0) {
        std::cerr << "Pulse quantity must be greater than zero.\n";
        return false;
    }

    if (::ioctl(file_descriptor_, SMART_METER_IOC_INJECT_PULSES, &pulses) < 0) {
        perror("Could not inject pulses");
        return false;
    }

    return true;
}

bool SmartMeterDevice::getPulseCount(std::uint64_t& count) const
{
    if (!isOpen()) {
        std::cerr << "Device is not open.\n";
        return false;
    }

    if (::ioctl(file_descriptor_, SMART_METER_IOC_GET_COUNT, &count) < 0) {
        perror("Could not read pulse count");
        return false;
    }

    return true;
}

bool SmartMeterDevice::resetCount() const
{
    if (!isOpen()) {
        std::cerr << "Device is not open.\n";
        return false;
    }

    if (::ioctl(file_descriptor_, SMART_METER_IOC_RESET_COUNT, 0) < 0) {
        perror("Could not reset pulse count");
        return false;
    }

    return true;
}

void SmartMeterDevice::closeDevice()
{
    if (file_descriptor_ >= 0) {
        if (::close(file_descriptor_) < 0)
            perror("Could not close /dev/smart_meter");

        file_descriptor_ = -1;
    }
}

bool SmartMeterDevice::isOpen() const noexcept
{
    return file_descriptor_ >= 0;
}
