# SPDX-License-Identifier: GPL-2.0-only
#
# Kbuild - kernel module build description for nexus-bus
#

obj-m += nexus-bus.o

nexus-bus-y := src/main.o \
               src/bus_ioctl.o \
               src/chardev.o

ccflags-y := -I$(src)/include
