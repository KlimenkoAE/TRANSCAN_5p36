#pragma once
#include <cstdint>


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
        0x00000000,//USB_EP_0
        0x00000010,//USB_EP_1
        0x00000020,//USB_EP_2
        0x00000030,//USB_EP_3
        0x00000040,//USB_EP_4
        0x00000050,//USB_EP_5
        0x00000060,//USB_EP_6
        0x00000070,//USB_EP_7
        0x00000080,//USB_EP_8
        0x00000090,//USB_EP_9
        0x000000A0,//USB_EP_10
        0x000000B0,//USB_EP_11
        0x000000C0,//USB_EP_12
        0x000000D0,//USB_EP_13
        0x000000E0,//USB_EP_14
        0x000000F0,//USB_EP_15
    };
    return mask[static_cast<uint8_t>(ep)];
}

static constexpr uint32_t INTEP_IN(MyUSB_EP ep)
{
    constexpr uint32_t mask[] =
    {
        0x00000000,//USB_INTEP_0
        0x00000002,//INTEP_DEV_IN_1
        0x00000004,//INTEP_DEV_IN_2
        0x00000008,//INTEP_DEV_IN_3
        0x00000010,//INTEP_DEV_IN_4
        0x00000020,//INTEP_DEV_IN_5
        0x00000040,//INTEP_DEV_IN_6
        0x00000080,//INTEP_DEV_IN_7
        0x00000100,//INTEP_DEV_IN_8
        0x00000200,//INTEP_DEV_IN_9
        0x00000400,//INTEP_DEV_IN_10
        0x00000800,//INTEP_DEV_IN_11
        0x00001000,//INTEP_DEV_IN_12
        0x00002000,//INTEP_DEV_IN_13
        0x00004000,//INTEP_DEV_IN_14
        0x00008000,//INTEP_DEV_IN_15
    };
    return mask[static_cast<uint8_t>(ep)];
}

