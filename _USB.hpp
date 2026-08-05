#pragma once

extern "C"{
#include "usb.h"
#include "hw_usb.h"
#include "sysctl.h"
#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
#include"interrupt.h"
}
#include <cstdint>
#include <cstdbool>
#include <functional>
#include <algorithm>
#include <cstdarg>

#include "periferalISR.hpp"
#include "USB_CONSTS.hpp"
#include "USB_THIS_PROGRAM_DEFS.hpp"
#include "periferalInterruptsHandlers.hpp"

template<
uint32_t usb_base,
auto 
>
class USBEnumerator;
class USB_DescriptorTypes;


template<CDC_DEVICE_CLASS_t CDC_DC>
class USB_Descriptors;

class UsbISR:IPeriferalISR{
public:
void Registration(std::function<void()> isr, uint32_t sw_def, ...);
};

//////////////////////////CLASS USB
template<
uint32_t usb_base,
auto usb_dev
>
class USB{
enum _device_state {Suspend,Default,Adressed,Configurated}device_state; 

//INTERRUPT
UsbISR UISR;
USB(){
  UISR.Registration([this](){
      this->ISR();
      },usb_base);
}

void ISR(){
uint32_t int_GEN_status;
uint32_t int_COM_status;
  int_COM_status=MAP_USBIntStatusEndpoint(USB0_BASE);
  if(int_COM_status!=0)
    USB_COM_Vector(int_COM_status);
  int_GEN_status=MAP_USBIntStatusControl(USB0_BASE);
    USB_GEN_Vector(int_GEN_status);
return;
}

inline int USB_GEN_Vector(uint32_t int_GEN_status){

if(int_GEN_status&USB_INTCTRL_RESET){
  return 1;
}


if(int_GEN_status&USB_INTCTRL_RESUME){
return 3;
}

if(int_GEN_status&USB_INTCTRL_SUSPEND){

  device_state=Suspend;
  return 2;
}

if(int_GEN_status&USB_INTCTRL_SOF){
  return USB_IS_SOF;
  }
return 0;
}

inline int USB_COM_Vector(uint32_t int_COM_status){

 if(int_COM_status&USB_INTEP_0){
unsigned long SetupPacketSz = MAP_USBEndpointDataAvail(USB0_BASE, USB_EP_0);

  if(SetupPacketSz>0)
  {
   Enumerator.USB_COM_Vector(int_COM_status,SetupPacketSz);
    int_COM_status&=~(USB_INTEP_0);
  }
}
USB_COM_Handlers<usb_base>::Execute(int_COM_status);

return 0;
}

////////////////////

class USBEnumerator<usb_base,usb_dev>Enumerator;
class USB_Descriptors<usb_dev> Descriptors;

};//class USB


