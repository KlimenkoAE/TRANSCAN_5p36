#pragma once
#include <cstdint>

#include "usb.h"

#include "hw_ints.h"


// ============================================================
// USB definitions generated from usb.h
// ============================================================

enum class MyUSB_EP : uint8_t
{
    EP0,
    EP1,
    EP2,
    EP3,
    EP4,
    EP5,
    EP6,
    EP7,
    EP8,
    EP9,
    EP10,
    EP11,
    EP12,
    EP13,
    EP14,
    EP15,
};

static constexpr uint32_t Endpoint(MyUSB_EP ep)
{
    constexpr uint32_t mask[] =
    {
        USB_EP_0,
        USB_EP_1,
        USB_EP_2,
        USB_EP_3,
        USB_EP_4,
        USB_EP_5,
        USB_EP_6,
        USB_EP_7,
        USB_EP_8,
        USB_EP_9,
        USB_EP_10,
        USB_EP_11,
        USB_EP_12,
        USB_EP_13,
        USB_EP_14,
        USB_EP_15,
    };
    return mask[static_cast<uint8_t>(ep)];
}

static constexpr uint32_t INTEP_IN(MyUSB_EP ep)
{
    constexpr uint32_t mask[] =
    {
        USB_INTEP_0,
        USB_INTEP_DEV_IN_1,
        USB_INTEP_DEV_IN_2,
        USB_INTEP_DEV_IN_3,
        USB_INTEP_DEV_IN_4,
        USB_INTEP_DEV_IN_5,
        USB_INTEP_DEV_IN_6,
        USB_INTEP_DEV_IN_7,
        USB_INTEP_DEV_IN_8,
        USB_INTEP_DEV_IN_9,
        USB_INTEP_DEV_IN_10,
        USB_INTEP_DEV_IN_11,
        USB_INTEP_DEV_IN_12,
        USB_INTEP_DEV_IN_13,
        USB_INTEP_DEV_IN_14,
        USB_INTEP_DEV_IN_15,
    };
    return mask[static_cast<uint8_t>(ep)];
}

static constexpr uint32_t INTEP_OUT(MyUSB_EP ep)
{
    constexpr uint32_t mask[] =
    {
        USB_INTEP_0,
        USB_INTEP_DEV_OUT_1,
        USB_INTEP_DEV_OUT_2,
        USB_INTEP_DEV_OUT_3,
        USB_INTEP_DEV_OUT_4,
        USB_INTEP_DEV_OUT_5,
        USB_INTEP_DEV_OUT_6,
        USB_INTEP_DEV_OUT_7,
        USB_INTEP_DEV_OUT_8,
        USB_INTEP_DEV_OUT_9,
        USB_INTEP_DEV_OUT_10,
        USB_INTEP_DEV_OUT_11,
        USB_INTEP_DEV_OUT_12,
        USB_INTEP_DEV_OUT_13,
        USB_INTEP_DEV_OUT_14,
        USB_INTEP_DEV_OUT_15,
    };
    return mask[static_cast<uint8_t>(ep)];
}

enum class MyUSB_INTCTRL : uint8_t
{
    ALL,
    STATUS,
    VBUS_ERR,
    SESSION,
    SESSION_END,
    DISCONNECT,
    CONNECT,
    SOF,
    BABBLE,
    RESET,
    RESUME,
    SUSPEND,
    MODE_DETECT,
    POWER_FAULT,
};

static constexpr uint32_t INTCTRL_TABLE[] =
{
    USB_INTCTRL_ALL,
    USB_INTCTRL_STATUS,
    USB_INTCTRL_VBUS_ERR,
    USB_INTCTRL_SESSION,
    USB_INTCTRL_SESSION_END,
    USB_INTCTRL_DISCONNECT,
    USB_INTCTRL_CONNECT,
    USB_INTCTRL_SOF,
    USB_INTCTRL_BABBLE,
    USB_INTCTRL_RESET,
    USB_INTCTRL_RESUME,
    USB_INTCTRL_SUSPEND,
    USB_INTCTRL_MODE_DETECT,
    USB_INTCTRL_POWER_FAULT,
};

