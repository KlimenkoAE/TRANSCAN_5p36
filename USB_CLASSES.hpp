#pragma once
#include <cstdint>

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
struct IFC{
uint8_t number;
uint8_t ep_cnt;
uint8_t i_class;
uint8_t sub_class;
uint8_t protocol;
};
template<uint8_t N>
struct USB_Interfaces{
uint8_t cnt;
IFC interfaces[N];
};


struct CDC_DEVICE_CLASS_t{
uint16_t vid;
uint16_t pid;
USB_Interfaces<2> cdc_interfaces;
USB_Endpoins<3> cdc_endpoints;
};



struct CDC_INIT_t{
 uint16_t tx_fr_size;
uint16_t rx_fr_size;

uint32_t USB_BASE;

uint32_t DATA_IN_EP;
uint32_t DATA_IN_EP_SZ;
uint32_t DATA_IN_INT;
uint8_t DATA_IN_EP_ADDR;

uint32_t DATA_OUT_EP;
uint32_t DATA_OUT_EP_SZ;
uint32_t DATA_OUT_INT;
uint8_t  DATA_OUT_EP_ADDR;

uint32_t COMMUNICATION_EP;
uint32_t COMMUNICATION_EP_SZ;
uint32_t COMMUNICATION_INT;
uint8_t COMMUNICATION_EP_ADDR;  
};
enum enumSetupStage {SETUP,DATA};
struct SetupStage_t{uint16_t Request;
       enumSetupStage Stage;
        uint16_t data_len; };

union LINE_CODING_Struct_t{
struct {uint32_t dwDTERate;   // скорость, little-endian
        uint8_t  bCharFormat; // стоп-биты
        uint8_t  bParityType; // паритет
        uint8_t  bDataBits;   // биты данных 
        };
        uint8_t arr[7];
};



 union _Buffer{
		struct{
		uint8_t bmRequestType;
		uint8_t bRequest;
		uint8_t wValueL;
		uint8_t wValueH;
		uint8_t wIndexL;
		uint8_t wIndexH;
		uint8_t wLengthL;
		uint8_t wLengthH;
		};
                struct{
                uint16_t wRequest;
                uint16_t wValue;
                uint16_t wIndex;
                uint16_t wLengt;
                };
		struct{
			uint8_t b0;
			uint8_t b1;
			uint8_t b2;
			uint8_t b3;
			uint8_t b4;
			uint8_t b5;
			uint8_t b6;
			uint8_t b7;
		};
		uint8_t arr[8];
  };
inline _Buffer buffer={.arr={0,0,0,0,0,0,0,0}};