template<
uint32_t usb_base,
auto usb_dev
>
class USBEnumerator{
typedef enum {Suspend,Default,Adressed,Configurated}usb_device_state; 
 static SetupStage_t SetupStage;
 static union _Buffer{
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
                }wFields;
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
static _Buffer buffer={.arr={0,0,0,0,0,0,0,0}};
static void EP_StatusClear(uint32_t ep){
 uint32_t st  = USBEndpointStatus(usb_base, ep);
    MAP_USBDevEndpointStatusClear(usb_base, ep, st);
}



inline int USB_COM_Vector(uint32_t int_COM_status,unsigned long   SetupPacketSz){

    MAP_USBEndpointDataGet (usb_base, USB_EP_0, (uint8_t*)&buffer,  &SetupPacketSz);

      if(SetupStage.Stage==SETUP)
          SetupStage.Request=(uint16_t)(buffer.bmRequestType)<<8|(buffer.bRequest);
    processingSetupPackage(SetupStage.Request);
}

//////////////////
static void processingSetupPackage(uint16_t rq){
	
	switch(rq){
		case GET_STATUS_DEVICE      :
		status_dev();
		break;

		case GET_STATUS_INTERF      :
		goto no_implementation;
		break;

		case GET_STATUS_ENDPNT      :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_DEVICE:
                switch (buffer.wValueL)
                {
                    case 1: // DEVICE_REMOTE_WAKEUP
                        // remote_wakeup_enabled = 0;
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    default:
                        // CLEAR TEST_MODE по спеке нельзя
                        MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                        break;
                }
                break;

		case CLEAR_FEATURE_INTERF   :
		goto no_implementation;
		break;

		case CLEAR_FEATURE_ENDPNT   :

                // уточняем feature = ENDPOINT_HALT (wValue == 0)
                if (buffer.wValueL != 0 || buffer.wValueH != 0)
                {
                    MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                    break;
                }

                switch (buffer.wIndexL)
                {
                    case 0x81: // EP1 IN — Interrupt (SERIAL_STATE)
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_1, USB_EP_DEV_IN);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_1, USB_EP_DEV_IN);
                         EP_StatusClear(USB_EP_1);
                        G_Flags.EP1_IN_BUSY = false;
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x81);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x02: // EP2 OUT — Bulk OUT
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                         EP_StatusClear(USB_EP_2);
                          Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x02);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        // снова разрешить приём на OUT
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_2, false);

                        break;

                    case 0x82: // EP2 IN — Bulk IN (типичный CDC)
                        EP_StatusClear(USB_EP_2);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_2, USB_EP_DEV_IN);             
                        fr_CDC_TX.clear(&fr_CDC_TX);
                        CDC0_Flags.DATA_IN_BUSY = false; // 
                        CDC0_Flags.DATA_IN_INT=false;
                        CDC0_Flags.PRIORITY_PENDING= false;
                        Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x82);
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_IN);
                        CDC0_TraceHostStatus(CDC_SS_DCD_DSR);
                        SysCtlDelay(DELAY_LOAD_1us*100);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x83);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
                         Execute_ExtSetupHandler(CLEAR_FEATURE_ENDPNT, 0x01);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    default:
                        MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                        break;
                }
                break;

		case SET_FEATURE_DEVICE:
                  // wValue = feature
                  switch (buffer.wValueL)
                  {
                      case 1: // DEVICE_REMOTE_WAKEUP
                          // remote_wakeup_enabled = 1;
                          MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                          break;

                      case 2: // TEST_MODE (для FS CDC обычно не нужен)
                          MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                          break;

                      default:
                          MAP_USBDevEndpointStall(usb_base, USB_EP_0, USB_EP_DEV_OUT);
                          break;
                  }
                  break;

		case SET_FEATURE_INTERF     :
		goto no_implementation;
		break;

		case SET_FEATURE_ENDPNT     :
		goto no_implementation;
		break;

		case SET_ADDRESS            :
		set_addr();
		break;

		case GET_DESCRIPTOR_DEVICE  :
                if(!USB_Descriptors<usb_dev>::DescriptorSend(buffer.wValueH,buffer.wLengthL,buffer.wValueL))goto no_implementation;	
		break;

		case GET_DESCRIPTOR_INTERF  :
                goto no_implementation;
		break;

		case GET_DESCRIPTOR_ENDPNT  :
		goto no_implementation;
		break;

		case SET_DESCRIPTOR         :
		goto no_implementation;
		break;

		case GET_CONFIGURATION      :
		goto no_implementation;
		break;

		case SET_CONFIGURATION      :
		
		set_cfg();
                CDC0_Flags.DATA_IN_ON=false;
                Execute_ExtSetupHandler(SET_CONFIGURATION);
                USBDevEndpointDataAck(usb_base, 0,true);
             //   ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SET_CONFIGURATION");
		break;

		case GET_INTERFACE          :
		goto no_implementation;
		break;

		case SET_INTERFACE          :
		goto no_implementation;
		break;

		case SYNCH_FRAME            :
		goto no_implementation;
		break;

		case GET_REPORT             :
		goto no_implementation;
		break;
		
		case SET_IDLE        	   :
		break;
                case USB_CDC_SET_LINE_CODING:
               

if(SetupStage.Stage==enumSetupStage::SETUP){
SetupStage.Stage=enumSetupStage::DATA;
SetupStage.data_len=(uint16_t)buffer.wLengthH<<8|buffer.wLengthL;
MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
}
else
{
 memcpy(LINE_CODING_Struct.arr, buffer.arr, SetupStage.data_len);  
    Execute_ExtSetupHandler(USB_CDC_SET_LINE_CODING);  
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
SetupStage.Stage=enumSetupStage::SETUP;
}                  
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                MAP_USBEndpointDataPut(usb_base, USB_EP_0,
              (uint8_t *)LINE_CODING_Struct.arr,sizeof(LINE_CODING_Struct.arr));
                Execute_ExtSetupHandler(USB_CDC_GET_LINE_CODING) ; 
                MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN_LAST);


                // Завершаем control-transfer
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:

                CDC_ControlState = ((uint16_t)buffer.wValueH << 8) | buffer.wValueL;
                CDC0_TraceHostStatus(CDC_ControlState);
               Execute_ExtSetupHandler(USB_CDC_SET_CONTROL_LINE_STATE,0,wValue,buffer.wIndex,buffer.wL) ;

                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                 break;	
		
