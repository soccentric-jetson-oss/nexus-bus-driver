savedcmd_nexus-bus.mod := printf '%s\n'   src/main.o src/bus_ioctl.o src/chardev.o | awk '!x[$$0]++ { print("./"$$0) }' > nexus-bus.mod
