#ifndef SMART_METER_DEVICE_HPP
#define SMART_METER_DEVICE_HPP

#include <cstdint>

class SmartMeterDevice {
public:
    SmartMeterDevice();
    ~SmartMeterDevice();

    SmartMeterDevice(const SmartMeterDevice&) = delete;
    SmartMeterDevice& operator=(const SmartMeterDevice&) = delete;

    bool openDevice();
    bool injectPulses(std::uint32_t pulses);
    bool getPulseCount(std::uint64_t& count) const;
    bool resetCount() const;
    void closeDevice();
    bool isOpen() const noexcept;

private:
    int file_descriptor_;
};

#endif