no_implementation:		
		default:
                USBDevEndpointStall(usb_base,USB_EP_0,USB_EP_DEV_IN);
		//stall();
		break;
	}
};//Process packet
static void status_dev(){
//bus powred, remote wakeup
SetUpAnswer((uint8_t*)&STATUS_DEVICE,sizeof(STATUS_DEVICE),buffer.wLengthL);
        MAP_USBEndpointDataPut(usb_base, USB_EP_0, (uint8_t*)&STATUS_DEVICE, buffer.wLengthL);
}
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){;};break;}
        else {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_left)==-1){;};
        while( MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN_LAST)==-1){;};
}

};//Class USB_Enumerator


class USB_DescriptorTypes
{
public:
    USB_DescriptorTypes() = delete;

protected:
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

template<IFC ifc>
 struct
 InterfaceDescriptor_t {//InterfaceDescriptor
	inline static constexpr uint8_t bLength=9;
	inline static constexpr uint8_t bDescriptorType=DESC_TYPE_INTERFACE;
	inline static constexpr uint8_t bInterfaceNumber=ifc.number;//индекс интерфейса в массиве интерфейсов поддерживаемых конфигурацией
	inline static constexpr uint8_t bAlternateSatting=0x00;//Если конфигурация поддерживает один интерфейс с несколькими альтернативными настройками - номер настройки
	inline static constexpr uint8_t bNumEndpoints=ifc.ep_cnt;//сколько конечных точек кроме контрольной
	inline static constexpr uint8_t bInterfaceClass=ifc.i_class;//0xFF - vendor specific All ather- (USB-IF)
	inline static constexpr uint8_t bInterfaceSubClass=ifc.sub_class;//(USB-IF) if bInterfactClass is not 0xff
	inline static constexpr uint8_t bInterfaceProtocol=ifc.protocol;//If this field is set to FFH, the device uses	a vendor-specific protocol for this	interface.
	inline static constexpr uint8_t iInterface=0x00;//Index of string descriptor describing this interface
};

template<Endpoint ep>
 struct
 EPDescriptor_t{
	inline static constexpr uint8_t bLength=0x7;
	inline static constexpr uint8_t bDescriptorType=DESC_TYPE_ENDPOINT;
	inline static constexpr uint8_t EndpointAddress=ep.address;//Bit 3...0: The endpoint number,	Bit 7: Direction, ignored for	control endpoints 0 = OUT 	1 = IN 
	inline static constexpr uint8_t bmAttributes=ep.type;//Bits 1..0: 00 = Control,01 = Isochronous,10 = Bulk,11 = Interrupt,
	//If not an isochronous endpoint bits 5..2 are reserved,else :Bits 3..2: 00 No Synchronization,	01 Asynchronous, 10 = Adaptive,	11 Synchronous
	//Bits 5..4: 00 Data ,01 Feedback,10 Implicit feedback Data,11 = Reserved
	inline static constexpr uint8_t wMaxPacketSizeL=ep.size&0xFF;//For all endpoints, bits 10..0 specify the maximum
							//packet size (in bytes).
							
	inline static constexpr uint8_t wMaxPacketSizeH=ep.size>>8;//For high-speed isochronous and interrupt endpoints:
							//Bits 12..11 specify the number of additional transaction
							//opportunities per microframe:
								//00 = None (1 transaction per microframe)
								//01 = 1 additional (2 per microframe)
								//10 = 2 additional (3 per microframe)
								//11 = Reserved
	inline static constexpr uint8_t bInterval=ep.interval; //Interval for polling endpoint for data transfers.
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
};

//////////////////////////////////////////////////////////////////////////////



template<
CDC_DEVICE_CLASS_t CDC_DC 
> class USB_Descriptors:USB_DescriptorTypes
{
 DeviceDescriptor_t  DeviceDescriptor=
 { //DeviceDescriptor
        .bLength=0x12,
	.bDescriptorType=0x01,
	.bcdUSBL=0x00,//in binary code decimal (i.e. 2.1 is 201H)
	.bcdUSBH=0x02,
	.bDeviceClass=0x00,
	.bDeviceSubClass=0x00,
	.bDeviceProtocol=0x00,
	.bMaxPacketSize=EP0_SZ,
	.idVendorL=CDC_DC.vid&0xFF,
	.idVendorH=CDC_DC.vid>>8,
	.idProductL=CDC_DC.pid&0xFF,
	.idProductH=CDC_DC.pid>>8,
	.bcdDeviceL=0x00,
	.bcdDeviceH=0x01,
	.iManufactured=0x01,
	.iProduct=0x02,
	.iSerialNumber=0x03,
	.bNumConfiguration=0x01
} ;

static InterfaceDescriptor_t <
CDC_DC.cdc_interfaces.interfaces[0]
>
_id0;
static EPDescriptor_t<
 CDC_DC.cdc_endpoints.endoints[0]
  >_epd1 ;//int in

static InterfaceDescriptor_t<
CDC_DC.cdc_interfaces.interfaces[1]
> _id1;
static EPDescriptor_t<
 CDC_DC.cdc_endpoints.endoints[1]
  >_epd2 ; //bulk in
static EPDescriptor_t<
 CDC_DC.cdc_endpoints.endoints[2]
  >_epd3 ; //bulk out 

static constexpr uint16_t config_total_len=
+sizeof(ConfigurationDescriptor_t)
+CDC_DC.cdc_interfaces.cnt*sizeof(_id0)
+sizeof(CDCHeaderDescriptor_t)
+sizeof(CDCACMDescriptor_t)
+sizeof(CDCCallManagementDescriptor_t)
+sizeof(CDCUnionDescriptor_t)
+CDC_DC.cdc_endpoints.cnt*sizeof(_epd3);

static constexpr uint8_t d_cfg_len=sizeof(ConfigurationDescriptor_t);
	
inline static constexpr
 ConfigurationDescriptor_t ConfigurationDescriptor={//ConfigurationDescriptor
		. bLength=d_cfg_len,
		. bDescriptorType=DESC_TYPE_CONFIGURATION,
		. wTotalLenghtL=config_total_len&0xFF,
		. wTotalLenghtH=config_total_len>>8,
		. bNumInterface=CDC_DC.cdc_interfaces.cnt,//число интерфейсов поддерживаемое конфигурацией
		. bConfigurationValue=0x01,//значение используемое SetConfiguration()  для выбора этой конфигурации
		. iConfiguration=0x00,//индекс строки описывающей конфигурацию
		. bmAttributes=0x80, //b5-remote wakeup,b6 - self powered
		. bMaxPower=0x32// 2 ma per units, i.e. 50 - 100 ma
	};





//////////////////////////CDC

inline static constexpr
CDCHeaderDescriptor_t CDCHeaderDescriptor=
{//CDCHeaderDescriptor
    . bFunctionLength=0x05,      // Размер этого функционального дескриптора (байт)
    . bDescriptorType=0x24,      // CS_INTERFACE (0x24) - класс-специфический дескриптор интерфейса
    . bDescriptorSubtype=0x00,   // Header Functional Descriptor (0x00)
    . bcdCDC_L=0x10,             // Версия спецификации CDC, младший байт
    . bcdCDC_H=0x01             // Версия спецификации CDC, старший байт
} ;

inline static constexpr 
CDCACMDescriptor_t CDCACMDescriptor=
{//CDCACMDescriptor
    . bFunctionLength=0x04,      // Размер дескриптора
    . bDescriptorType=0x24,      // CS_INTERFACE (0x24)
    . bDescriptorSubtype=0x02,   // Abstract Control Management Functional Descriptor (0x02)
    . bmCapabilities=0x02       // Возможности ACM-интерфейса
                                // bit0 = поддержка Set_Comm_Feature/Clear_Comm_Feature
                                // bit1 = поддержка Set_Line_Coding,
                                //        Set_Control_Line_State,
                                //        Get_Line_Coding
                                // bit2 = Send_Break
                                // bit3 = Network Connection
} ;

inline static constexpr 
CDCCallManagementDescriptor_t CDCCallManagementDescriptor=
{//CDCCallManagementDescriptor
    .bFunctionLength=0x05,      // Размер дескриптора
    .bDescriptorType=0x24,      // CS_INTERFACE (0x24)
    .bDescriptorSubtype=0x01,   // Call Management Functional Descriptor (0x01)
    .bmCapabilities=0x00,       // Возможности управления вызовами
                               // bit0 = устройство самостоятельно обрабатывает Call Management
                               // bit1 = Data Interface используется для Call Management

    .bDataInterface=0x01       // Номер Data Interface
} ;

inline static constexpr 
CDCUnionDescriptor_t CDCUnionDescriptor
{//CDCUnionDescriptor
    .bFunctionLength=0x05,        // Размер дескриптора
    .bDescriptorType=0x24,        // CS_INTERFACE (0x24)
   .bDescriptorSubtype=0x06,     // Union Functional Descriptor (0x06)

    .bMasterInterface=0x00,       // Номер Communication Interface

    .bSlaveInterface0=0x01       // Номер первого Data Interface
} ;

inline static constexpr struct{
	ConfigurationDescriptor_t cd=ConfigurationDescriptor;
        InterfaceDescriptor_t<
        CDC_DC.cdc_interfaces.interfaces[0]> id0 =_id0;
        CDCHeaderDescriptor_t cdc_h=CDCHeaderDescriptor;
        CDCCallManagementDescriptor_t cdc_callMan=CDCCallManagementDescriptor;
        CDCACMDescriptor_t cdc_acm=CDCACMDescriptor;
        CDCUnionDescriptor_t cdc_union=CDCUnionDescriptor;

       EPDescriptor_t<
       CDC_DC.cdc_endpoints.endoints[0]
       > epd1=_epd1;
       InterfaceDescriptor_t<
      CDC_DC.cdc_interfaces.interfaces[1]
      > id1=_id1;
       EPDescriptor_t <
       CDC_DC.cdc_endpoints.endoints[1]
        >epd2=_epd2;
       EPDescriptor_t <
       CDC_DC.cdc_endpoints.endoints[2]
       >epd3=_epd3;
}FullConfigurationDescriptor;


#define LANG_ID               0x00
#define MAN_INDEX             0x01
#define PRD_INDEX             0x02
#define SRN_INDEX             0x03





static constexpr  StringDescriptor_t ManDescriptor ={
	14
	,DESC_TYPE_STRING
	,{L'A',L'n',L'd',L'r',L'e',L'w'}
	} ;
	
static constexpr StringDescriptor_t ProductDescriptor ={
	10
	,DESC_TYPE_STRING
	,{L'T',L'E',L'S',L'T',L'0'}
};

static constexpr StringDescriptor_t SerialNumber = {
    16,               // длина: 2 + 7*2
    DESC_TYPE_STRING, // тип = 0x03
    { L'1', L'2', L'3', L'4', L'5', L'6', L'7' }
};
static constexpr StringDescriptor_t LanguageDescriptor ={
	4
	,DESC_TYPE_STRING
	,{0x0409}
};
//////////////////////////
static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( MAP_USBEndpointDataPut(USB0_BASE,USB_EP_0,data_begin,byte_to_transfer)==-1){;}; 
        if(byte_left==0)      
          {while(MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN)==-1){;};break;}
        else {while(MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN)==-1){;}};
        byte_left-=byte_to_transfer;
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
        while( MAP_USBEndpointDataPut(USB0_BASE,USB_EP_0,data_begin,byte_left)==-1){;};
        while( MAP_USBEndpointDataSend(USB0_BASE,USB_EP_0,USB_TRANS_IN_LAST)==-1){;};
}

