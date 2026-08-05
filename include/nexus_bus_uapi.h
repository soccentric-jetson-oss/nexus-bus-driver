#ifndef NEXUS_BUS_UAPI_H
#define NEXUS_BUS_UAPI_H
#include <linux/types.h>
#include <linux/ioctl.h>
#define NEXUS_BUS_MAGIC 0x4E
#define NEXUS_BUS_TYPE_GPIO 0
#define NEXUS_BUS_TYPE_I2C  1
#define NEXUS_BUS_TYPE_SPI  2
#define NEXUS_BUS_TYPE_UART 3
#define NEXUS_BUS_TYPE_CAN  4
struct nexus_bus_transfer {
    __u32 bus_type; __u32 bus_id; __u32 addr; __u32 reg; __u32 value; __u32 flags; __u64 reserved[4];
};
#define NEXUS_BUS_IOCTL_READ   _IOWR(NEXUS_BUS_MAGIC, 1, struct nexus_bus_transfer)
#define NEXUS_BUS_IOCTL_WRITE  _IOW(NEXUS_BUS_MAGIC, 2, struct nexus_bus_transfer)
#define NEXUS_BUS_IOCTL_GET_INFO _IOR(NEXUS_BUS_MAGIC, 3, __u32)
#endif
