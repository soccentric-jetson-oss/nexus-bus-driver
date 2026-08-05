#ifndef LIBNEXUS_BUS_H
#define LIBNEXUS_BUS_H
#include <stdint.h>

/* Bus types */
#define NEXUS_BUS_TYPE_GPIO 0
#define NEXUS_BUS_TYPE_I2C  1
#define NEXUS_BUS_TYPE_SPI  2
#define NEXUS_BUS_TYPE_UART 3
#define NEXUS_BUS_TYPE_CAN  4

#ifdef __cplusplus
extern "C" {
#endif
struct nexus_bus_handle;
struct nexus_bus_handle *nexus_bus_open(const char *path);
void nexus_bus_close(struct nexus_bus_handle *h);
int nexus_bus_read(struct nexus_bus_handle *h, uint32_t type, uint32_t id, uint32_t addr, uint32_t reg, uint32_t *value);
int nexus_bus_write(struct nexus_bus_handle *h, uint32_t type, uint32_t id, uint32_t addr, uint32_t reg, uint32_t value);
#ifdef __cplusplus
}
#endif
#endif
