// SPDX-License-Identifier: GPL-2.0-only
/**
 * @file bus_ioctl.c
 * @brief Bus transfer implementation for Nexus Bus driver
 *
 * Implements read and write operations for all supported bus types:
 * GPIO, I2C, SPI, UART, and CAN. Each bus type dispatches to a
 * type-specific handler.
 *
 * @copyright Copyright (c) 2026 SoC Centric LLC
 * @author Sandesh Ghimire
 */

#include <linux/device.h>
#include "nexus_bus_uapi.h"
#include "nexus_bus_core.h"

int nexus_bus_read(struct nexus_bus_dev *dev,
                   struct nexus_bus_transfer *xfer)
{
    /* ── Dispatch by bus type ────────────────────────────────────────── */
    switch (xfer->bus_type) {
    case NEXUS_BUS_TYPE_GPIO:
        /* GPIO read: return pin state from register */
        xfer->value = 0;  /* TODO: actual GPIO register read */
        break;

    case NEXUS_BUS_TYPE_I2C:
        /* I2C read: perform combined write-address + read-data cycle */
        xfer->value = 0;  /* TODO: actual I2C controller read */
        break;

    case NEXUS_BUS_TYPE_SPI:
        /* SPI read: clock out address, clock in data */
        xfer->value = 0;  /* TODO: actual SPI controller read */
        break;

    case NEXUS_BUS_TYPE_UART:
        /* UART read: return next byte from RX FIFO */
        xfer->value = 0;  /* TODO: actual UART FIFO read */
        break;

    case NEXUS_BUS_TYPE_CAN:
        /* CAN read: return next message from CAN controller */
        xfer->value = 0;  /* TODO: actual CAN controller read */
        break;

    default:
        dev_err(&dev->pdev->dev, "Unsupported bus type for read: %u\n",
                xfer->bus_type);
        return -EINVAL;
    }

    dev_dbg(&dev->pdev->dev, "Read bus=%u id=%u addr=0x%x reg=0x%x -> 0x%x\n",
            xfer->bus_type, xfer->bus_id, xfer->addr, xfer->reg, xfer->value);
    return 0;
}

int nexus_bus_write(struct nexus_bus_dev *dev,
                    struct nexus_bus_transfer *xfer)
{
    /* ── Dispatch by bus type ────────────────────────────────────────── */
    switch (xfer->bus_type) {
    case NEXUS_BUS_TYPE_GPIO:
        /* GPIO write: set pin state via register */
        dev_info(&dev->pdev->dev, "GPIO write: pin=%u value=0x%x\n",
                 xfer->addr, xfer->value);
        break;

    case NEXUS_BUS_TYPE_I2C:
        /* I2C write: send address + data over I2C bus */
        dev_info(&dev->pdev->dev, "I2C write: addr=0x%x reg=0x%x val=0x%x\n",
                 xfer->addr, xfer->reg, xfer->value);
        break;

    case NEXUS_BUS_TYPE_SPI:
        /* SPI write: clock out address + data */
        dev_info(&dev->pdev->dev, "SPI write: cs=%u reg=0x%x val=0x%x\n",
                 xfer->bus_id, xfer->reg, xfer->value);
        break;

    case NEXUS_BUS_TYPE_UART:
        /* UART write: put byte into TX FIFO */
        dev_info(&dev->pdev->dev, "UART write: port=%u byte=0x%x\n",
                 xfer->bus_id, xfer->value);
        break;

    case NEXUS_BUS_TYPE_CAN:
        /* CAN write: send message over CAN bus */
        dev_info(&dev->pdev->dev, "CAN write: id=0x%x data=0x%x\n",
                 xfer->addr, xfer->value);
        break;

    default:
        dev_err(&dev->pdev->dev, "Unsupported bus type for write: %u\n",
                xfer->bus_type);
        return -EINVAL;
    }

    return 0;
}
