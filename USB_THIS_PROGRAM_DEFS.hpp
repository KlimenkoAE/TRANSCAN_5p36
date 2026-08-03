#pragma once
extern "C"{
#include <stdint.h>
#include "hw_types.h"
#include "usb.h"
}
#include <stdint.h> 
#include "USB_CONSTS.hpp"

constexpr uint32_t CDC0_DATA_IN_EP = USB_EP_2;
constexpr uint32_t CDC0_DATA_IN_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_IN_INT = USB_INTEP_DEV_IN_2;
constexpr uint8_t  CDC0_DATA_IN_EP_ADDR EP_OUT(2);

constexpr uint32_t CDC0_DATA_OUT_EP = USB_EP_2;
constexpr uint32_t CDC0_DATA_OUT_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_OUT_INT = USB_INTEP_DEV_OUT_2;
constexpr uint8_t  CDC0_DATA_OUT_EP_ADDR EP_OUT(2);

constexpr uint32_t CDC0_COMMUNICATION_EP = USB_EP_1;
constexpr uint32_t CDC0_COMMUNICFTION_EP_SZ = 16;
constexpr uint32_t CDC0_COMMUNICATION_INT = USB_INTEP_DEV_IN_1;
constexpr uint8_t  CDC0_COMMUNICATION_EP_ADDR EP_IN(1);

#define EP0_SZ 0x40

struct Endpoint {
    uint8_t address;
    uint8_t type;
    uint16_t size;
    uint8_t interval;
};

template<uint8_t N>
struct USB_Endpoins{
uint8_t cnt;
Endpoint endoints[N]; 
};

constexpr USB_Endpoins<3> CDC_endpoints={
.cnt=3,
.endoints=
  {
    {
    CDC0_COMMUNICATION_EP_ADDR,
    EP_CONTROL,
    CDC0_COMMUNICFTION_EP_SZ,
    0x01
    },
    {
    CDC0_DATA_IN_EP_ADDR,
    EP_BULK,
    CDC0_DATA_IN_EP_SZ,
    0x01
    },
    {
    CDC0_DATA_OUT_EP_ADDR,
    EP_BULK,
    CDC0_DATA_OUT_EP_SZ,
    0x01
    }
  }
};

struct IFC{
uint8_t ifc_number;
uint8_t ifc_ep_cnt;
uint8_t ufc_class;
uint8_t ifc_sub_class;
uint8_t ifc_protocol;
};
template<uint8_t N>
struct USB_Interfaces{
uint8_t cnt;
IFC interfaces[N];
};

constexpr USB_Interfaces<2> CDC_interfaces{
.cnt=2,
.interfaces=
  {
    {
    .ifc_number=0x00,
    .ifc_ep_cnt=0x01,
    .ufc_class=0x02,
    .ifc_sub_class=0x02,
    .ifc_protocol=0x01
    },
    {
    .ifc_number=0x01,
    .ifc_ep_cnt=0x02,
    .ufc_class=0x0A,
    .ifc_sub_class=0x00,
    .ifc_protocol=0x00
    }
  }
};


/////ЭТО ВСЕ ЗДЕСЬ ВРЕМЕННО
#define DELAY_LOAD_1us 27
#define DELAY_LOAD_1ms 26666
#define UART_SPEED 115200
#define DEFAULT_CAN_FREQUENCY 10000
# define TRW_ID 0x260
#define TAIMER_PERIODms 100
#define PING_PONG_ID 0x111
#define PING_PONG_LEN 1