static constexpr uint32_t INTEP_OUT(MyUSB_EP ep)
{
    constexpr uint32_t mask[] =
    {
         0x00000000,//USB_INTEP_0
         0x00020000,//INTEP_DEV_OUT_1
         0x00040000,//INTEP_DEV_OUT_2
         0x00080000,//INTEP_DEV_OUT_3
         0x00100000,//INTEP_DEV_OUT_4
         0x00200000,//INTEP_DEV_OUT_5
         0x00400000,//INTEP_DEV_OUT_6
         0x00800000,//INTEP_DEV_OUT_7
         0x01000000,//INTEP_DEV_OUT_8
         0x02000000,//INTEP_DEV_OUT_9
         0x04000000,//INTEP_DEV_OUT_10
         0x08000000,//INTEP_DEV_OUT_11
         0x10000000,//INTEP_DEV_OUT_12
         0x20000000,//INTEP_DEV_OUT_13
         0x40000000,//INTEP_DEV_OUT_14
         0x80000000,//INTEP_DEV_OUT_15
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
    0x000003FF,//USB_INTCTRL_ALL
    0x000000FF,//USB_INTCTRL_STATUS
    0x00000080,//USB_INTCTRL_VBUS_ERR
    0x00000040,//USB_INTCTRL_SESSION
    0x00000040,//USB_INTCTRL_SESSION_END
    0x00000020,//USB_INTCTRL_DISCONNECT
    0x00000010,//USB_INTCTRL_CONNECT
    0x00000008,//USB_INTCTRL_SOF
    0x00000004,//USB_INTCTRL_BABBLE
    0x00000004,//USB_INTCTRL_RESET
    0x00000002,//USB_INTCTRL_RESUME
    0x00000001,//USB_INTCTRL_SUSPEND
    0x00000200,//USB_INTCTRL_MODE_DETECT
    0x00000100,//USB_INTCTRL_POWER_FAULT
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
    0x00000001,//USB_EP_AUTO_SET
    0x00000002,//USB_EP_AUTO_REQUEST
    0x00000004,//USB_EP_AUTO_CLEAR
    0x00000008,//USB_EP_DMA_MODE_0
    0x00000010,//USB_EP_DMA_MODE_1
    0x00000000,//USB_EP_MODE_ISOC
    0x00000100,//USB_EP_MODE_BULK
    0x00000200,//USB_EP_MODE_INT
    0x00000300,//USB_EP_MODE_CTRL
    0x00000300,//USB_EP_MODE_MASK
    0x00000000,//USB_EP_SPEED_LOW
    0x00001000,//USB_EP_SPEED_FULL
    0x00000000,//USB_EP_HOST_IN
    0x00002000,//USB_EP_HOST_OUT
    0x00002000,//USB_EP_DEV_IN
    0x00000000,//USB_EP_DEV_OUT
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
    0x00000000,//USB_FIFO_SZ_8
    0x00000001,//USB_FIFO_SZ_16
    0x00000002,//USB_FIFO_SZ_32
    0x00000003,//USB_FIFO_SZ_64
    0x00000004,//USB_FIFO_SZ_128
    0x00000005,//USB_FIFO_SZ_256
    0x00000006,//USB_FIFO_SZ_512
    0x00000007,//USB_FIFO_SZ_1024
    0x00000008,//USB_FIFO_SZ_2048
    0x00000009,//USB_FIFO_SZ_4096
    0x00000010,//USB_FIFO_SZ_8_DB
    0x00000011,//USB_FIFO_SZ_16_DB
    0x00000012,//USB_FIFO_SZ_32_DB
    0x00000013,//USB_FIFO_SZ_64_DB
    0x00000014,//USB_FIFO_SZ_128_DB
    0x00000015,//USB_FIFO_SZ_256_DB
    0x00000016,//USB_FIFO_SZ_512_DB
    0x00000017,//USB_FIFO_SZ_1024_DB
    0x00000018,//USB_FIFO_SZ_2048_DB
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
    0x00000102,//USB_TRANS_OUT
    0x00000102,//USB_TRANS_IN
    0x0000010a,//USB_TRANS_IN_LAST
    0x0000110a,//USB_TRANS_SETUP
    0x00000142,//USB_TRANS_STATUS
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
        0x80000000,//USB_UNDEF_SPEED
        0x00000001,//USB_FULL_SPEED
        0x00000000,//USB_LOW_SPEED
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
    0x00400000,//USB_DEV_RX_SENT_STALL
    0x00080000,//USB_DEV_RX_DATA_ERROR
    0x00040000,//USB_DEV_RX_OVERRUN
    0x00020000,//USB_DEV_RX_FIFO_FULL
    0x00010000,//USB_DEV_RX_PKT_RDY
    0x00000080,//USB_DEV_TX_NOT_COMP
    0x00000020,//USB_DEV_TX_SENT_STALL
    0x00000004,//USB_DEV_TX_UNDERRUN
    0x00000002,//USB_DEV_TX_FIFO_NE
    0x00000001,//USB_DEV_TX_TXPKTRDY
    0x00000010,//USB_DEV_EP0_SETUP_END
    0x00000004,//USB_DEV_EP0_SENT_STALL
    0x00000002,//USB_DEV_EP0_IN_PKTPEND
    0x00000001,//USB_DEV_EP0_OUT_PKTRDY
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
    0xFF030E0F,//USB_INT_ALL
    0xFF000000,//USB_INT_STATUS
    0x80000000,//USB_INT_VBUS_ERR
    0x40000000,//USB_INT_SESSION_START
    0x20000000,//USB_INT_SESSION_END
    0x20000000,//USB_INT_DISCONNECT
    0x10000000,//USB_INT_CONNECT
    0x08000000,//USB_INT_SOF
    0x04000000,//USB_INT_BABBLE
    0x04000000,//USB_INT_RESET
    0x02000000,//USB_INT_RESUME
    0x01000000,//USB_INT_SUSPEND
    0x00020000,//USB_INT_MODE_DETECT
    0x00010000,//USB_INT_POWER_FAULT
    0x00000E00,//USB_INT_HOST_IN
    0x00000E00,//USB_INT_DEV_OUT
    0x00000800,//USB_INT_HOST_IN_EP3
    0x00000400,//USB_INT_HOST_IN_EP2
    0x00000200,//USB_INT_HOST_IN_EP1
    0x00000800,//USB_INT_DEV_OUT_EP3
    0x00000400,//USB_INT_DEV_OUT_EP2
    0x00000200,//USB_INT_DEV_OUT_EP1
    0x0000000E,//USB_INT_HOST_OUT
    0x0000000E,//USB_INT_DEV_IN
    0x00000008,//USB_INT_HOST_OUT_EP3
    0x00000004,//USB_INT_HOST_OUT_EP2
    0x00000002,//USB_INT_HOST_OUT_EP1
    0x00000008,//USB_INT_DEV_IN_EP3
    0x00000004,//USB_INT_DEV_IN_EP2
    0x00000002,//USB_INT_DEV_IN_EP1
    0x00000001,//USB_INT_EP0
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
    DBG,
    PENDSV,
    SYSTICK,
};

static constexpr uint32_t FAULT(MyFAULT flag)
{
    constexpr uint32_t mask[] =
    {
        2,//FAULT_NMI,
        3,//FAULT_HARD,
        4,//FAULT_MPU,
        5,//FAULT_BUS,
        6,//FAULT_USAGE,
        11,//FAULT_SVCALL,
        12,//FAULT_DEBUG,
        14,//FAULT_PENDSV,
        15,//FAULT_SYSTICK,
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
        16,//INT_GPIOA,
        17,//INT_GPIOB,
        18,//INT_GPIOC,
        19,//INT_GPIOD,
        20,//INT_GPIOE,
        21,//INT_UART0,
        22,//INT_UART1,
        23,//INT_SSI0,
        24,//INT_I2C0,
        25,//INT_PWM0_FAULT,
        26,//INT_PWM0_0,
        27,//INT_PWM0_1,
        28,//INT_PWM0_2,
        29,//INT_QEI0,
        30,//INT_ADC0SS0,
        31,//INT_ADC0SS1,
        32,//INT_ADC0SS2,
        33,//INT_ADC0SS3,
        34,//INT_WATCHDOG,
        35,//INT_TIMER0A,
        36,//INT_TIMER0B,
        37,//INT_TIMER1A,
        38,//INT_TIMER1B,
        39,//INT_TIMER2A,
        40,//INT_TIMER2B,
        41,//INT_COMP0,
        42,//INT_COMP1,
        43,//INT_COMP2,
        44,//INT_SYSCTL,
        45,//INT_FLASH,
        46,//INT_GPIOF,
        47,//INT_GPIOG,
        48,//INT_GPIOH,
        49,//INT_UART2,
        50,//INT_SSI1,
        51,//INT_TIMER3A,
        52,//INT_TIMER3B,
        53,//INT_I2C1,
        54,//INT_QEI1,
        55,//INT_CAN0,
        56,//INT_CAN1,
        57,//INT_CAN2,
        58,//INT_ETH,
        59,//INT_HIBERNATE,
        60,//INT_USB0,
        61,//INT_PWM0_3,
        62,//INT_UDMA,
        63,//INT_UDMAERR,
        64,//INT_ADC1SS0,
        65,//INT_ADC1SS1,
        66,//INT_ADC1SS2,
        67,//INT_ADC1SS3,
        68,//INT_I2S0,
        69,//INT_EPI0,
        70,//INT_GPIOJ,
        71,//INT_GPIOK,
        72,//INT_GPIOL,
        73,//INT_SSI2,
        74,//INT_SSI3,
        75,//INT_UART3,
        76,//INT_UART4,
        77,//INT_UART5,
        78,//INT_UART6,
        79,//INT_UART7,
        84,//INT_I2C2,
        85,//INT_I2C3,
        86,//INT_TIMER4A,
        87,//INT_TIMER4B,
        108,//INT_TIMER5A,
        109,//INT_TIMER5B,
        110,//INT_WTIMER0A,
        111,//INT_WTIMER0B,
        112,//INT_WTIMER1A,
        113,//INT_WTIMER1B,
        114,//INT_WTIMER2A,
        115,//INT_WTIMER2B,
        116,//INT_WTIMER3A,
        117,//INT_WTIMER3B,
        118,//INT_WTIMER4A,
        119,//INT_WTIMER4B,
        120,//INT_WTIMER5A,
        121,//INT_WTIMER5B,
        122,//INT_SYSEXC,
        123,//INT_PECI0,
        124,//INT_LPC0,
        125,//INT_I2C4,
        126,//INT_I2C5,
        127,//INT_GPIOM,
        128,//INT_GPION,
        130,//INT_FAN0,
        132,//INT_GPIOP0,
        133,//INT_GPIOP1,
        134,//INT_GPIOP2,
        135,//INT_GPIOP3,
        136,//INT_GPIOP4,
        137,//INT_GPIOP5,
        138,//INT_GPIOP6,
        139,//INT_GPIOP7,
        140,//INT_GPIOQ0,
        141,//INT_GPIOQ1,
        142,//INT_GPIOQ2,
        143,//INT_GPIOQ3,
        144,//INT_GPIOQ4,
        145,//INT_GPIOQ5,
        146,//INT_GPIOQ6,
        147,//INT_GPIOQ7,
        150,//INT_PWM1_0,
        151,//INT_PWM1_1,
        152,//INT_PWM1_2,
        153,//INT_PWM1_3,
        154,//INT_PWM1_FAULT,
    };
    return mask[static_cast<uint8_t>(flag)];
}

static constexpr uint32_t NumInterrupts = 155;
static constexpr uint32_t NumPriority = 8;
static constexpr uint32_t NumPriorityBits = 3;


// ============================================================
// Timer definitions generated from timer.h
// ============================================================

enum class MyTIMER : uint8_t
{
    CFG_ONE_SHOT,
    CFG_ONE_SHOT_UP,
    CFG_PERIODIC,
    CFG_PERIODIC_UP,
    CFG_RTC,
    CFG_SPLIT_PAIR,
    CFG_A_ONE_SHOT,
    CFG_A_ONE_SHOT_UP,
    CFG_A_PERIODIC,
    CFG_A_PERIODIC_UP,
    CFG_A_CAP_COUNT,
    CFG_A_CAP_COUNT_UP,
    CFG_A_CAP_TIME,
    CFG_A_CAP_TIME_UP,
    CFG_A_PWM,
    CFG_B_ONE_SHOT,
    CFG_B_ONE_SHOT_UP,
    CFG_B_PERIODIC,
    CFG_B_PERIODIC_UP,
    CFG_B_CAP_COUNT,
    CFG_B_CAP_COUNT_UP,
    CFG_B_CAP_TIME,
    CFG_B_CAP_TIME_UP,
    CFG_B_PWM,
    TIMB_MATCH,
    CAPB_EVENT,
    CAPB_MATCH,
    TIMB_TIMEOUT,
    TIMA_MATCH,
    RTC_MATCH,
    CAPA_EVENT,
    CAPA_MATCH,
    TIMA_TIMEOUT,
    EVENT_POS_EDGE,
    EVENT_NEG_EDGE,
    EVENT_BOTH_EDGES,
    A,
    B,
    BOTH,
    T0A_SYNC,
    T0B_SYNC,
    T1A_SYNC,
    T1B_SYNC,
    T2A_SYNC,
    T2B_SYNC,
    T3A_SYNC,
    T3B_SYNC,
    T4A_SYNC,
    T4B_SYNC,
    T5A_SYNC,
    T5B_SYNC,
};

static constexpr uint32_t TIMER(MyTIMER flag)
{
    constexpr uint32_t mask[] =
    {
        0x00000021,
        0x00000031,
        0x00000022,
        0x00000032,
        0x01000000,
        0x04000000,
        0x00000021,
        0x00000031,
        0x00000022,
        0x00000032,
        0x00000003,
        0x00000013,
        0x00000007,
        0x00000017,
        0x0000000A,
        0x00002100,
        0x00003100,
        0x00002200,
        0x00003200,
        0x00000300,
        0x00001300,
        0x00000700,
        0x00001700,
        0x00000A00,
        0x00000800,
        0x00000400,
        0x00000200,
        0x00000100,
        0x00000010,
        0x00000008,
        0x00000004,
        0x00000002,
        0x00000001,
        0x00000000,
        0x00000404,
        0x00000C0C,
        0x000000ff,
        0x0000ff00,
        0x0000ffff,
        0x00000001,
        0x00000002,
        0x00000004,
        0x00000008,
        0x00000010,
        0x00000020,
        0x00000040,
        0x00000080,
        0x00000100,
        0x00000200,
        0x00000400,
        0x00000800,
    };
    return mask[static_cast<uint8_t>(flag)];
}

enum class MyWTIMER : uint8_t
{
    T0A_SYNC,
    T0B_SYNC,
    T1A_SYNC,
    T1B_SYNC,
    T2A_SYNC,
    T2B_SYNC,
    T3A_SYNC,
    T3B_SYNC,
    T4A_SYNC,
    T4B_SYNC,
    T5A_SYNC,
    T5B_SYNC,
};

static constexpr uint32_t WTIMER(MyWTIMER flag)
{
    constexpr uint32_t mask[] =
    {
        0x00001000,
        0x00002000,
        0x00004000,
        0x00008000,
        0x00010000,
        0x00020000,
        0x00040000,
        0x00080000,
        0x00100000,
        0x00200000,
        0x00400000,
        0x00800000,
    };
    return mask[static_cast<uint8_t>(flag)];
}

// Auto-generated from hw_memmap.h

enum class MyBASE_ADDR : uint8_t
{
    FLASH,
    SRAM,
    WATCHDOG0,
    WATCHDOG1,
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    SSI0,
    SSI1,
    SSI2,
    SSI3,
    UART0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
    I2C0_MASTER,
    I2C0_SLAVE,
    I2C1_MASTER,
    I2C1_SLAVE,
    I2C2_MASTER,
    I2C2_SLAVE,
    I2C3_MASTER,
    I2C3_SLAVE,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
    PWM0,
    PWM1,
    QEI0,
    QEI1,
    TIMER0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
    TIMER5,
    WTIMER0,
    WTIMER1,
    ADC0,
    ADC1,
    COMP,
    GPIOJ,
    CAN0,
    CAN1,
    CAN2,
    ETH,
    MAC,
    WTIMER2,
    WTIMER3,
    WTIMER4,
    WTIMER5,
    USB0,
    I2S0,
    GPIOA_AHB,
    GPIOB_AHB,
    GPIOC_AHB,
    GPIOD_AHB,
    GPIOE_AHB,
    GPIOF_AHB,
    GPIOG_AHB,
    GPIOH_AHB,
    GPIOJ_AHB,
    GPIOK,
    GPIOL,
    GPIOM,
    GPION,
    GPIOP,
    GPIOQ,
    LPC0,
    FAN0,
    EEPROM,
    PECI0,
    I2C4_MASTER,
    I2C4_SLAVE,
    I2C5_MASTER,
    I2C5_SLAVE,
    EPI0,
    SYSEXC,
    HIB,
    FLASH_CTRL,
    SYSCTL,
    UDMA,
    ITM,
    DWT,
    FPB,
    NVIC,
    TPIU,
    WATCHDOG,
    SSI,
    I2C_MASTER,
    I2C_SLAVE,
    PWM,
    QEI,
    ADC,
};

static constexpr uint32_t BASE_ADDR(MyBASE_ADDR p)
{
    constexpr uint32_t base[] = {
        0x00000000, // FLASH
        0x20000000, // SRAM
        0x40000000, // WATCHDOG0
        0x40001000, // WATCHDOG1
        0x40004000, // GPIO_PORTA
        0x40005000, // GPIO_PORTB
        0x40006000, // GPIO_PORTC
        0x40007000, // GPIO_PORTD
        0x40008000, // SSI0
        0x40009000, // SSI1
        0x4000A000, // SSI2
        0x4000B000, // SSI3
        0x4000C000, // UART0
        0x4000D000, // UART1
        0x4000E000, // UART2
        0x4000F000, // UART3
        0x40010000, // UART4
        0x40011000, // UART5
        0x40012000, // UART6
        0x40013000, // UART7
        0x40020000, // I2C0_MASTER
        0x40020800, // I2C0_SLAVE
        0x40021000, // I2C1_MASTER
        0x40021800, // I2C1_SLAVE
        0x40022000, // I2C2_MASTER
        0x40022800, // I2C2_SLAVE
        0x40023000, // I2C3_MASTER
        0x40023800, // I2C3_SLAVE
        0x40024000, // GPIO_PORTE
        0x40025000, // GPIO_PORTF
        0x40026000, // GPIO_PORTG
        0x40027000, // GPIO_PORTH
        0x40028000, // PWM0
        0x40029000, // PWM1
        0x4002C000, // QEI0
        0x4002D000, // QEI1
        0x40030000, // TIMER0
        0x40031000, // TIMER1
        0x40032000, // TIMER2
        0x40033000, // TIMER3
        0x40034000, // TIMER4
        0x40035000, // TIMER5
        0x40036000, // WTIMER0
        0x40037000, // WTIMER1
        0x40038000, // ADC0
        0x40039000, // ADC1
        0x4003C000, // COMP
        0x4003D000, // GPIO_PORTJ
        0x40040000, // CAN0
        0x40041000, // CAN1
        0x40042000, // CAN2
        0x40048000, // ETH
        0x40048000, // MAC
        0x4004C000, // WTIMER2
        0x4004D000, // WTIMER3
        0x4004E000, // WTIMER4
        0x4004F000, // WTIMER5
        0x40050000, // USB0
        0x40054000, // I2S0
        0x40058000, // GPIO_PORTA_AHB
        0x40059000, // GPIO_PORTB_AHB
        0x4005A000, // GPIO_PORTC_AHB
        0x4005B000, // GPIO_PORTD_AHB
        0x4005C000, // GPIO_PORTE_AHB
        0x4005D000, // GPIO_PORTF_AHB
        0x4005E000, // GPIO_PORTG_AHB
        0x4005F000, // GPIO_PORTH_AHB
        0x40060000, // GPIO_PORTJ_AHB
        0x40061000, // GPIO_PORTK
        0x40062000, // GPIO_PORTL
        0x40063000, // GPIO_PORTM
        0x40064000, // GPIO_PORTN
        0x40065000, // GPIO_PORTP
        0x40066000, // GPIO_PORTQ
        0x40080000, // LPC0
        0x40084000, // FAN0
        0x400AF000, // EEPROM
        0x400B0000, // PECI0
        0x400C0000, // I2C4_MASTER
        0x400C0800, // I2C4_SLAVE
        0x400C1000, // I2C5_MASTER
        0x400C1800, // I2C5_SLAVE
        0x400D0000, // EPI0
        0x400F9000, // SYSEXC
        0x400FC000, // HIB
        0x400FD000, // FLASH_CTRL
        0x400FE000, // SYSCTL
        0x400FF000, // UDMA
        0xE0000000, // ITM
        0xE0001000, // DWT
        0xE0002000, // FPB
        0xE000E000, // NVIC
        0xE0040000, // TPIU
        0x40000000, // WATCHDOG
        0x40008000, // SSI
        0x40020000, // I2C_MASTER
        0x40020800, // I2C_SLAVE
        0x40028000, // PWM
        0x4002C000, // QEI
        0x40038000, // ADC
    };
    return base[static_cast<uint8_t>(p)];
}

// ============================================================
// SYSCTL definitions generated from sysctl.h
// ============================================================

enum class MyPERIPH : uint8_t
{
    PERIPH2_ADC0,
    PERIPH2_ADC1,
    PERIPH2_CAN0,
    PERIPH2_CAN1,
    PERIPH2_CAN2,
    PERIPH2_COMP0,
    PERIPH2_EPI0,
    PERIPH2_ETH,
    PERIPH2_GPIOA,
    PERIPH2_GPIOB,
    PERIPH2_GPIOC,
    PERIPH2_GPIOD,
    PERIPH2_GPIOE,
    PERIPH2_GPIOF,
    PERIPH2_GPIOG,
    PERIPH2_GPIOH,
    PERIPH2_GPIOJ,
    PERIPH2_HIB,
    PERIPH2_I2C0,
    PERIPH2_I2C1,
    PERIPH2_I2S0,
    PERIPH2_PWM0,
    PERIPH2_QEI0,
    PERIPH2_QEI1,
    PERIPH2_SSI0,
    PERIPH2_SSI1,
    PERIPH2_TIMER0,
    PERIPH2_TIMER1,
    PERIPH2_TIMER2,
    PERIPH2_TIMER3,
    PERIPH2_UART0,
    PERIPH2_UART1,
    PERIPH2_UART2,
    PERIPH2_UDMA,
    PERIPH2_USB0,
    PERIPH2_WDOG0,
    PERIPH2_WDOG1,
    PERIPH_ADC,
    PERIPH_ADC0,
    PERIPH_ADC1,
    PERIPH_CAN0,
    PERIPH_CAN1,
    PERIPH_CAN2,
    PERIPH_COMP0,
    PERIPH_COMP1,
    PERIPH_COMP2,
    PERIPH_EEPROM0,
    PERIPH_EPI0,
    PERIPH_ETH,
    PERIPH_FAN0,
    PERIPH_GPIOA,
    PERIPH_GPIOB,
    PERIPH_GPIOC,
    PERIPH_GPIOD,
    PERIPH_GPIOE,
    PERIPH_GPIOF,
    PERIPH_GPIOG,
    PERIPH_GPIOH,
    PERIPH_GPIOJ,
    PERIPH_GPIOK,
    PERIPH_GPIOL,
    PERIPH_GPIOM,
    PERIPH_GPION,
    PERIPH_GPIOP,
    PERIPH_GPIOQ,
    PERIPH_GPIOR,
    PERIPH_GPIOS,
    PERIPH_HIBERNATE,
    PERIPH_I2C,
    PERIPH_I2C0,
    PERIPH_I2C1,
    PERIPH_I2C2,
    PERIPH_I2C3,
    PERIPH_I2C4,
    PERIPH_I2C5,
    PERIPH_I2S0,
    PERIPH_IEEE1588,
    PERIPH_LPC0,
    PERIPH_MPU,
    PERIPH_PECI0,
    PERIPH_PLL,
    PERIPH_PWM,
    PERIPH_PWM0,
    PERIPH_PWM1,
    PERIPH_QEI,
    PERIPH_QEI0,
    PERIPH_QEI1,
    PERIPH_SSI,
    PERIPH_SSI0,
    PERIPH_SSI1,
    PERIPH_SSI2,
    PERIPH_SSI3,
    PERIPH_TEMP,
    PERIPH_TIMER0,
    PERIPH_TIMER1,
    PERIPH_TIMER2,
    PERIPH_TIMER3,
    PERIPH_TIMER4,
    PERIPH_TIMER5,
    PERIPH_UART0,
    PERIPH_UART1,
    PERIPH_UART2,
    PERIPH_UART3,
    PERIPH_UART4,
    PERIPH_UART5,
    PERIPH_UART6,
    PERIPH_UART7,
    PERIPH_UDMA,
    PERIPH_USB0,
    PERIPH_WDOG,
    PERIPH_WDOG0,
    PERIPH_WDOG1,
    PERIPH_WTIMER0,
    PERIPH_WTIMER1,
    PERIPH_WTIMER2,
    PERIPH_WTIMER3,
    PERIPH_WTIMER4,
    PERIPH_WTIMER5,
};

static constexpr uint32_t PERIPH_TABLE[] =
{
    0xf0003800, // PERIPH2_ADC0
    0xf0003801, // PERIPH2_ADC1
    0xf0003400, // PERIPH2_CAN0
    0xf0003401, // PERIPH2_CAN1
    0xf0003402, // PERIPH2_CAN2
    0xf0003c00, // PERIPH2_COMP0
    0xf0001000, // PERIPH2_EPI0
    0xf0002c00, // PERIPH2_ETH
    0xf0000800, // PERIPH2_GPIOA
    0xf0000801, // PERIPH2_GPIOB
    0xf0000802, // PERIPH2_GPIOC
    0xf0000803, // PERIPH2_GPIOD
    0xf0000804, // PERIPH2_GPIOE
    0xf0000805, // PERIPH2_GPIOF
    0xf0000806, // PERIPH2_GPIOG
    0xf0000807, // PERIPH2_GPIOH
    0xf0000808, // PERIPH2_GPIOJ
    0xf0001400, // PERIPH2_HIB
    0xf0002000, // PERIPH2_I2C0
    0xf0002001, // PERIPH2_I2C1
    0xf0002400, // PERIPH2_I2S0
    0xf0004000, // PERIPH2_PWM0
    0xf0004400, // PERIPH2_QEI0
    0xf0004401, // PERIPH2_QEI1
    0xf0001c00, // PERIPH2_SSI0
    0xf0001c01, // PERIPH2_SSI1
    0xf0000400, // PERIPH2_TIMER0
    0xf0000401, // PERIPH2_TIMER1
    0xf0000402, // PERIPH2_TIMER2
    0xf0000403, // PERIPH2_TIMER3
    0xf0001800, // PERIPH2_UART0
    0xf0001801, // PERIPH2_UART1
    0xf0001802, // PERIPH2_UART2
    0xf0000c00, // PERIPH2_UDMA
    0xf0002800, // PERIPH2_USB0
    0xf0000000, // PERIPH2_WDOG0
    0xf0000001, // PERIPH2_WDOG1
    0x00100001, // PERIPH_ADC
    0x00100001, // PERIPH_ADC0
    0x00100002, // PERIPH_ADC1
    0x00100100, // PERIPH_CAN0
    0x00100200, // PERIPH_CAN1
    0x00100400, // PERIPH_CAN2
    0x10100100, // PERIPH_COMP0
    0x10100200, // PERIPH_COMP1
    0x10100400, // PERIPH_COMP2
    0xf0005800, // PERIPH_EEPROM0
    0x10104000, // PERIPH_EPI0
    0x20105000, // PERIPH_ETH
    0xf0005400, // PERIPH_FAN0
    0x20000001, // PERIPH_GPIOA
    0x20000002, // PERIPH_GPIOB
    0x20000004, // PERIPH_GPIOC
    0x20000008, // PERIPH_GPIOD
    0x20000010, // PERIPH_GPIOE
    0x20000020, // PERIPH_GPIOF
    0x20000040, // PERIPH_GPIOG
    0x20000080, // PERIPH_GPIOH
    0x20000100, // PERIPH_GPIOJ
    0xf0000809, // PERIPH_GPIOK
    0xf000080a, // PERIPH_GPIOL
    0xf000080b, // PERIPH_GPIOM
    0xf000080c, // PERIPH_GPION
    0xf000080d, // PERIPH_GPIOP
    0xf000080e, // PERIPH_GPIOQ
    0xf000080f, // PERIPH_GPIOR
    0xf0000810, // PERIPH_GPIOS
    0x00000040, // PERIPH_HIBERNATE
    0x10001000, // PERIPH_I2C
    0x10001000, // PERIPH_I2C0
    0x10004000, // PERIPH_I2C1
    0xf0002002, // PERIPH_I2C2
    0xf0002003, // PERIPH_I2C3
    0xf0002004, // PERIPH_I2C4
    0xf0002005, // PERIPH_I2C5
    0x10101000, // PERIPH_I2S0
    0x20100100, // PERIPH_IEEE1588
    0xf0004800, // PERIPH_LPC0
    0x30000080, // PERIPH_MPU
    0xf0005000, // PERIPH_PECI0
    0x30000010, // PERIPH_PLL
    0x00100010, // PERIPH_PWM
    0x00100010, // PERIPH_PWM0
    0xf0004001, // PERIPH_PWM1
    0x10000100, // PERIPH_QEI
    0x10000100, // PERIPH_QEI0
    0x10000200, // PERIPH_QEI1
    0x10000010, // PERIPH_SSI
    0x10000010, // PERIPH_SSI0
    0x10000020, // PERIPH_SSI1
    0xf0001c02, // PERIPH_SSI2
    0xf0001c03, // PERIPH_SSI3
    0x30000020, // PERIPH_TEMP
    0x10100001, // PERIPH_TIMER0
    0x10100002, // PERIPH_TIMER1
    0x10100004, // PERIPH_TIMER2
    0x10100008, // PERIPH_TIMER3
    0xf0000404, // PERIPH_TIMER4
    0xf0000405, // PERIPH_TIMER5
    0x10000001, // PERIPH_UART0
    0x10000002, // PERIPH_UART1
    0x10000004, // PERIPH_UART2
    0xf0001803, // PERIPH_UART3
    0xf0001804, // PERIPH_UART4
    0xf0001805, // PERIPH_UART5
    0xf0001806, // PERIPH_UART6
    0xf0001807, // PERIPH_UART7
    0x20002000, // PERIPH_UDMA
    0x20100001, // PERIPH_USB0
    0x00000008, // PERIPH_WDOG
    0x00000008, // PERIPH_WDOG0
    0x00101000, // PERIPH_WDOG1
    0xf0005c00, // PERIPH_WTIMER0
    0xf0005c01, // PERIPH_WTIMER1
    0xf0005c02, // PERIPH_WTIMER2
    0xf0005c03, // PERIPH_WTIMER3
    0xf0005c04, // PERIPH_WTIMER4
    0xf0005c05, // PERIPH_WTIMER5
};

static constexpr uint32_t PERIPH(MyPERIPH flag)
{
    return PERIPH_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyPIN : uint8_t
{
    PIN_32KHZ,
    PIN_ADC0,
    PIN_ADC1,
    PIN_ADC2,
    PIN_ADC3,
    PIN_ADC4,
    PIN_ADC5,
    PIN_ADC6,
    PIN_ADC7,
    PIN_C0MINUS,
    PIN_C0O,
    PIN_C0PLUS,
    PIN_C1MINUS,
    PIN_C1O,
    PIN_C1PLUS,
    PIN_C2MINUS,
    PIN_C2O,
    PIN_C2PLUS,
    PIN_CCP0,
    PIN_CCP1,
    PIN_CCP2,
    PIN_CCP3,
    PIN_CCP4,
    PIN_CCP5,
    PIN_MC_FAULT0,
    PIN_PWM0,
    PIN_PWM1,
    PIN_PWM2,
    PIN_PWM3,
    PIN_PWM4,
    PIN_PWM5,
    PIN_PWM6,
    PIN_PWM7,
};

static constexpr uint32_t PIN_TABLE[] =
{
    0x80000000, // PIN_32KHZ
    0x00010000, // PIN_ADC0
    0x00020000, // PIN_ADC1
    0x00040000, // PIN_ADC2
    0x00080000, // PIN_ADC3
    0x00100000, // PIN_ADC4
    0x00200000, // PIN_ADC5
    0x00400000, // PIN_ADC6
    0x00800000, // PIN_ADC7
    0x00000040, // PIN_C0MINUS
    0x00000100, // PIN_C0O
    0x00000080, // PIN_C0PLUS
    0x00000200, // PIN_C1MINUS
    0x00000800, // PIN_C1O
    0x00000400, // PIN_C1PLUS
    0x00001000, // PIN_C2MINUS
    0x00004000, // PIN_C2O
    0x00002000, // PIN_C2PLUS
    0x01000000, // PIN_CCP0
    0x02000000, // PIN_CCP1
    0x04000000, // PIN_CCP2
    0x08000000, // PIN_CCP3
    0x10000000, // PIN_CCP4
    0x20000000, // PIN_CCP5
    0x00008000, // PIN_MC_FAULT0
    0x00000001, // PIN_PWM0
    0x00000002, // PIN_PWM1
    0x00000004, // PIN_PWM2
    0x00000008, // PIN_PWM3
    0x00000010, // PIN_PWM4
    0x00000020, // PIN_PWM5
    0x00000040, // PIN_PWM6
    0x00000080, // PIN_PWM7
};

static constexpr uint32_t PIN(MyPIN flag)
{
    return PIN_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyLDOCFG : uint8_t
{
    LDOCFG_ARST,
    LDOCFG_NORST,
};

static constexpr uint32_t LDOCFG_TABLE[] =
{
    0x00000001, // LDOCFG_ARST
    0x00000000, // LDOCFG_NORST
};

static constexpr uint32_t LDOCFG(MyLDOCFG flag)
{
    return LDOCFG_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyLDO : uint8_t
{
    LDOCFG_ARST,
    LDOCFG_NORST,
    LDO_2_25V,
    LDO_2_30V,
    LDO_2_35V,
    LDO_2_40V,
    LDO_2_45V,
    LDO_2_50V,
    LDO_2_55V,
    LDO_2_60V,
    LDO_2_65V,
    LDO_2_70V,
    LDO_2_75V,
};

static constexpr uint32_t LDO_TABLE[] =
{
    0x00000001, // LDOCFG_ARST
    0x00000000, // LDOCFG_NORST
    0x00000005, // LDO_2_25V
    0x00000004, // LDO_2_30V
    0x00000003, // LDO_2_35V
    0x00000002, // LDO_2_40V
    0x00000001, // LDO_2_45V
    0x00000000, // LDO_2_50V
    0x0000001f, // LDO_2_55V
    0x0000001e, // LDO_2_60V
    0x0000001d, // LDO_2_65V
    0x0000001c, // LDO_2_70V
    0x0000001b, // LDO_2_75V
};

static constexpr uint32_t LDO(MyLDO flag)
{
    return LDO_TABLE[static_cast<uint8_t>(flag)];
}

enum class MySYSCTL_INT : uint8_t
{
    INT_BOR,
    INT_CUR_LIMIT,
    INT_IOSC_FAIL,
    INT_MOSC_FAIL,
    INT_MOSC_PUP,
    INT_OSC_DIS,
    INT_PLL_FAIL,
    INT_PLL_LOCK,
    INT_POR,
    INT_USBPLL_LOCK,
};

static constexpr uint32_t SYSCTL_INT_TABLE[] =
{
    0x00000002, // INT_BOR
    0x00000020, // INT_CUR_LIMIT
    0x00000010, // INT_IOSC_FAIL
    0x00000008, // INT_MOSC_FAIL
    0x00000100, // INT_MOSC_PUP
    0x00000002, // INT_OSC_DIS
    0x00000001, // INT_PLL_FAIL
    0x00000040, // INT_PLL_LOCK
    0x00000004, // INT_POR
    0x00000080, // INT_USBPLL_LOCK
};

static constexpr uint32_t SYSCTL_INT(MySYSCTL_INT flag)
{
    return SYSCTL_INT_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyCAUSE : uint8_t
{
    CAUSE_BOR,
    CAUSE_EXT,
    CAUSE_LDO,
    CAUSE_POR,
    CAUSE_SW,
    CAUSE_WDOG,
    CAUSE_WDOG0,
    CAUSE_WDOG1,
};

static constexpr uint32_t CAUSE_TABLE[] =
{
    0x00000004, // CAUSE_BOR
    0x00000001, // CAUSE_EXT
    0x00000020, // CAUSE_LDO
    0x00000002, // CAUSE_POR
    0x00000010, // CAUSE_SW
    0x00000008, // CAUSE_WDOG
    0x00000008, // CAUSE_WDOG0
    0x00000020, // CAUSE_WDOG1
};

static constexpr uint32_t CAUSE(MyCAUSE flag)
{
    return CAUSE_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyBOR : uint8_t
{
    BOR_RESAMPLE,
    BOR_RESET,
};

static constexpr uint32_t MyBOR_TABLE[] =
{
    0x00000001, // BOR_RESAMPLE
    0x00000002, // BOR_RESET
};

static constexpr uint32_t MyBOR(MyBOR flag)
{
    return MyBOR_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyXTAL : uint8_t
{
    XTAL_10MHZ,
    XTAL_12MHZ,
    XTAL_12_2MHZ,
    XTAL_13_5MHZ,
    XTAL_14_3MHZ,
    XTAL_16MHZ,
    XTAL_16_3MHZ,
    XTAL_18MHZ,
    XTAL_1MHZ,
    XTAL_1_84MHZ,
    XTAL_20MHZ,
    XTAL_24MHZ,
    XTAL_25MHZ,
    XTAL_2MHZ,
    XTAL_2_45MHZ,
    XTAL_3_57MHZ,
    XTAL_3_68MHZ,
    XTAL_4MHZ,
    XTAL_4_09MHZ,
    XTAL_4_91MHZ,
    XTAL_5MHZ,
    XTAL_5_12MHZ,
    XTAL_6MHZ,
    XTAL_6_14MHZ,
    XTAL_7_37MHZ,
    XTAL_8MHZ,
    XTAL_8_19MHZ,
};

static constexpr uint32_t XTAL_TABLE[] =
{
    0x00000400, // XTAL_10MHZ
    0x00000440, // XTAL_12MHZ
    0x00000480, // XTAL_12_2MHZ
    0x000004C0, // XTAL_13_5MHZ
    0x00000500, // XTAL_14_3MHZ
    0x00000540, // XTAL_16MHZ
    0x00000580, // XTAL_16_3MHZ
    0x000005C0, // XTAL_18MHZ
    0x00000000, // XTAL_1MHZ
    0x00000040, // XTAL_1_84MHZ
    0x00000600, // XTAL_20MHZ
    0x00000640, // XTAL_24MHZ
    0x00000680, // XTAL_25MHZ
    0x00000080, // XTAL_2MHZ
    0x000000C0, // XTAL_2_45MHZ
    0x00000100, // XTAL_3_57MHZ
    0x00000140, // XTAL_3_68MHZ
    0x00000180, // XTAL_4MHZ
    0x000001C0, // XTAL_4_09MHZ
    0x00000200, // XTAL_4_91MHZ
    0x00000240, // XTAL_5MHZ
    0x00000280, // XTAL_5_12MHZ
    0x000002C0, // XTAL_6MHZ
    0x00000300, // XTAL_6_14MHZ
    0x00000340, // XTAL_7_37MHZ
    0x00000380, // XTAL_8MHZ
    0x000003C0, // XTAL_8_19MHZ
};

static constexpr uint32_t XTAL(MyXTAL flag)
{
    return XTAL_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyOSC : uint8_t
{
    OSC_EXT32,
    OSC_EXT4_19,
    OSC_INT,
    OSC_INT30,
    OSC_INT4,
    OSC_MAIN,
};

static constexpr uint32_t OSC_TABLE[] =
{
    0x80000038, // OSC_EXT32
    0x80000028, // OSC_EXT4_19
    0x00000010, // OSC_INT
    0x00000030, // OSC_INT30
    0x00000020, // OSC_INT4
    0x00000000, // OSC_MAIN
};

static constexpr uint32_t OSC(MyOSC flag)
{
    return OSC_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyDSLP : uint8_t
{
    DSLP_DIV_1,
    DSLP_DIV_10,
    DSLP_DIV_11,
    DSLP_DIV_12,
    DSLP_DIV_13,
    DSLP_DIV_14,
    DSLP_DIV_15,
    DSLP_DIV_16,
    DSLP_DIV_17,
    DSLP_DIV_18,
    DSLP_DIV_19,
    DSLP_DIV_2,
    DSLP_DIV_20,
    DSLP_DIV_21,
    DSLP_DIV_22,
    DSLP_DIV_23,
    DSLP_DIV_24,
    DSLP_DIV_25,
    DSLP_DIV_26,
    DSLP_DIV_27,
    DSLP_DIV_28,
    DSLP_DIV_29,
    DSLP_DIV_3,
    DSLP_DIV_30,
    DSLP_DIV_31,
    DSLP_DIV_32,
    DSLP_DIV_33,
    DSLP_DIV_34,
    DSLP_DIV_35,
    DSLP_DIV_36,
    DSLP_DIV_37,
    DSLP_DIV_38,
    DSLP_DIV_39,
    DSLP_DIV_4,
    DSLP_DIV_40,
    DSLP_DIV_41,
    DSLP_DIV_42,
    DSLP_DIV_43,
    DSLP_DIV_44,
    DSLP_DIV_45,
    DSLP_DIV_46,
    DSLP_DIV_47,
    DSLP_DIV_48,
    DSLP_DIV_49,
    DSLP_DIV_5,
    DSLP_DIV_50,
    DSLP_DIV_51,
    DSLP_DIV_52,
    DSLP_DIV_53,
    DSLP_DIV_54,
    DSLP_DIV_55,
    DSLP_DIV_56,
    DSLP_DIV_57,
    DSLP_DIV_58,
    DSLP_DIV_59,
    DSLP_DIV_6,
    DSLP_DIV_60,
    DSLP_DIV_61,
    DSLP_DIV_62,
    DSLP_DIV_63,
    DSLP_DIV_64,
    DSLP_DIV_7,
    DSLP_DIV_8,
    DSLP_DIV_9,
    DSLP_OSC_EXT32,
    DSLP_OSC_INT,
    DSLP_OSC_INT30,
    DSLP_OSC_MAIN,
    DSLP_PIOSC_PD,
};

static constexpr uint32_t DSLP_TABLE[] =
{
    0x00000000, // DSLP_DIV_1
    0x04800000, // DSLP_DIV_10
    0x05000000, // DSLP_DIV_11
    0x05800000, // DSLP_DIV_12
    0x06000000, // DSLP_DIV_13
    0x06800000, // DSLP_DIV_14
    0x07000000, // DSLP_DIV_15
    0x07800000, // DSLP_DIV_16
    0x08000000, // DSLP_DIV_17
    0x08800000, // DSLP_DIV_18
    0x09000000, // DSLP_DIV_19
    0x00800000, // DSLP_DIV_2
    0x09800000, // DSLP_DIV_20
    0x0A000000, // DSLP_DIV_21
    0x0A800000, // DSLP_DIV_22
    0x0B000000, // DSLP_DIV_23
    0x0B800000, // DSLP_DIV_24
    0x0C000000, // DSLP_DIV_25
    0x0C800000, // DSLP_DIV_26
    0x0D000000, // DSLP_DIV_27
    0x0D800000, // DSLP_DIV_28
    0x0E000000, // DSLP_DIV_29
    0x01000000, // DSLP_DIV_3
    0x0E800000, // DSLP_DIV_30
    0x0F000000, // DSLP_DIV_31
    0x0F800000, // DSLP_DIV_32
    0x10000000, // DSLP_DIV_33
    0x10800000, // DSLP_DIV_34
    0x11000000, // DSLP_DIV_35
    0x11800000, // DSLP_DIV_36
    0x12000000, // DSLP_DIV_37
    0x12800000, // DSLP_DIV_38
    0x13000000, // DSLP_DIV_39
    0x01800000, // DSLP_DIV_4
    0x13800000, // DSLP_DIV_40
    0x14000000, // DSLP_DIV_41
    0x14800000, // DSLP_DIV_42
    0x15000000, // DSLP_DIV_43
    0x15800000, // DSLP_DIV_44
    0x16000000, // DSLP_DIV_45
    0x16800000, // DSLP_DIV_46
    0x17000000, // DSLP_DIV_47
    0x17800000, // DSLP_DIV_48
    0x18000000, // DSLP_DIV_49
    0x02000000, // DSLP_DIV_5
    0x18800000, // DSLP_DIV_50
    0x19000000, // DSLP_DIV_51
    0x19800000, // DSLP_DIV_52
    0x1A000000, // DSLP_DIV_53
    0x1A800000, // DSLP_DIV_54
    0x1B000000, // DSLP_DIV_55
    0x1B800000, // DSLP_DIV_56
    0x1C000000, // DSLP_DIV_57
    0x1C800000, // DSLP_DIV_58
    0x1D000000, // DSLP_DIV_59
    0x02800000, // DSLP_DIV_6
    0x1D800000, // DSLP_DIV_60
    0x1E000000, // DSLP_DIV_61
    0x1E800000, // DSLP_DIV_62
    0x1F000000, // DSLP_DIV_63
    0x1F800000, // DSLP_DIV_64
    0x03000000, // DSLP_DIV_7
    0x03800000, // DSLP_DIV_8
    0x04000000, // DSLP_DIV_9
    0x00000070, // DSLP_OSC_EXT32
    0x00000010, // DSLP_OSC_INT
    0x00000030, // DSLP_OSC_INT30
    0x00000000, // DSLP_OSC_MAIN
    0x00000002, // DSLP_PIOSC_PD
};

static constexpr uint32_t DSLP(MyDSLP flag)
{
    return DSLP_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyINT_OSC : uint8_t
{
    INT_OSC_DIS,
};

static constexpr uint32_t INT_OSC_TABLE[] =
{
    0x00000002, // INT_OSC_DIS
};

static constexpr uint32_t INT_OSC(MyINT_OSC flag)
{
    return INT_OSC_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyMAIN_OSC : uint8_t
{
    MAIN_OSC_DIS,
};

static constexpr uint32_t MAIN_OSC_TABLE[] =
{
    0x00000001, // MAIN_OSC_DIS
};

static constexpr uint32_t MAIN_OSC(MyMAIN_OSC flag)
{
    return MAIN_OSC_TABLE[static_cast<uint8_t>(flag)];
}

enum class MyUSE : uint8_t
{
    USE_OSC,
    USE_PLL,
};

static constexpr uint32_t USE_TABLE[] =
{
    0x00003800, // USE_OSC
    0x00000000, // USE_PLL
};

static constexpr uint32_t USE(MyUSE flag)
{
    return USE_TABLE[static_cast<uint8_t>(flag)];
}


// ============================================================
// CAN definitions generated from can.h
// ============================================================

enum class MyCAN_MSG : uint8_t
{
    OBJ_TX_INT_ENABLE,
    OBJ_RX_INT_ENABLE,
    OBJ_EXTENDED_ID,
    OBJ_USE_ID_FILTER,
    OBJ_NEW_DATA,
    OBJ_DATA_LOST,
    OBJ_REMOTE_FRAME,
    OBJ_FIFO,
    OBJ_NO_FLAGS,
};

static constexpr uint32_t CAN_MSG(MyCAN_MSG flag)
{
    constexpr uint32_t mask[] =
    {
        0x00000001,
        0x00000002,
        0x00000004,
        0x00000008,
        0x00000080,
        0x00000100,
        0x00000040,
        0x00000200,
        0x00000000,
    };
    return mask[static_cast<uint8_t>(flag)];
}

enum class MyCAN : uint8_t
{
    INT_ERROR,
    INT_STATUS,
    INT_MASTER,
    STATUS_BUS_OFF,
    STATUS_EWARN,
    STATUS_EPASS,
    STATUS_RXOK,
    STATUS_TXOK,
    STATUS_LEC_MSK,
    STATUS_LEC_NONE,
    STATUS_LEC_STUFF,
    STATUS_LEC_FORM,
    STATUS_LEC_ACK,
    STATUS_LEC_BIT1,
    STATUS_LEC_BIT0,
    STATUS_LEC_CRC,
    STATUS_LEC_MASK,
};

static constexpr uint32_t CAN(MyCAN flag)
{
    constexpr uint32_t mask[] =
    {
        0x00000008,
        0x00000004,
        0x00000002,
        0x00000080,
        0x00000040,
        0x00000020,
        0x00000010,
        0x00000008,
        0x00000007,
        0x00000000,
        0x00000001,
        0x00000002,
        0x00000003,
        0x00000004,
        0x00000005,
        0x00000006,
        0x00000007,
    };
    return mask[static_cast<uint8_t>(flag)];
}


// ============================================================
// CAN structures
// ============================================================

struct tCANMsgObject
{
    uint32_t ulMsgID;
    uint32_t ulMsgIDMask;
    uint32_t ulFlags;
    uint32_t ulMsgLen;
    uint8_t* pucMsgData;
};

struct tCANBitClkParms
{
    uint32_t ulSyncPropPhase1Seg;
    uint32_t ulPhase2Seg;
    uint32_t ulSJW;
    uint32_t ulQuantumPrescaler;
};

// ============================================================
// CAN enums
// ============================================================

enum class tCANIntStsReg
{
    CAN_INT_STS_CAUSE,
    CAN_INT_STS_OBJECT,
};

enum class tCANStsReg
{
    CAN_STS_CONTROL,
    CAN_STS_TXREQUEST,
    CAN_STS_NEWDAT,
    CAN_STS_MSGVAL,
};

enum class tMsgObjType
{
    MSG_OBJ_TYPE_TX,
    MSG_OBJ_TYPE_TX_REMOTE,
    MSG_OBJ_TYPE_RX,
    MSG_OBJ_TYPE_RX_REMOTE,
    MSG_OBJ_TYPE_RXTX_REMOTE,
};
