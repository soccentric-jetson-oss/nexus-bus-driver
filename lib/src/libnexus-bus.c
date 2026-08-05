#include "libnexus-bus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>

#define NEXUS_BUS_MAGIC 0x4E
#define NEXUS_BUS_IOCTL_READ  _IOWR(NEXUS_BUS_MAGIC, 1, uint32_t[6])
#define NEXUS_BUS_IOCTL_WRITE _IOW(NEXUS_BUS_MAGIC, 2, uint32_t[6])

struct nexus_bus_handle { int fd; };

struct nexus_bus_handle *nexus_bus_open(const char *p) {
    if (!p) { errno = EINVAL; return NULL; }
    int f = open(p, O_RDWR); if (f < 0) return NULL;
    struct nexus_bus_handle *h = calloc(1, sizeof(*h));
    if (!h) { close(f); return NULL; }
    h->fd = f; return h;
}

void nexus_bus_close(struct nexus_bus_handle *h) { if (!h) return; close(h->fd); free(h); }

int nexus_bus_read(struct nexus_bus_handle *h, uint32_t t, uint32_t i, uint32_t a, uint32_t r, uint32_t *v) {
    if (!h || !v) return -EINVAL;
    uint32_t x[6] = {t, i, a, r, 0, 0};
    int e = ioctl(h->fd, NEXUS_BUS_IOCTL_READ, x);
    if (e < 0) return -errno;
    *v = x[4]; return 0;
}

int nexus_bus_write(struct nexus_bus_handle *h, uint32_t t, uint32_t i, uint32_t a, uint32_t r, uint32_t v) {
    if (!h) return -EINVAL;
    uint32_t x[6] = {t, i, a, r, v, 0};
    int e = ioctl(h->fd, NEXUS_BUS_IOCTL_WRITE, x);
    return e < 0 ? -errno : 0;
}
