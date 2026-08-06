// SPDX-License-Identifier: GPL-2.0-only
/*
 * nexus_bus_core.h - Core device structure for Nexus Bus driver
 *
 * Defines the main device structure aggregating char device state,
 * bus transfer logic, and hardware resources.
 */

#ifndef NEXUS_BUS_CORE_H
#define NEXUS_BUS_CORE_H

#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mutex.h>

/**
 * struct nexus_bus_dev - Main driver device structure
 * @pdev:  Platform device
 * @cdev:  Character device
 * @devt:  Device number
 * @dev:   Kernel device
 * @class: Device class
 * @lock:  Mutex protecting bus transfer state
 */
struct nexus_bus_dev {
    struct platform_device *pdev;
    struct cdev cdev;
    dev_t devt;
    struct device *dev;
    const struct class *class;
    struct mutex lock;
};

/* ── Bus transfer implementation ─────────────────────────────────────── */

/**
 * nexus_bus_read - Perform a bus read operation
 * @dev:  Nexus bus device
 * @xfer: Transfer descriptor (kernel-side, already copied from user)
 *
 * Returns: 0 on success, negative errno on failure.
 */
int nexus_bus_read(struct nexus_bus_dev *dev,
                   struct nexus_bus_transfer *xfer);

/**
 * nexus_bus_write - Perform a bus write operation
 * @dev:  Nexus bus device
 * @xfer: Transfer descriptor (kernel-side, already copied from user)
 *
 * Returns: 0 on success, negative errno on failure.
 */
int nexus_bus_write(struct nexus_bus_dev *dev,
                    struct nexus_bus_transfer *xfer);

/* ── Char device operations ──────────────────────────────────────────── */

extern const struct file_operations nexus_bus_fops;

#endif /* NEXUS_BUS_CORE_H */
