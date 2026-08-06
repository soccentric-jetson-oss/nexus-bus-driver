// SPDX-License-Identifier: GPL-2.0-only
/**
 * @file main.c
 * @brief Module entry point for Nexus Bus driver
 *
 * Thin module glue: init, exit, probe, remove. Delegates all
 * functional logic to bus_ioctl and chardev modules.
 *
 * @copyright Copyright (c) 2026 SoC Centric LLC
 * @author Sandesh Ghimire
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>

#include "nexus_bus_uapi.h"
#include "nexus_bus_core.h"

#define DRV_NAME    "nexus-bus"
#define DRV_VERSION "0.1.0"

static const struct class nexus_bus_class = {
    .name  = DRV_NAME,
};

static int nexus_bus_probe(struct platform_device *pdev)
{
    struct device *devp = &pdev->dev;
    struct nexus_bus_dev *dev;
    int r;

    dev = devm_kzalloc(devp, sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->pdev = pdev;
    platform_set_drvdata(pdev, dev);
    mutex_init(&dev->lock);

    /* ── Character device registration ──────────────────────────────── */
    r = alloc_chrdev_region(&dev->devt, 0, 1, DRV_NAME);
    if (r)
        return dev_err_probe(devp, r, "chrdev region\n");

    cdev_init(&dev->cdev, &nexus_bus_fops);
    dev->cdev.owner = THIS_MODULE;
    r = cdev_add(&dev->cdev, dev->devt, 1);
    if (r) {
        unregister_chrdev_region(dev->devt, 1);
        return r;
    }

    dev->dev = device_create(&nexus_bus_class, devp, dev->devt,
                             dev, DRV_NAME "%u", 0);
    if (IS_ERR(dev->dev)) {
        cdev_del(&dev->cdev);
        unregister_chrdev_region(dev->devt, 1);
        return PTR_ERR(dev->dev);
    }

    dev_info(devp, "Nexus Bus v%s loaded\n", DRV_VERSION);
    return 0;
}

static void nexus_bus_remove(struct platform_device *pdev)
{
    struct nexus_bus_dev *dev = platform_get_drvdata(pdev);

    device_destroy(&nexus_bus_class, dev->devt);
    cdev_del(&dev->cdev);
    unregister_chrdev_region(dev->devt, 1);
}

/* ── Device tree match table ─────────────────────────────────────────── */

static const struct of_device_id nexus_bus_of_match[] = {
    { .compatible = "nvidia,tegra234-nexus-bus" },
    {}
};
MODULE_DEVICE_TABLE(of, nexus_bus_of_match);

static struct platform_driver nexus_bus_driver = {
    .probe  = nexus_bus_probe,
    .remove = nexus_bus_remove,
    .driver = {
        .name           = DRV_NAME,
        .of_match_table = nexus_bus_of_match,
    },
};

/* ── Module init / exit ──────────────────────────────────────────────── */

static int __init nexus_bus_init(void)
{
    int r;

    r = class_register(&nexus_bus_class);
    if (r)
        return r;

    r = platform_driver_register(&nexus_bus_driver);
    if (r)
        class_unregister(&nexus_bus_class);

    pr_info("Nexus Bus v%s\n", DRV_VERSION);
    return r;
}

static void __exit nexus_bus_exit(void)
{
    platform_driver_unregister(&nexus_bus_driver);
    class_unregister(&nexus_bus_class);
}

module_init(nexus_bus_init);
module_exit(nexus_bus_exit);

MODULE_AUTHOR("Sandesh Ghimire <sandesh@soccentric.com>");
MODULE_DESCRIPTION("Jetson AGX Orin peripheral bus driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRV_VERSION);
