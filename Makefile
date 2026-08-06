DRV_NAME := nexus-bus
DRV_VERSION := 0.1.0
CC ?= gcc
CFLAGS := -O2 -Wall -Wextra
INCLUDES := -Ilib/include -Iinclude
BUILD_DIR := build
KDIR ?= /lib/modules/$(shell uname -r)/build
ARCH ?= $(shell uname -m | sed s/aarch64/arm64/ | sed s/x86_64/x86_64/)
CROSS_COMPILE ?=

# Source files
LIB_SRC := lib/src/lib$(DRV_NAME).c

all: module lib test

# ── Kernel module ──────────────────────────────────────────────────────
module:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

module_clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean

# ── Userspace library ─────────────────────────────────────────────────
lib: $(BUILD_DIR)/lib$(DRV_NAME).so $(BUILD_DIR)/lib$(DRV_NAME).a

$(BUILD_DIR)/lib$(DRV_NAME).o: $(LIB_SRC) include/nexus_bus_uapi.h include/nexus_bus_core.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/lib$(DRV_NAME).so: $(BUILD_DIR)/lib$(DRV_NAME).o
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/lib$(DRV_NAME).a: $(BUILD_DIR)/lib$(DRV_NAME).o
	ar rcs $@ $^

test: $(BUILD_DIR)/$(DRV_NAME)_test
	LD_LIBRARY_PATH=$(BUILD_DIR) $<

$(BUILD_DIR)/$(DRV_NAME)_test: test/$(DRV_NAME)_test.c $(BUILD_DIR)/lib$(DRV_NAME).a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -L$(BUILD_DIR) -l$(DRV_NAME) -lpthread

clean: module_clean
	rm -rf $(BUILD_DIR)
