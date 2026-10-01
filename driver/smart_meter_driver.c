#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#include "../include/smart_meter_ioctl.h"

#define DEVICE_NAME "smart_meter"

static DEFINE_MUTEX(smart_meter_mutex);
static __u64 smart_meter_pulse_count;

static long smart_meter_ioctl(struct file *file,
                              unsigned int command,
                              unsigned long argument)
{
    __u32 pulses;
    __u64 count;

    (void)file;

    if (_IOC_TYPE(command) != SMART_METER_IOC_MAGIC)
        return -ENOTTY;

    switch (command) {
    case SMART_METER_IOC_INJECT_PULSES:
        if (copy_from_user(&pulses, (void __user *)argument,
                           sizeof(pulses)))
            return -EFAULT;

        if (pulses == 0)
            return -EINVAL;

        mutex_lock(&smart_meter_mutex);

        if (smart_meter_pulse_count > (~(__u64)0 - pulses)) {
            mutex_unlock(&smart_meter_mutex);
            return -EOVERFLOW;
        }

        smart_meter_pulse_count += pulses;
        mutex_unlock(&smart_meter_mutex);
        return 0;

    case SMART_METER_IOC_GET_COUNT:
        mutex_lock(&smart_meter_mutex);
        count = smart_meter_pulse_count;
        mutex_unlock(&smart_meter_mutex);

        if (copy_to_user((void __user *)argument, &count, sizeof(count)))
            return -EFAULT;

        return 0;

    case SMART_METER_IOC_RESET_COUNT:
        mutex_lock(&smart_meter_mutex);
        smart_meter_pulse_count = 0;
        mutex_unlock(&smart_meter_mutex);
        return 0;

    default:
        return -ENOTTY;
    }
}

static const struct file_operations smart_meter_file_operations = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = smart_meter_ioctl,
   
};

static struct miscdevice smart_meter_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &smart_meter_file_operations,
    .mode = 0660,
};

static int __init smart_meter_init(void)
{
    int result = misc_register(&smart_meter_device);

    if (result)
        pr_err("smart_meter: failed to register device: %d\n", result);
    else
        pr_info("smart_meter: registered /dev/%s\n", DEVICE_NAME);

    return result;
}

static void __exit smart_meter_exit(void)
{
    misc_deregister(&smart_meter_device);
    pr_info("smart_meter: unregistered /dev/%s\n", DEVICE_NAME);
}

module_init(smart_meter_init);
module_exit(smart_meter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smart Meter Capstone Project");
MODULE_DESCRIPTION("Software-only virtual smart-meter pulse counter");
MODULE_VERSION("1.0");
