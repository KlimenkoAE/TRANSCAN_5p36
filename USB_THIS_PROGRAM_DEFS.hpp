#pragma once
extern "C"{
#include <stdint.h>
#include "hw_types.h"
#include "usb.h"
}

constexpr uint32_t CDC0_DATA_IN_EP = USB_EP_2;
constexpr uint32_t CDC0_DATA_IN_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_IN_INT = USB_INTEP_DEV_IN_2;

constexpr uint32_t CDC0_DATA_OUT_EP = USB_EP_2;
constexpr uint32_t CDC0_DATA_OUT_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_OUT_INT = USB_INTEP_DEV_OUT_2;

constexpr uint32_t CDC0_COMMUNICATION_EP = USB_EP_1;
constexpr uint32_t CDC0_COMMUNICFTION_EP_SZ = 16;
constexpr uint32_t CDC0_COMMUNICATION_INT = USB_INTEP_DEV_IN_1;


/////ЭТО ВСЕ ЗДЕСЬ ВРЕМЕННО
#define DELAY_LOAD_1us 27
#define DELAY_LOAD_1ms 26666
#define UART_SPEED 115200
#define DEFAULT_CAN_FREQUENCY 10000
# define TRW_ID 0x260
#define TAIMER_PERIODms 100
#define PING_PONG_ID 0x111
#define PING_PONG_LEN 1


