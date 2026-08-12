#pragma once
#include <cstdint>
#include "MyTuples.hpp"

class USB_DescriptorTypes
{

protected:
    constexpr USB_DescriptorTypes() = default;

struct  
 DeviceDescriptor_t{ //DeviceDescriptor
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bcdUSBL;//in binary code decimal (i.e. 2.1 is 201H)
	uint8_t bcdUSBH;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize;
	uint8_t idVendorL;
	uint8_t idVendorH;
	uint8_t idProductL;
	uint8_t idProductH;
	uint8_t bcdDeviceL;
	uint8_t bcdDeviceH;
	uint8_t iManufactured;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfiguration;
};
	
 struct
 ConfigurationDescriptor_t{//ConfigurationDescriptor
        uint8_t bLength;
        uint8_t bDescriptorType;
        uint8_t wTotalLenghtL;
        uint8_t wTotalLenghtH;
        uint8_t bNumInterface;//число интерфейсов поддерживаемое конфигурацией
        uint8_t bConfigurationValue;//значение используемое SetConfiguration()  для выбора этой конфигурации
        uint8_t iConfiguration;//индекс строки описывающей конфигурацию
        uint8_t bmAttributes; //b5-remote wakeup,b6 - self powered
        uint8_t bMaxPower;// 2 ma per units, i.e. 50 - 100 ma
	};



 struct
 InterfaceDescriptor_t {//InterfaceDescriptor
	 uint8_t bLength;
	 uint8_t bDescriptorType;
	 uint8_t bInterfaceNumber;//индекс интерфейса в массиве интерфейсов поддерживаемых конфигурацией
	 uint8_t bAlternateSatting;//Если конфигурация поддерживает один интерфейс с несколькими альтернативными настройками - номер настройки
	 uint8_t bNumEndpoints;//сколько конечных точек кроме контрольной
	 uint8_t bInterfaceClass;//0xFF - vendor specific All ather- (USB-IF)
	 uint8_t bInterfaceSubClass;//(USB-IF) if bInterfactClass is not 0xff
	 uint8_t bInterfaceProtocol;//If this field is set to FFH, the device uses	a vendor-specific protocol for this	interface.
	 uint8_t iInterface;//Index of string descriptor describing this interface
};




 struct
 EPDescriptor_t{
	 uint8_t bLength;
	 uint8_t bDescriptorType;
	 uint8_t EndpointAddress;//Bit 3...0: The endpoint number,	Bit 7: Direction, ignored for	control endpoints 0 = OUT 	1 = IN 
	 uint8_t bmAttributes;//Bits 1..0: 00 = Control,01 = Isochronous,10 = Bulk,11 = Interrupt,
	//If not an isochronous endpoint bits 5..2 are reserved,else :Bits 3..2: 00 No Synchronization,	01 Asynchronous, 10 = Adaptive,	11 Synchronous
	//Bits 5..4: 00 Data ,01 Feedback,10 Implicit feedback Data,11 = Reserved
	 uint8_t wMaxPacketSizeL;//For all endpoints, bits 10..0 specify the maximum
							//packet size (in bytes).
							
	 uint8_t wMaxPacketSizeH;//For high-speed isochronous and interrupt endpoints:
							//Bits 12..11 specify the number of additional transaction
							//opportunities per microframe:
								//00 = None (1 transaction per microframe)
								//01 = 1 additional (2 per microframe)
								//10 = 2 additional (3 per microframe)
								//11 = Reserved
	 uint8_t bInterval; //Interval for polling endpoint for data transfers.
					//Expressed in frames or microframes depending on the
					//device operating speed (i.e., either 1 millisecond or
					//125 μs units).
					//For full-/high-speed isochronous endpoints, this value
					//must be in the range from 1 to 16. The bInterval value
					//is used as the exponent for a 2bInterval-1 value; e.g., a
					//bInterval of 4 means a period of 8 (24-1).
					//For full-/low-speed interrupt endpoints, the value of
					//this field may be from 1 to 255.
					//For high-speed interrupt endpoints, the bInterval value
					//is used as the exponent for a 2**(bInterval-1) value; e.g., a
					//bInterval of 4 means a period of 8 (2**4-1). This value
					//must be from 1 to 16.
					//For high-speed bulk/control OUT endpoints, the
					//bInterval must specify the maximum NAK rate of the
					//endpoint. A value of 0 indicates the endpoint never
					//NAKs. Other values indicate at most 1 NAK each
					//bInterval number of microframes. This value must be
					//in the range from 0 to 255.
};


//////////////////////////CDC
public:
 struct
CDCHeaderDescriptor_t{
    uint8_t bFunctionLength;      // Размер этого функционального дескриптора (байт)
    uint8_t bDescriptorType;      // CS_INTERFACE (0x24) - класс-специфический дескриптор интерфейса
    uint8_t bDescriptorSubtype;   // Header Functional Descriptor (0x00)
    uint8_t bcdCDC_L;             // Версия спецификации CDC, младший байт
    uint8_t bcdCDC_H;             // Версия спецификации CDC, старший байт
} ;

