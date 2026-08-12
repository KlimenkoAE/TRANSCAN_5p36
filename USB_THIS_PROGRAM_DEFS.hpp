#pragma once
extern "C"{
#include <stdint.h>
#include "hw_types.h"
#include "hw_memmap.h"
#include "usb.h"
}
#include <stdint.h> 
#include "USB_CONSTS.hpp"
#include "USB_CLASSES.hpp"
//#include "VendorFunctionsWrap.hpp"
//#include "wrappers_declarations.hpp"

//#include "VENDOR_CONSTANT_WRAP.hpp"

#include "wrappers_headers.hpp"


using  PROC=Stellaris;

using USBWRP=MyUSB<FunctionWraper<PROC>::USB,PROC>;
using USBVndCnst = VendorConsts<PROC>;







#define EP_IN(n) (0x8##n)
#define EP_OUT(n) (0x0##n)

constexpr uint32_t CDC_USB_BASE=USB0_BASE;

constexpr MyUSB_EP CDC0_DATA_IN_EP = MyUSB_EP::EP2;
constexpr uint32_t CDC0_DATA_IN_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_IN_INT = USB_INTEP_DEV_IN_2;
constexpr uint8_t  CDC0_DATA_IN_EP_ADDR EP_IN(2);

constexpr MyUSB_EP CDC0_DATA_OUT_EP = MyUSB_EP::EP2;
constexpr uint32_t CDC0_DATA_OUT_EP_SZ = 64;
constexpr uint32_t CDC0_DATA_OUT_INT = USB_INTEP_DEV_OUT_2;
constexpr uint8_t  CDC0_DATA_OUT_EP_ADDR EP_OUT(2);

constexpr MyUSB_EP CDC0_COMMUNICATION_EP = MyUSB_EP::EP1;
constexpr uint32_t CDC0_COMMUNICFTION_EP_SZ = 16;
constexpr uint32_t CDC0_COMMUNICATION_INT = USB_INTEP_DEV_IN_1;
constexpr uint8_t  CDC0_COMMUNICATION_EP_ADDR EP_IN(1);

constexpr uint8_t EP0_SZ = 0x40;

constexpr uint8_t REMOTE_WAKEUP = 1;
constexpr uint8_t SELF_POWRED =1;

constexpr uint8_t STATUS_DEVICE[2]= {(REMOTE_WAKEUP<<1)|(SELF_POWRED),0 };





constexpr CDC_DEVICE_CLASS_t CDC_DEVICE_CLASS{
    .vid = 0x0547,
    .pid = 0x1002,

    .interfaces = {
        .interfaces = {
            {
                    .number    = 0,
                    .i_class   = 0x02,
                    .sub_class = 0x02,
                    .protocol  = 0x01,

                    .specific = {
                        .value = USB_DescriptorTypes::CDCHeaderDescriptor_t{
                              5, 0x24, 0x00, 0x10, 0x01
                          },

                      .rest = {
                          .value = USB_DescriptorTypes::CDCCallManagementDescriptor_t{
                              5, 0x24, 0x01, 0x01, 1
                          },

                      .rest = {
                          .value = USB_DescriptorTypes::CDCACMDescriptor_t{
                              4, 0x24, 0x02, 0x02
                          },

                      .rest = {
                          .value = USB_DescriptorTypes::CDCUnionDescriptor_t{
                              5, 0x24, 0x06, 0, 1
                          }
            }
        }
    }
                    },

                    .endpoints = {
                        .cnt = 1,
                        .endpoints = {{
                            CDC0_COMMUNICATION_EP_ADDR,
                            EP_CONTROL,
                            CDC0_COMMUNICFTION_EP_SZ,
                            0x01
                        }}
                    }
            },

            {
                .value = {
                    .number    = 1,
                    .i_class   = 0x0A,
                    .sub_class = 0,
                    .protocol  = 0,

                    .specific = {},

                    .endpoints = {
                        .cnt = 2,
                        .endpoints = {{
                            CDC0_DATA_IN_EP_ADDR,
                            EP_BULK,
                            CDC0_DATA_IN_EP_SZ,
                            0x01
                        }, {
                            CDC0_DATA_OUT_EP_ADDR,
                            EP_BULK,
                            CDC0_DATA_OUT_EP_SZ,
                            0x01
                        }}
                    }
                }
            }
        }
    }
};
  


/*constexpr USB_Endpoins<3> CDC_endpoints={
.cnt=3,
.endpoints=
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



constexpr USB_Interfaces<2> CDC_interfaces{
.cnt=2,
.interfaces=
  {
    {
    .number=0x00,
    .ep_cnt=0x01,
    .i_class=0x02,
    .sub_class=0x02,
    .protocol=0x01
    },
    {
    .number=0x01,
    .ep_cnt=0x02,
    .i_class=0x0A,
    .sub_class=0x00,
    .protocol=0x00
    }
  }
};

static constexpr CDC_DEVICE_CLASS_t CDC_DEVICE_CLASS={
.vid=0x0547,
.pid=0x1002,
.interfaces=CDC_interfaces,
.endpoints=CDC_endpoints
};*/



constexpr  CDC_INIT_t CDC_INIT={
.tx_fr_size= 0x800,
.rx_fr_size = 0x800,
.USB_BASE=CDC_USB_BASE,

.DATA_IN_EP=CDC0_DATA_IN_EP,
.DATA_IN_EP_SZ=CDC0_DATA_IN_EP_SZ,
.DATA_IN_INT=CDC0_DATA_IN_INT,
.DATA_IN_EP_ADDR=CDC0_DATA_IN_EP_ADDR,

.DATA_OUT_EP=CDC0_DATA_OUT_EP,
.DATA_OUT_EP_SZ=CDC0_DATA_OUT_EP_SZ,
.DATA_OUT_INT=CDC0_DATA_OUT_INT,
.DATA_OUT_EP_ADDR=CDC0_DATA_OUT_EP_ADDR,

.COMMUNICATION_EP=CDC0_COMMUNICATION_EP,
.COMMUNICATION_EP_SZ=CDC0_COMMUNICFTION_EP_SZ,
.COMMUNICATION_INT=CDC0_COMMUNICATION_INT,
.COMMUNICATION_EP_ADDR = CDC0_COMMUNICATION_EP_ADDR  
};



constexpr uint8_t ExtSetupHandlersCnt=55;


/////ЭТО ВСЕ ЗДЕСЬ ВРЕМЕННО
#define DELAY_LOAD_1us 27
#define DELAY_LOAD_1ms 26666
#define UART_SPEED 115200
#define DEFAULT_CAN_FREQUENCY 10000
# define TRW_ID 0x260
#define TAIMER_PERIODms 100
#define PING_PONG_ID 0x111
#define PING_PONG_LEN 1




