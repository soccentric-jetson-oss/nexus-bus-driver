// SPDX-License-Identifier: GPL-2.0-only
/**
 * @file chardev.c
 * @brief Character device operations for Nexus Bus driver
 *
 * Implements open, release, and ioctl handlers that dispatch to
 * the bus transfer module.
 *
 * @copyright Copyright (c) 2026 SoC Centric LLC
 * @author Sandesh Ghimire
 */

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "nexus_bus_uapi.h"
#include "nexus_bus_core.h"

static int nexus_bus_open(struct inode *inode, struct file *filp)
{
    filp->private_data = container_of(inode->i_cdev,
                                      struct nexus_bus_dev, cdev);
    return 0;
}

static int nexus_bus_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static long nexus_bus_ioctl(struct file *filp, unsigned int cmd,
                            unsigned long arg)
{
    struct nexus_bus_dev *dev = filp->private_data;
    void __user *u = (void __user *)arg;
    struct nexus_bus_transfer xfer;
    int ret;

    switch (cmd) {

    case NEXUS_BUS_IOCTL_READ:
        if (copy_from_user(&xfer, u, sizeof(xfer)))
            return -EFAULT;

        ret = nexus_bus_read(dev, &xfer);
        if (ret)
            return ret;

        if (copy_to_user(u, &xfer, sizeof(xfer)))
            return -EFAULT;
        return 0;

    case NEXUS_BUS_IOCTL_WRITE:
        if (copy_from_user(&xfer, u, sizeof(xfer)))
            return -EFAULT;

        ret = nexus_bus_write(dev, &xfer);
        if (ret)
            return ret;
        return 0;

    case NEXUS_BUS_IOCTL_GET_INFO: {
        __u32 info = 0;

        if (copy_to_user(u, &info, sizeof(info)))
            return -EFAULT;
        return 0;
    }

    case NEXUS_BUS_IOCTL_GET_DEBUG: {
        struct nexus_bus_debug_info dbg;

        memset(&dbg, 0, sizeof(dbg));
        if (copy_to_user(u, &dbg, sizeof(dbg)))
            return -EFAULT;
        return 0;
    }

    case NEXUS_BUS_IOCTL_RESET: {
        __u32 bus_id;

        if (copy_from_user(&bus_id, u, sizeof(bus_id)))
            return -EFAULT;
        dev_info(&dev->pdev->dev, "Reset bus %u\n", bus_id);
        return 0;
    }

    default:
        return -ENOTTY;
    }
}

const struct file_operations nexus_bus_fops = {
    .owner          = THIS_MODULE,
    .open           = nexus_bus_open,
    .release        = nexus_bus_release,
    .unlocked_ioctl = nexus_bus_ioctl,
    .llseek         = noop_llseek,
};
