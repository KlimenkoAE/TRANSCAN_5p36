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




using USBWRP=MyUSB<FunctionWraper<PROC>::USB,PROC>;


//USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::MODE_INT)|USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_IN));


//#define EP_IN(n) (0x8##n)
//#define EP_OUT(n) (0x0##n)

constexpr uint8_t _EP_IN( USBVndCnst::MyUSB_EP ep_idx){return ((uint8_t)ep_idx)|0x80;};
constexpr uint8_t _EP_OUT( USBVndCnst::MyUSB_EP ep_idx){return (uint8_t)ep_idx;};

///////////////////////////////////////////////CONTROL ENDPOIT//////////////////////////////
constexpr uint32_t CDC_USB_BASE=USB0_BASE;

//constexpr USBVndCnst::MyUSB_EP EP00_IDX=USBVndCnst::MyUSB_EP::EP0;

/*constexpr PHYControlEndpoint PHY_EP00={
.IDX=static_cast<uint32_t>(EP00_IDX),
.ALIAS=USBVndCnst::Endpoint(EP00_IDX),//USB_EP_N - Stellaris !=EP_IDX 
.SZ=64,//number 16/64/
.FIFO_SZ=USBVndCnst::FIFO_SIZE(USBVndCnst::MyUSB_FIFO_SIZE::SZ_64),//vendor const
.DoubleBuffered=false,
.INTEP=USBVndCnst::INTEP_OUT(EP00_IDX),//interrupt
.CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::MODE_BULK)|USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_OUT),
.FIFO_CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_OUT),
.ADDR=_EP_OUT(EP02_IDX)
};*/

///////////////////////////////////////////////OTHER ENDPOITS//////////////////////////////

constexpr USBVndCnst::MyUSB_EP EP02_IDX=USBVndCnst::MyUSB_EP::EP2;
constexpr USBVndCnst::MyUSB_EP EP82_IDX=USBVndCnst::MyUSB_EP::EP2;
constexpr USBVndCnst::MyUSB_EP EP81_IDX=USBVndCnst::MyUSB_EP::EP1;
constexpr USBVndCnst::MyUSB_EP EP00_IDX=USBVndCnst::MyUSB_EP::EP0;

constexpr uint8_t EP0_SZ = 0x40;
constexpr uint32_t USB_BASE=USB0_BASE;

constexpr PHYControlEndpoint<Stellaris> CONTROL_EP{
{
.USB_BASE=USB_BASE,
. IDX=static_cast<uint32_t>(EP00_IDX),
. ALIAS= USBVndCnst::Endpoint(EP00_IDX), 
. SZ=EP0_SZ,//number 16/64/
. INTEP=USBVndCnst::INTEP_IN(EP00_IDX),//interrupt
.  ADDR=0x80
},
.INIT_DATA.INT_USBDevice=USBVndCnst::INT(USBVndCnst::MyINT::USB0),
.INIT_DATA.INT_GEN_FlagsAll=USBVndCnst::INTCTRL(USBVndCnst::MyUSB_INTCTRL::ALL),
.INIT_DATA.INT_GEN_Flags_Enable=USBVndCnst::INTCTRL(USBVndCnst::MyUSB_INTCTRL::RESET)|
  USBVndCnst::INTCTRL(USBVndCnst::MyUSB_INTCTRL::SUSPEND)|
  USBVndCnst::INTCTRL(USBVndCnst::MyUSB_INTCTRL::RESUME)|
  USBVndCnst::INTCTRL(USBVndCnst::MyUSB_INTCTRL::SOF),
.INIT_DATA.INT_All=USBVndCnst::INT(USBVndCnst::MyUSB_INT::ALL),
.INIT_DATA.INT_EP0=USBVndCnst::INT(USBVndCnst::MyUSB_INT::EP0),
.INIT_DATA.SysCtlPeriferal=SYSCTL_PERIPH_USB0
};//INTCTR

