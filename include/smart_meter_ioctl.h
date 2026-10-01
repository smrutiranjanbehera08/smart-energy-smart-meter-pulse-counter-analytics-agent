#ifndef SMART_METER_IOCTL_H
#define SMART_METER_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

/*
 * Shared ioctl interface for the Smart Meter Linux driver and C++ application.
 * Keep the command numbers and data types consistent in both components.
 */
#define SMART_METER_IOC_MAGIC 'S'

#define SMART_METER_IOC_INJECT_PULSES \
    _IOW(SMART_METER_IOC_MAGIC, 1, __u32)

#define SMART_METER_IOC_GET_COUNT \
    _IOR(SMART_METER_IOC_MAGIC, 2, __u64)

#define SMART_METER_IOC_RESET_COUNT \
    _IO(SMART_METER_IOC_MAGIC, 3)

#endif /* SMART_METER_IOCTL_H */
