# Yocto/Buildroot Integration

## Yocto Recipe
```
inherit module
SRC_URI = "git://github.com/soccentric-jetson-oss/nexus-bus-driver.git;branch=main"
S = "${WORKDIR}/git"
```

## Buildroot Package
```
NEXUS_BUS_DRIVER_VERSION = 0.1.0
NEXUS_BUS_DRIVER_SITE = git://github.com/soccentric-jetson-oss/nexus-bus-driver.git
$(eval $(kernel-module))
```

## Cross-Compilation
```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- KDIR=/path/to/kernel
```