static constexpr uint32_t INTCTRL(MyUSB_INTCTRL flag)
{
    return INTCTRL_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSB_EP_CFG : uint8_t
{
    AUTO_SET,
    AUTO_REQUEST,
    AUTO_CLEAR,
    DMA_MODE_0,
    DMA_MODE_1,
    MODE_ISOC,
    MODE_BULK,
    MODE_INT,
    MODE_CTRL,
    MODE_MASK,
    SPEED_LOW,
    SPEED_FULL,
    HOST_IN,
    HOST_OUT,
    DEV_IN,
    DEV_OUT,
};

static constexpr uint32_t EP_CFG_TABLE[] =
{
    USB_EP_AUTO_SET,
    USB_EP_AUTO_REQUEST,
    USB_EP_AUTO_CLEAR,
    USB_EP_DMA_MODE_0,
    USB_EP_DMA_MODE_1,
    USB_EP_MODE_ISOC,
    USB_EP_MODE_BULK,
    USB_EP_MODE_INT,
    USB_EP_MODE_CTRL,
    USB_EP_MODE_MASK,
    USB_EP_SPEED_LOW,
    USB_EP_SPEED_FULL,
    USB_EP_HOST_IN,
    USB_EP_HOST_OUT,
    USB_EP_DEV_IN,
    USB_EP_DEV_OUT,
};

static constexpr uint32_t EP_CFG(MyUSB_EP_CFG flag)
{
    return EP_CFG_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSB_FIFO_SIZE : uint8_t
{
    SZ_8,
    SZ_16,
    SZ_32,
    SZ_64,
    SZ_128,
    SZ_256,
    SZ_512,
    SZ_1024,
    SZ_2048,
    SZ_4096,
    SZ_8_DB,
    SZ_16_DB,
    SZ_32_DB,
    SZ_64_DB,
    SZ_128_DB,
    SZ_256_DB,
    SZ_512_DB,
    SZ_1024_DB,
    SZ_2048_DB,
};

static constexpr uint32_t FIFO_SIZE_TABLE[] =
{
    USB_FIFO_SZ_8,
    USB_FIFO_SZ_16,
    USB_FIFO_SZ_32,
    USB_FIFO_SZ_64,
    USB_FIFO_SZ_128,
    USB_FIFO_SZ_256,
    USB_FIFO_SZ_512,
    USB_FIFO_SZ_1024,
    USB_FIFO_SZ_2048,
    USB_FIFO_SZ_4096,
    USB_FIFO_SZ_8_DB,
    USB_FIFO_SZ_16_DB,
    USB_FIFO_SZ_32_DB,
    USB_FIFO_SZ_64_DB,
    USB_FIFO_SZ_128_DB,
    USB_FIFO_SZ_256_DB,
    USB_FIFO_SZ_512_DB,
    USB_FIFO_SZ_1024_DB,
    USB_FIFO_SZ_2048_DB,
};

static constexpr uint32_t FIFO_SIZE(MyUSB_FIFO_SIZE flag)
{
    return FIFO_SIZE_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSB_TRANS : uint8_t
{
    OUT,
    IN,
    IN_LAST,
    SETUP,
    STATUS,
};

static constexpr uint32_t TRANS_TABLE[] =
{
    USB_TRANS_OUT,
    USB_TRANS_IN,
    USB_TRANS_IN_LAST,
    USB_TRANS_SETUP,
    USB_TRANS_STATUS,
};

static constexpr uint32_t TRANS(MyUSB_TRANS flag)
{
    return TRANS_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSB_SPEED : uint8_t
{
    UNDEF,
    FULL,
    LOW,
};

static constexpr uint32_t SPEED(MyUSB_SPEED speed)
{
    constexpr uint32_t mask[] =
    {
        USB_UNDEF_SPEED,
        USB_FULL_SPEED,
        USB_LOW_SPEED,
    };
    return mask[static_cast<uint8_t>(speed)];
}

enum class MyUSB_EP_STATUS : uint8_t
{
    RX_SENT_STALL,
    RX_DATA_ERROR,
    RX_OVERRUN,
    RX_FIFO_FULL,
    RX_PKT_RDY,
    TX_NOT_COMP,
    TX_SENT_STALL,
    TX_UNDERRUN,
    TX_FIFO_NE,
    TX_TXPKTRDY,
    EP0_SETUP_END,
    EP0_SENT_STALL,
    EP0_IN_PKTPEND,
    EP0_OUT_PKTRDY,
};

static constexpr uint32_t EP_STATUS_TABLE[] =
{
    USB_DEV_RX_SENT_STALL,
    USB_DEV_RX_DATA_ERROR,
    USB_DEV_RX_OVERRUN,
    USB_DEV_RX_FIFO_FULL,
    USB_DEV_RX_PKT_RDY,
    USB_DEV_TX_NOT_COMP,
    USB_DEV_TX_SENT_STALL,
    USB_DEV_TX_UNDERRUN,
    USB_DEV_TX_FIFO_NE,
    USB_DEV_TX_TXPKTRDY,
    USB_DEV_EP0_SETUP_END,
    USB_DEV_EP0_SENT_STALL,
    USB_DEV_EP0_IN_PKTPEND,
    USB_DEV_EP0_OUT_PKTRDY,
};

static constexpr uint32_t EP_STATUS(MyUSB_EP_STATUS flag)
{
    return EP_STATUS_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSB_INT : uint8_t
{
    ALL,
    STATUS,
    VBUS_ERR,
    SESSION_START,
    SESSION_END,
    DISCONNECT,
    CONNECT,
    SOF,
    BABBLE,
    RESET,
    RESUME,
    SUSPEND,
    MODE_DETECT,
    POWER_FAULT,
    HOST_IN,
    DEV_OUT,
    HOST_IN_EP3,
    HOST_IN_EP2,
    HOST_IN_EP1,
    DEV_OUT_EP3,
    DEV_OUT_EP2,
    DEV_OUT_EP1,
    HOST_OUT,
    DEV_IN,
    HOST_OUT_EP3,
    HOST_OUT_EP2,
    HOST_OUT_EP1,
    DEV_IN_EP3,
    DEV_IN_EP2,
    DEV_IN_EP1,
    EP0,
};

static constexpr uint32_t INT_TABLE[] =
{
    USB_INT_ALL,
    USB_INT_STATUS,
    USB_INT_VBUS_ERR,
    USB_INT_SESSION_START,
    USB_INT_SESSION_END,
    USB_INT_DISCONNECT,
    USB_INT_CONNECT,
    USB_INT_SOF,
    USB_INT_BABBLE,
    USB_INT_RESET,
    USB_INT_RESUME,
    USB_INT_SUSPEND,
    USB_INT_MODE_DETECT,
    USB_INT_POWER_FAULT,
    USB_INT_HOST_IN,
    USB_INT_DEV_OUT,
    USB_INT_HOST_IN_EP3,
    USB_INT_HOST_IN_EP2,
    USB_INT_HOST_IN_EP1,
    USB_INT_DEV_OUT_EP3,
    USB_INT_DEV_OUT_EP2,
    USB_INT_DEV_OUT_EP1,
    USB_INT_HOST_OUT,
    USB_INT_DEV_IN,
    USB_INT_HOST_OUT_EP3,
    USB_INT_HOST_OUT_EP2,
    USB_INT_HOST_OUT_EP1,
    USB_INT_DEV_IN_EP3,
    USB_INT_DEV_IN_EP2,
    USB_INT_DEV_IN_EP1,
    USB_INT_EP0,
};

static constexpr uint32_t INT(MyUSB_INT flag)
{
    return INT_TABLE[static_cast<uint8_t>(flag)];
}


// ============================================================
// USB registers
// ============================================================

enum class MyUSB_REG : uint8_t
{
    POWER,
    TXIS,
    RXIS,
    TXIE,
    RXIE,
    IS,
    IE,
    FRAME,
    EPIDX,
    TEST,
    TXFIFOSZ,
    RXFIFOSZ,
    TXFIFOADD,
    RXFIFOADD,
    CONTIM,
    FSEOF,
    LSEOF,
    RXDPKTBUFDIS,
    TXDPKTBUFDIS,
    DRRIS,
    DRIM,
    DRISC,
    DMASEL,
};

static constexpr uint32_t USB_REGS[] =
{
    0x0001, // POWER
    0x0002, // TXIS
    0x0004, // RXIS
    0x0006, // TXIE
    0x0008, // RXIE
    0x000A, // IS
    0x000B, // IE
    0x000C, // FRAME
    0x000E, // EPIDX
    0x000F, // TEST
    0x0062, // TXFIFOSZ
    0x0063, // RXFIFOSZ
    0x0064, // TXFIFOADD
    0x0066, // RXFIFOADD
    0x007A, // CONTIM
    0x007D, // FSEOF
    0x007E, // LSEOF
    0x0340, // RXDPKTBUFDIS
    0x0342, // TXDPKTBUFDIS
    0x0410, // DRRIS
    0x0414, // DRIM
    0x0418, // DRISC
    0x0450, // DMASEL
};

static constexpr uint32_t USB_REG(MyUSB_REG reg)
{
    return USB_REGS[static_cast<uint8_t>(reg)];
}


// ============================================================
// USB endpoint registers
// ============================================================

enum class MyUSB_EP_REG : uint8_t
{
    COUNT,
    CSRH,
    CSRL,
    FIFO,
    RXCOUNT,
    RXCSRH,
    RXCSRL,
    RXMAXP,
    TXCSRH,
    TXCSRL,
    TXMAXP,
};

static constexpr uint32_t USB_EP_REGS[][11] =
{
    { 0x0108, 0x0103, 0x0102, 0x0020, 0, 0, 0, 0, 0, 0, 0 }, // EP0
    { 0, 0, 0, 0x0024, 0x0118, 0x0117, 0x0116, 0x0114, 0x0113, 0x0112, 0x0110 }, // EP1
    { 0, 0, 0, 0x0028, 0x0128, 0x0127, 0x0126, 0x0124, 0x0123, 0x0122, 0x0120 }, // EP2
    { 0, 0, 0, 0x002C, 0x0138, 0x0137, 0x0136, 0x0134, 0x0133, 0x0132, 0x0130 }, // EP3
    { 0, 0, 0, 0x0030, 0x0148, 0x0147, 0x0146, 0x0144, 0x0143, 0x0142, 0x0140 }, // EP4
    { 0, 0, 0, 0x0034, 0x0158, 0x0157, 0x0156, 0x0154, 0x0153, 0x0152, 0x0150 }, // EP5
    { 0, 0, 0, 0x0038, 0x0168, 0x0167, 0x0166, 0x0164, 0x0163, 0x0162, 0x0160 }, // EP6
    { 0, 0, 0, 0x003C, 0x0178, 0x0177, 0x0176, 0x0174, 0x0173, 0x0172, 0x0170 }, // EP7
    { 0, 0, 0, 0x0040, 0x0188, 0x0187, 0x0186, 0x0184, 0x0183, 0x0182, 0x0180 }, // EP8
    { 0, 0, 0, 0x0044, 0x0198, 0x0197, 0x0196, 0x0194, 0x0193, 0x0192, 0x0190 }, // EP9
    { 0, 0, 0, 0x0048, 0x01A8, 0x01A7, 0x01A6, 0x01A4, 0x01A3, 0x01A2, 0x01A0 }, // EP10
    { 0, 0, 0, 0x004C, 0x01B8, 0x01B7, 0x01B6, 0x01B4, 0x01B3, 0x01B2, 0x01B0 }, // EP11
    { 0, 0, 0, 0x0050, 0x01C8, 0x01C7, 0x01C6, 0x01C4, 0x01C3, 0x01C2, 0x01C0 }, // EP12
    { 0, 0, 0, 0x0054, 0x01D8, 0x01D7, 0x01D6, 0x01D4, 0x01D3, 0x01D2, 0x01D0 }, // EP13
    { 0, 0, 0, 0x0058, 0x01E8, 0x01E7, 0x01E6, 0x01E4, 0x01E3, 0x01E2, 0x01E0 }, // EP14
    { 0, 0, 0, 0x005C, 0x01F8, 0x01F7, 0x01F6, 0x01F4, 0x01F3, 0x01F2, 0x01F0 }, // EP15
};

static constexpr uint32_t EP_REG(MyUSB_EP ep, MyUSB_EP_REG reg)
{
    return USB_EP_REGS[static_cast<uint8_t>(ep)][static_cast<uint8_t>(reg)];
}

static constexpr uint32_t COUNT(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::COUNT);
}

static constexpr uint32_t CSRH(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::CSRH);
}

static constexpr uint32_t CSRL(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::CSRL);
}

static constexpr uint32_t FIFO(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::FIFO);
}

static constexpr uint32_t RXCOUNT(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::RXCOUNT);
}