 struct
 CDCACMDescriptor_t
{//CDCACMDescriptor
    uint8_t bFunctionLength;      // Размер дескриптора
    uint8_t bDescriptorType;      // CS_INTERFACE (0x24)
    uint8_t bDescriptorSubtype;   // Abstract Control Management Functional Descriptor (0x02)
    uint8_t bmCapabilities;       // Возможности ACM-интерфейса
                                // bit0 = поддержка Set_Comm_Feature/Clear_Comm_Feature
                                // bit1 = поддержка Set_Line_Coding,
                                //        Set_Control_Line_State,
                                //        Get_Line_Coding
                                // bit2 = Send_Break
                                // bit3 = Network Connection
} ;

 struct
 CDCCallManagementDescriptor_t
{//CDCCallManagementDescriptor
    uint8_t bFunctionLength;      // Размер дескриптора
    uint8_t bDescriptorType;      // CS_INTERFACE (0x24)
    uint8_t bDescriptorSubtype;   // Call Management Functional Descriptor (0x01)

    uint8_t bmCapabilities;       // Возможности управления вызовами
                               // bit0 = устройство самостоятельно обрабатывает Call Management
                               // bit1 = Data Interface используется для Call Management

    uint8_t bDataInterface;       // Номер Data Interface
} ;

 struct
 CDCUnionDescriptor_t
{//CDCUnionDescriptor
    uint8_t bFunctionLength;        // Размер дескриптора
    uint8_t bDescriptorType;        // CS_INTERFACE (0x24)
    uint8_t bDescriptorSubtype;     // Union Functional Descriptor (0x06)

    uint8_t bMasterInterface;       // Номер Communication Interface

    uint8_t bSlaveInterface0;       // Номер первого Data Interface
} ;


 struct 
 StringDescriptor_t{
	uint8_t sz;
	uint8_t type;
	uint16_t str[7];
	} ;



/*template<class ClassSpecific, class Endpoints>
struct Interface
{
    InterfaceDescriptor_t descriptor;
    ClassSpecific class_specific;
    Endpoints endpoints;
};
 template<size_t N>
struct Interfaces{
Interface ifc<>[]
}

template<CDC_DEVICE_CLASS_t cdc_dev>
struct FullConfigurationDescriptor_t{
        ConfigurationDescriptor_t cd;
        Interfaces ifc;
  };*/
};






enum _device_state {Suspend,Default,Adressed,Configurated};
struct Endpoint {
    uint8_t address;
    uint8_t type;
    uint16_t size;
    uint8_t interval;
};

template<uint8_t N>
struct USB_Endpoins{
uint8_t cnt;
Endpoint endpoints[N]; 
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

template<class Specific, uint8_t N>
struct newIFC
{
    using SpecificType = Specific;

    uint8_t number;
    uint8_t i_class;
    uint8_t sub_class;
    uint8_t protocol;

    Specific specific;
    USB_Endpoins<N> endpoints;
};

template<class... IFC>
struct newUSB_Interfaces {
    CTuple<IFC...> interfaces;
};

struct NoSpecific {};

using CDC_ControlSpecific = CTuple<
    USB_DescriptorTypes::CDCHeaderDescriptor_t,
    USB_DescriptorTypes::CDCCallManagementDescriptor_t,
    USB_DescriptorTypes::CDCACMDescriptor_t,
    USB_DescriptorTypes::CDCUnionDescriptor_t
>;

using CDC_Interfaces = newUSB_Interfaces<
    newIFC<CDC_ControlSpecific, 1>,   // Communication interface: 1 endpoint
    newIFC<NoSpecific,2>    // Data interface: 2 endpoints
>;



template<class Interfaces>
struct DEVICE_CLASS_t {
    uint16_t vid;
    uint16_t pid;
    Interfaces interfaces;
};

using CDC_DEVICE_CLASS_t = DEVICE_CLASS_t<CDC_Interfaces>;

















/*доступ на пымять
std::get<0>(DEVICE.interfaces).endpoints
std::get<1>(DEVICE.interfaces).endpoints*/

enum class MyUSB_EP : uint8_t
{
    EP0, EP1, EP2, EP3, EP4, EP5, EP6, EP7,
    EP8, EP9, EP10, EP11, EP12, EP13, EP14, EP15,
    EP16, EP17, EP18, EP19, EP20, EP21, EP22, EP23,
    EP24, EP25, EP26, EP27, EP28, EP29, EP30, EP31
};



struct CDC_INIT_t{
 uint16_t tx_fr_size;
uint16_t rx_fr_size;

uint32_t USB_BASE;

MyUSB_EP DATA_IN_EP;
uint32_t DATA_IN_EP_SZ;
uint32_t DATA_IN_INT;
uint8_t DATA_IN_EP_ADDR;

MyUSB_EP DATA_OUT_EP;
uint32_t DATA_OUT_EP_SZ;
uint32_t DATA_OUT_INT;
uint8_t  DATA_OUT_EP_ADDR;

MyUSB_EP COMMUNICATION_EP;
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