static bool DescriptorSend(uint8_t desc_type,uint16_t host_await_sz,uint8_t index=0){

		switch(desc_type){

			case DESC_TYPE_DEVICE:

			SetUpAnswer((uint8_t*)&DeviceDescriptor,sizeof(DeviceDescriptor),host_await_sz);
                        return true;

			case DESC_TYPE_CONFIGURATION:{
			uint16_t dbg =sizeof(FullConfigurationDescriptor);
                        SetUpAnswer((uint8_t*)&FullConfigurationDescriptor,sizeof(FullConfigurationDescriptor),host_await_sz);
			return true;
                        }

			case DESC_TYPE_STRING:	
			return string(index,host_await_sz);

			case DESC_TYPE_INTERFACE:
			break;
			case DESC_TYPE_ENDPOINT:
			break;
			case DESC_TYPE_DEVICE_QUALIFIER:
			break;
			case DESC_TYPE_OTHER_SPEED_CONFIGURATION:
			break;
			case DESC_TYPE_INTERFACE_POWER1:
			break;
		}
return false;
 }   

static bool string(uint8_t index ,uint8_t host_await_sz){
    switch (index){
    case 0:
    SetUpAnswer((uint8_t*)&LanguageDescriptor,sizeof(LanguageDescriptor),host_await_sz);
    return true;
    case 1:
    SetUpAnswer((uint8_t*)&ManDescriptor,sizeof(ManDescriptor),host_await_sz);
    return true;
    break;
    case 2:
    SetUpAnswer((uint8_t*)&ProductDescriptor,sizeof(ProductDescriptor),host_await_sz);
    return true;
    case 3:
    SetUpAnswer((uint8_t*)&SerialNumber,sizeof(SerialNumber),host_await_sz);
    return true;
    }
    return false;
  }

};//desc class




