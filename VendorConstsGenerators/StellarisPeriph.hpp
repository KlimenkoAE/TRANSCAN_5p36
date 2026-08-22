// Auto-generated from hw_memmap.h

enum class MyPERIPH : uint8_t
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

static constexpr uint32_t PERIPH(MyPERIPH p)
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