//#define USB_GEN_INT_EN USB_INTCTRL_RESET|USB_INTCTRL_SUSPEND|USB_INTCTRL_RESUME|USB_INTCTRL_SOF
constexpr PHYEndpoint<Stellaris> PHY_EP02={
{
.USB_BASE=USB_BASE,
.IDX=static_cast<uint32_t>(EP02_IDX),
.ALIAS=USBVndCnst::Endpoint(EP02_IDX),//USB_EP_N - Stellaris !=EP_IDX 
.SZ=64,//number 16/64/
.INTEP=USBVndCnst::INTEP_OUT(EP02_IDX),//interrupt
.ADDR=_EP_OUT(EP02_IDX)
},
.FIFO.SZ=USBVndCnst::FIFO_SIZE(USBVndCnst::MyUSB_FIFO_SIZE::SZ_64),//vendor const
.FIFO.DoubleBuffered=false,
.CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::MODE_BULK)|USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_OUT),
.FIFO.CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_OUT)

};
constexpr PHYEndpoint<Stellaris> PHY_EP82={
{
. USB_BASE=USB_BASE,
. IDX=static_cast<uint32_t>(EP82_IDX),
. ALIAS=USBVndCnst::Endpoint(EP82_IDX),//USB_EP_N - Stellaris !=EP_IDX 
. SZ=64,//number 16/64/
. INTEP=USBVndCnst::INTEP_IN(EP82_IDX),
. ADDR=_EP_IN(EP82_IDX)
},
. FIFO.SZ=USBVndCnst::FIFO_SIZE(USBVndCnst::MyUSB_FIFO_SIZE::SZ_64),//vendor const
. FIFO.DoubleBuffered=false,
. CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::MODE_BULK)|USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_IN),
. FIFO.CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_IN)
};

constexpr PHYEndpoint<Stellaris> PHY_EP81={
{
. USB_BASE=USB_BASE,
. IDX=static_cast<uint32_t>(EP81_IDX),
. ALIAS=USBVndCnst::Endpoint(EP81_IDX),//USB_EP_N - Stellaris !=EP_IDX 
. SZ=16,//number 16/64/
.INTEP=USBVndCnst::INTEP_IN(EP81_IDX),//interrupt
. ADDR=_EP_IN(EP81_IDX)
},
. FIFO.SZ=USBVndCnst::FIFO_SIZE(USBVndCnst::MyUSB_FIFO_SIZE::SZ_16),//vendor const
. FIFO.DoubleBuffered=false,
 
. CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::MODE_INT)|USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_IN),
. FIFO.CFG_FLAGS=USBVndCnst::EP_CFG(USBVndCnst::MyUSB_EP_CFG::DEV_IN)

};


constexpr uint8_t REMOTE_WAKEUP = 1;
constexpr uint8_t SELF_POWRED =1;

constexpr uint8_t STATUS_DEVICE[2]= {(REMOTE_WAKEUP<<1)|(SELF_POWRED),0 };

constexpr  CDC_INIT_t CDC_INIT={
.tx_fr_size= 0x800,
.rx_fr_size = 0x800,

.PHY_EP_DATA_IN=PHY_EP82,
.PHY_EP_DATA_OUT=PHY_EP02,
.PHY_EP_COMMUNICATION=PHY_EP81
};



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
                            CDC_INIT.PHY_EP_COMMUNICATION.ADDR,
                            EP_INTERRUPT,
                            CDC_INIT.PHY_EP_COMMUNICATION.SZ,
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
                            CDC_INIT.PHY_EP_DATA_IN.ADDR,
                            EP_BULK,
                            CDC_INIT.PHY_EP_DATA_IN.SZ,
                            0x01
                        }, {
                            CDC_INIT.PHY_EP_DATA_OUT.ADDR,
                            EP_BULK,
                            CDC_INIT.PHY_EP_DATA_OUT.SZ,
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