static constexpr uint32_t RXCSRH(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::RXCSRH);
}

static constexpr uint32_t RXCSRL(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::RXCSRL);
}

static constexpr uint32_t RXMAXP(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::RXMAXP);
}

static constexpr uint32_t TXCSRH(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::TXCSRH);
}

static constexpr uint32_t TXCSRL(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::TXCSRL);
}

static constexpr uint32_t TXMAXP(MyUSB_EP ep)
{
    return EP_REG(ep, MyUSB_EP_REG::TXMAXP);
}


// ============================================================
// Interrupt definitions generated from hw_ints.h
// ============================================================

enum class MyFAULT : uint8_t
{
    NMI,
    HARD,
    MPU,
    BUS,
    USAGE,
    SVCALL,
    DEBUG,
    PENDSV,
    SYSTICK,
};

static constexpr uint32_t FAULT(MyFAULT flag)
{
    constexpr uint32_t mask[] =
    {
        FAULT_NMI,
        FAULT_HARD,
        FAULT_MPU,
        FAULT_BUS,
        FAULT_USAGE,
        FAULT_SVCALL,
        FAULT_DEBUG,
        FAULT_PENDSV,
        FAULT_SYSTICK,
    };
    return mask[static_cast<uint8_t>(flag)];
}

enum class MyINT : uint8_t
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    UART0,
    UART1,
    SSI0,
    I2C0,
    PWM0_FAULT,
    PWM0_0,
    PWM0_1,
    PWM0_2,
    QEI0,
    ADC0SS0,
    ADC0SS1,
    ADC0SS2,
    ADC0SS3,
    WATCHDOG,
    TIMER0A,
    TIMER0B,
    TIMER1A,
    TIMER1B,
    TIMER2A,
    TIMER2B,
    COMP0,
    COMP1,
    COMP2,
    SYSCTL,
    FLASH,
    GPIOF,
    GPIOG,
    GPIOH,
    UART2,
    SSI1,
    TIMER3A,
    TIMER3B,
    I2C1,
    QEI1,
    CAN0,
    CAN1,
    CAN2,
    ETH,
    HIBERNATE,
    USB0,
    PWM0_3,
    UDMA,
    UDMAERR,
    ADC1SS0,
    ADC1SS1,
    ADC1SS2,
    ADC1SS3,
    I2S0,
    EPI0,
    GPIOJ,
    GPIOK,
    GPIOL,
    SSI2,
    SSI3,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
    I2C2,
    I2C3,
    TIMER4A,
    TIMER4B,
    TIMER5A,
    TIMER5B,
    WTIMER0A,
    WTIMER0B,
    WTIMER1A,
    WTIMER1B,
    WTIMER2A,
    WTIMER2B,
    WTIMER3A,
    WTIMER3B,
    WTIMER4A,
    WTIMER4B,
    WTIMER5A,
    WTIMER5B,
    SYSEXC,
    PECI0,
    LPC0,
    I2C4,
    I2C5,
    GPIOM,
    GPION,
    FAN0,
    GPIOP0,
    GPIOP1,
    GPIOP2,
    GPIOP3,
    GPIOP4,
    GPIOP5,
    GPIOP6,
    GPIOP7,
    GPIOQ0,
    GPIOQ1,
    GPIOQ2,
    GPIOQ3,
    GPIOQ4,
    GPIOQ5,
    GPIOQ6,
    GPIOQ7,
    PWM1_0,
    PWM1_1,
    PWM1_2,
    PWM1_3,
    PWM1_FAULT,
};

