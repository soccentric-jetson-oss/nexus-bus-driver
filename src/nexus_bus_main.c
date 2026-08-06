#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include "nexus_bus_uapi.h"
#define DRV_NAME "nexus-bus"
#define DRV_VERSION "0.1.0"
struct nexus_bus_dev
{
    struct platform_device *pdev;
    struct cdev cdev;
    dev_t devt;
    struct device *dev;
    const struct class *class;
};
static int nexus_bus_open(struct inode *inode, struct file *filp)
{
    filp->private_data = container_of(inode->i_cdev, struct nexus_bus_dev, cdev);
    return 0;
}
static long nexus_bus_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    struct nexus_bus_dev *dev = filp->private_data;
    void __user *u = (void __user *)arg;
    struct nexus_bus_transfer xfer;
    switch (cmd)
    {
    case NEXUS_BUS_IOCTL_READ:
        if (copy_from_user(&xfer, u, sizeof(xfer)))
            return -EFAULT;
        xfer.value = 0; /* TODO: actual bus read */
        if (copy_to_user(u, &xfer, sizeof(xfer)))
            return -EFAULT;
        return 0;
    case NEXUS_BUS_IOCTL_WRITE:
        if (copy_from_user(&xfer, u, sizeof(xfer)))
            return -EFAULT;
        dev_info(&dev->pdev->dev, "Write bus=%d id=%d addr=0x%x reg=0x%x val=0x%x\n",
                 xfer.bus_type, xfer.bus_id, xfer.addr, xfer.reg, xfer.value);
        return 0;
    default:
        return -ENOTTY;
    }
}
static const struct file_operations nexus_bus_fops = {
    .owner = THIS_MODULE,
    .open = nexus_bus_open,
    .unlocked_ioctl = nexus_bus_ioctl,
    .llseek = no_llseek,
};
static int nexus_bus_probe(struct platform_device *pdev)
{
    struct nexus_bus_dev *dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;
    dev->pdev = pdev;
    platform_set_drvdata(pdev, dev);
    int r = alloc_chrdev_region(&dev->devt, 0, 1, DRV_NAME);
    if (r)
        return dev_err_probe(&pdev->dev, r, "chrdev\n");
    cdev_init(&dev->cdev, &nexus_bus_fops);
    dev->cdev.owner = THIS_MODULE;
    r = cdev_add(&dev->cdev, dev->devt, 1);
    if (r)
    {
        unregister_chrdev_region(dev->devt, 1);
        return r;
    }
    dev->dev = device_create(dev->class, &pdev->dev, dev->devt, dev, DRV_NAME "%u", 0);
    if (IS_ERR(dev->dev))
    {
        cdev_del(&dev->cdev);
        unregister_chrdev_region(dev->devt, 1);
        return PTR_ERR(dev->dev);
    }
    dev_info(&pdev->dev, "Nexus Bus v%s loaded\n", DRV_VERSION);
    return 0;
}
static void nexus_bus_remove(struct platform_device *pdev)
{
    struct nexus_bus_dev *dev = platform_get_drvdata(pdev);
    device_destroy(dev->class, dev->devt);
    cdev_del(&dev->cdev);
    unregister_chrdev_region(dev->devt, 1);
}
static const struct of_device_id nexus_bus_of_match[] = {{.compatible = "nvidia,tegra234-nexus-bus"}, {}};
MODULE_DEVICE_TABLE(of, nexus_bus_of_match);
static struct platform_driver nexus_bus_driver = {.probe = nexus_bus_probe, .remove = nexus_bus_remove, .driver = {.name = DRV_NAME, .of_match_table = nexus_bus_of_match}};
static const struct class nexus_bus_class = {.name = DRV_NAME, .owner = THIS_MODULE};
static int __init nexus_bus_init(void)
{
    int r = class_register(&nexus_bus_class);
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