static constexpr uint32_t INT(MyINT flag)
{
    constexpr uint32_t mask[] =
    {
        INT_GPIOA,
        INT_GPIOB,
        INT_GPIOC,
        INT_GPIOD,
        INT_GPIOE,
        INT_UART0,
        INT_UART1,
        INT_SSI0,
        INT_I2C0,
        INT_PWM0_FAULT,
        INT_PWM0_0,
        INT_PWM0_1,
        INT_PWM0_2,
        INT_QEI0,
        INT_ADC0SS0,
        INT_ADC0SS1,
        INT_ADC0SS2,
        INT_ADC0SS3,
        INT_WATCHDOG,
        INT_TIMER0A,
        INT_TIMER0B,
        INT_TIMER1A,
        INT_TIMER1B,
        INT_TIMER2A,
        INT_TIMER2B,
        INT_COMP0,
        INT_COMP1,
        INT_COMP2,
        INT_SYSCTL,
        INT_FLASH,
        INT_GPIOF,
        INT_GPIOG,
        INT_GPIOH,
        INT_UART2,
        INT_SSI1,
        INT_TIMER3A,
        INT_TIMER3B,
        INT_I2C1,
        INT_QEI1,
        INT_CAN0,
        INT_CAN1,
        INT_CAN2,
        INT_ETH,
        INT_HIBERNATE,
        INT_USB0,
        INT_PWM0_3,
        INT_UDMA,
        INT_UDMAERR,
        INT_ADC1SS0,
        INT_ADC1SS1,
        INT_ADC1SS2,
        INT_ADC1SS3,
        INT_I2S0,
        INT_EPI0,
        INT_GPIOJ,
        INT_GPIOK,
        INT_GPIOL,
        INT_SSI2,
        INT_SSI3,
        INT_UART3,
        INT_UART4,
        INT_UART5,
        INT_UART6,
        INT_UART7,
        INT_I2C2,
        INT_I2C3,
        INT_TIMER4A,
        INT_TIMER4B,
        INT_TIMER5A,
        INT_TIMER5B,
        INT_WTIMER0A,
        INT_WTIMER0B,
        INT_WTIMER1A,
        INT_WTIMER1B,
        INT_WTIMER2A,
        INT_WTIMER2B,
        INT_WTIMER3A,
        INT_WTIMER3B,
        INT_WTIMER4A,
        INT_WTIMER4B,
        INT_WTIMER5A,
        INT_WTIMER5B,
        INT_SYSEXC,
        INT_PECI0,
        INT_LPC0,
        INT_I2C4,
        INT_I2C5,
        INT_GPIOM,
        INT_GPION,
        INT_FAN0,
        INT_GPIOP0,
        INT_GPIOP1,
        INT_GPIOP2,
        INT_GPIOP3,
        INT_GPIOP4,
        INT_GPIOP5,
        INT_GPIOP6,
        INT_GPIOP7,
        INT_GPIOQ0,
        INT_GPIOQ1,
        INT_GPIOQ2,
        INT_GPIOQ3,
        INT_GPIOQ4,
        INT_GPIOQ5,
        INT_GPIOQ6,
        INT_GPIOQ7,
        INT_PWM1_0,
        INT_PWM1_1,
        INT_PWM1_2,
        INT_PWM1_3,
        INT_PWM1_FAULT,
    };
    return mask[static_cast<uint8_t>(flag)];
}

static constexpr uint32_t NumInterrupts = 155;
static constexpr uint32_t NumPriority = 8;
static constexpr uint32_t NumPriorityBits = 3;

