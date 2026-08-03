#pragma once

extern "C"{
#include "usb.h"
#include "hw_usb.h"
#include "sysctl.h"
#include "rom.h"
#include "rom_map.h"
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



class UsbISR:IPeriferalISR{
public:
void Registration(std::function<void()> isr, uint32_t sw_def, ...);
};


/*template<
uint32_t usb_base
>
class USB_Enumerator{
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

//print_d("USB EP status = %08X\n", int_COM_status);
 if(int_COM_status&USB_INTEP_0){
unsigned long SetupPacketSz = MAP_USBEndpointDataAvail(USB0_BASE, USB_EP_0);

  if(SetupPacketSz>0)
  {
    MAP_USBEndpointDataGet (USB0_BASE, USB_EP_0, (uint8_t*)&buffer,  &SetupPacketSz);
      if(SetupStage.Stage==SETUP)
          SetupStage.Request=(uint16_t)(buffer.bmRequestType)<<8|(buffer.bRequest);
    
PrintBuffer
    SetUpRoutine(SetupStage.Request);
   }else{

 };
}

  if(int_COM_status & CDC0_COMMUNICATION_INT)
    {
    CDC0_Communication_InterrupHandler();
    }
    //* ---------- EP2 (CDC Bulk IN) ---------- 
    if(int_COM_status & CDC0_DATA_IN_INT)
    {
    CDC0_TX_InterrupHandler();
    }
   / /* ---------- EP3 (CDC Bulk OUT) ---------- 
    if(int_COM_status & CDC0_DATA_OUT_INT)
    {
    CDC0_RX_InterrupHandler();  
    }

return 0;
}

void ISR_USB(){
uint32_t int_GEN_status;
uint32_t int_COM_status;
  int_COM_status=MAP_USBIntStatusEndpoint(USB0_BASE);
  if(int_COM_status!=0)
    USB_COM_Vector(int_COM_status);
  int_GEN_status=MAP_USBIntStatusControl(USB0_BASE);
  USB_GEN_Vector(int_GEN_status);
return;
}*/

template<
uint32_t usb_base
>
class USBEnumerator{
typedef enum {Suspend,Default,Adressed,Configurated}usb_device_state; 
 union _Buffer{
		struct{;
		uint8_t bmRequestType;
		uint8_t bRequest;
		uint8_t wValueL;
		uint8_t wValueH;
		uint8_t wIndexL;
		uint8_t wIndexH;
		uint8_t wLengthL;
		uint8_t wLengthH;
		};
		struct{;
			uint8_t b0;
			uint8_t b1;
			uint8_t b2;
			uint8_t b3;
			uint8_t b4;
			uint8_t b5;
			uint8_t b6;
			uint8_t b7;
		};
                struct{
                
                };
		uint8_t arr[8];
  };
static _Buffer buffer={.arr={0,0,0,0,0,0,0,0}};

/*static void processingSetupPackage(uint16_t rq){
	
	switch(rq){
		case GET_STATUS_DEVICE      :
		//status_dev();
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
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x02: // EP2 OUT — Bulk OUT
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_2, USB_EP_DEV_OUT);
                         EP_StatusClear(USB_EP_2);
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
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_2, USB_EP_DEV_IN);
                        CDC0_TraceHostStatus(CDC_SS_DCD_DSR);
                        SysCtlDelay(DELAY_LOAD_1us*100);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x83: // EP3 IN — только если такой endpoint есть
                        MAP_USBDevEndpointStallClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                        MAP_USBEndpointDataToggleClear(usb_base, USB_EP_3, USB_EP_DEV_IN);
                        MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                        break;

                    case 0x01: // EP1 OUT — на всякий случай (в логе бывало wIndex=0001)
                        // если EP1 OUT нет в дескрипторах — можно просто ACK
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

		switch(buffer.wValueH){
			case DESC_TYPE_DEVICE:
			d_device();
			break;
			case DESC_TYPE_CONFIGURATION:
			d_config();
			break;
			case DESC_TYPE_STRING:
			d_string();
			break;
			case DESC_TYPE_INTERFACE:
			goto no_implementation;
			break;
			case DESC_TYPE_ENDPOINT:;
			goto no_implementation;
			break;
			case DESC_TYPE_DEVICE_QUALIFIER:
			goto no_implementation;
			break;
			case DESC_TYPE_OTHER_SPEED_CONFIGURATION:
			goto no_implementation;
			break;
			case DESC_TYPE_INTERFACE_POWER1:
			goto no_implementation;
			break;
			default:
                        PrintBuffer
			//stall();
			break;
		}
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
               

if(SetupStage.Stage==SETUP){
SetupStage.Stage=DATA;
SetupStage.data_len=(uint16_t)buffer.wLengthH<<8|buffer.wLengthL;
MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, false);
//ToDebugPrint.DebugPrintAdd(0,EP_CONTROL_STATUS_F,SET_CONFIGURATION,"SETUP STAGE CDC_SET_LINE_CODING");
}
else
{
 memcpy(LINE_CODING_Struct.arr, buffer.arr, SetupStage.data_len);  
      
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);

SetupStage.Stage=SETUP;
}
}
                   
                break;
                case USB_CDC_GET_LINE_CODING:

                // Отправляем текущую структуру Line Coding
                MAP_USBEndpointDataPut(usb_base, USB_EP_0,
                                       (uint8_t *)LINE_CODING_Struct.arr,sizeof(LINE_CODING_Struct.arr));
                MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN_LAST);


                // Завершаем control-transfer
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);

                break;

    
            //    break;
                case USB_CDC_SET_CONTROL_LINE_STATE:
                CDC_ControlState = ((uint16_t)buffer.wValueH << 8) | buffer.wValueL;

                CDC0_TraceHostStatus(CDC_ControlState);
               
                MAP_USBDevEndpointDataAck(usb_base, USB_EP_0, true);
                 break;
		
		
no_implementation:		
		default:
                USBDevEndpointStall(usb_base,USB_EP_0,USB_EP_DEV_IN);
		//stall();
		break;
	}
};*///Process packet

/*static void SetUpAnswer(uint8_t* buf,uint8_t buf_sz,uint8_t host_await_sz){

        uint8_t byte_left= buf_sz>host_await_sz?host_await_sz:buf_sz;
        uint8_t* data_begin=buf;


        while(byte_left>=EP0_SZ){
          uint8_t byte_to_transfer=EP0_SZ;      
          while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_to_transfer)==-1){print_d("w1\n");}; 
        if(byte_left==0)      
          {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){print_d("w2\n");};break;}
        else {while(MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN)==-1){print_d("w3\n");}};
        byte_left-=byte_to_transfer;
        print_d(" %u\n", byte_left);
        data_begin+=byte_to_transfer;
	}
        //0<byte_left<EP0_SZ
         print_d(" %u\n", byte_left);
        while( MAP_USBEndpointDataPut(usb_base,USB_EP_0,data_begin,byte_left)==-1){print_d("w4\n");};
         while( MAP_USBEndpointDataSend(usb_base,USB_EP_0,USB_TRANS_IN_LAST)==-1){print_d("w5\n");};
}*/

};//Class USB_Enumerator

/*constexpr Endpoint epCDC0_DATA_OUT={
    CDC0_DATA_OUT_EP_ADDR,
    EP_BULK,
    CDC0_DATA_OUT_EP_SZ,
    0x01
};*/

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

template<uint8_t ifc_number,uint8_t ifc_ep_cnt,uint8_t ufc_class,uint8_t ifc_sub_class,uint8_t ifc_protocol>
 struct
 InterfaceDescriptor_t {//InterfaceDescriptor
	inline static constexpr uint8_t bLength=9;
	inline static constexpr uint8_t bDescriptorType=DESC_TYPE_INTERFACE;
	inline static constexpr uint8_t bInterfaceNumber=ifc_number;//индекс интерфейса в массиве интерфейсов поддерживаемых конфигурацией
	inline static constexpr uint8_t bAlternateSatting=0x00;//Если конфигурация поддерживает один интерфейс с несколькими альтернативными настройками - номер настройки
	inline static constexpr uint8_t bNumEndpoints=ifc_ep_cnt;//сколько конечных точек кроме контрольной
	inline static constexpr uint8_t bInterfaceClass=ufc_class;//0xFF - vendor specific All ather- (USB-IF)
	inline static constexpr uint8_t bInterfaceSubClass=ifc_sub_class;//(USB-IF) if bInterfactClass is not 0xff
	inline static constexpr uint8_t bInterfaceProtocol=ifc_protocol;//If this field is set to FFH, the device uses	a vendor-specific protocol for this	interface.
	inline static constexpr uint8_t iInterface=0x00;//Index of string descriptor describing this interface
};

template<uint8_t adres,uint8_t type,uint16_t sz,uint8_t interval>
 struct
 EPDescriptor_t{
	inline static constexpr uint8_t bLength=0x7;
	inline static constexpr uint8_t bDescriptorType=DESC_TYPE_ENDPOINT;
	inline static constexpr uint8_t EndpointAddress=adres;//Bit 3...0: The endpoint number,	Bit 7: Direction, ignored for	control endpoints 0 = OUT 	1 = IN 
	inline static constexpr uint8_t bmAttributes=type;//Bits 1..0: 00 = Control,01 = Isochronous,10 = Bulk,11 = Interrupt,
	//If not an isochronous endpoint bits 5..2 are reserved,else :Bits 3..2: 00 No Synchronization,	01 Asynchronous, 10 = Adaptive,	11 Synchronous
	//Bits 5..4: 00 Data ,01 Feedback,10 Implicit feedback Data,11 = Reserved
	inline static constexpr uint8_t wMaxPacketSizeL=sz&0xFF;//For all endpoints, bits 10..0 specify the maximum
							//packet size (in bytes).
							
	inline static constexpr uint8_t wMaxPacketSizeH=sz>>8;//For high-speed isochronous and interrupt endpoints:
							//Bits 12..11 specify the number of additional transaction
							//opportunities per microframe:
								//00 = None (1 transaction per microframe)
								//01 = 1 additional (2 per microframe)
								//10 = 2 additional (3 per microframe)
								//11 = Reserved
	inline static constexpr uint8_t bInterval=interval; //Interval for polling endpoint for data transfers.
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
} CDCACMDescriptor;

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
} CDCCallManagementDescriptor;

 struct
 CDCUnionDescriptor_t
{//CDCUnionDescriptor
    uint8_t bFunctionLength;        // Размер дескриптора
    uint8_t bDescriptorType;        // CS_INTERFACE (0x24)
    uint8_t bDescriptorSubtype;     // Union Functional Descriptor (0x06)

    uint8_t bMasterInterface;       // Номер Communication Interface

    uint8_t bSlaveInterface0;       // Номер первого Data Interface
} CDCUnionDescriptor;


 struct 
 StringDescriptor_t{
	uint8_t sz;
	uint8_t type;
	uint16_t str[7];
	} ;
};
//////////////////////////////////////////////////////////////////////////////
/*template<
typename DevType,
uint16_t vid,
uint16_t pid,
void... ext
> class {};*/
template<
class CDC_DEVICE_CLASS ,
uint16_t vid,
uint16_t pid,
USB_Interfaces<2> cdc_interfaces,
USB_Endpoins<3> cdc_endpoints
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
	.idVendorL=vid&0xFF,
	.idVendorH=vid>>8,
	.idProductL=pid&0xFF,
	.idProductH=pid>>8,
	.bcdDeviceL=0x00,
	.bcdDeviceH=0x01,
	.iManufactured=0x01,
	.iProduct=0x02,
	.iSerialNumber=0x03,
	.bNumConfiguration=0x01
} ;

static InterfaceDescriptor_t <
cdc_interfaces.interfaces[0].ifc_number,
cdc_interfaces.interfaces[0].ifc_ep_cnt,
cdc_interfaces.interfaces[0].ufc_class,
cdc_interfaces.interfaces[0].ifc_sub_class,
cdc_interfaces.interfaces[0].ifc_protocol
>
_id0;
static EPDescriptor_t<
 cdc_endpoints.endoints[0].address,
 cdc_endpoints.endoints[0].type,
 cdc_endpoints.endoints[0].size,
 cdc_endpoints.endoints[0].interval
  >_epd1 ;//int in

static InterfaceDescriptor_t<
cdc_interfaces.interfaces[1].ifc_number,
cdc_interfaces.interfaces[1]. ifc_ep_cnt,
cdc_interfaces.interfaces[1].ufc_class,
cdc_interfaces.interfaces[1].ifc_sub_class,
cdc_interfaces.interfaces[1].ifc_protocol
> _id1;
static EPDescriptor_t<
 cdc_endpoints.endoints[1].address,
 cdc_endpoints.endoints[1].type,
 cdc_endpoints.endoints[1].size,
 cdc_endpoints.endoints[1].interval
  >_epd2 ; //bulk in
static EPDescriptor_t<
 cdc_endpoints.endoints[2].address,
 cdc_endpoints.endoints[2].type,
 cdc_endpoints.endoints[2].size,
 cdc_endpoints.endoints[2].interval
  >_epd3 ; //bulk out 

static constexpr uint16_t config_total_len=
+sizeof(ConfigurationDescriptor_t)
+cdc_interfaces.cnt*sizeof(_id0)
+sizeof(CDCHeaderDescriptor_t)
+sizeof(CDCACMDescriptor_t)
+sizeof(CDCCallManagementDescriptor_t)
+sizeof(CDCUnionDescriptor_t)
+cdc_endpoints.cnt*sizeof(_epd3);

static constexpr uint8_t d_cfg_len=sizeof(ConfigurationDescriptor_t);
	
inline static constexpr
 ConfigurationDescriptor_t ConfigurationDescriptor{//ConfigurationDescriptor
		. bLength=d_cfg_len,
		. bDescriptorType=DESC_TYPE_CONFIGURATION,
		. wTotalLenghtL=config_total_len&0xFF,
		. wTotalLenghtH=config_total_len>>8,
		. bNumInterface=cdc_interfaces.cnt,//число интерфейсов поддерживаемое конфигурацией
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
        InterfaceDescriptor_t<cdc_interfaces.interfaces[0].ifc_number,
        cdc_interfaces.interfaces[0].ifc_ep_cnt,
        cdc_interfaces.interfaces[0].ufc_class,
        cdc_interfaces.interfaces[0].ifc_sub_class,
        cdc_interfaces.interfaces[0].ifc_protocol> id0 =_id0;
        CDCHeaderDescriptor_t cdc_h=CDCHeaderDescriptor;
        CDCCallManagementDescriptor_t cdc_callMan=CDCCallManagementDescriptor;
        CDCACMDescriptor_t cdc_acm=CDCACMDescriptor;
        CDCUnionDescriptor_t cdc_union=CDCUnionDescriptor;

       EPDescriptor_t<
       cdc_endpoints.endoints[0].address,
       cdc_endpoints.endoints[0].type,
       cdc_endpoints.endoints[0].size,
       cdc_endpoints.endoints[0].interval
       > epd1=_epd1;
       InterfaceDescriptor_t<
      cdc_interfaces.interfaces[1].ifc_number,
      cdc_interfaces.interfaces[1]. ifc_ep_cnt,
      cdc_interfaces.interfaces[1].ufc_class,
      cdc_interfaces.interfaces[1].ifc_sub_class,
      cdc_interfaces.interfaces[1].ifc_protocol
      > id1=_id1;
       EPDescriptor_t <
       cdc_endpoints.endoints[1].address,
       cdc_endpoints.endoints[1].type,
       cdc_endpoints.endoints[1].size,
       cdc_endpoints.endoints[1].interval
        >epd2=_epd2;
       EPDescriptor_t <
       cdc_endpoints.endoints[2].address,
       cdc_endpoints.endoints[2].type,
       cdc_endpoints.endoints[2].size,
       cdc_endpoints.endoints[2].interval
       >epd3=_epd3;
}FullConfigurationDescriptor;


#define LANG_ID               0x00
#define MAN_INDEX             0x01
#define PRD_INDEX             0x02
#define SRN_INDEX             0x03





const StringDescriptor_t ManDescriptor ={
	14
	,DESC_TYPE_STRING
	,{L'A',L'n',L'd',L'r',L'e',L'w'}
	} ;
	
const StringDescriptor_t ProductDescriptor ={
	10
	,DESC_TYPE_STRING
	,{L'T',L'E',L'S',L'T',L'0'}
};

const StringDescriptor_t SerialNumber = {
    16,               // длина: 2 + 7*2
    DESC_TYPE_STRING, // тип = 0x03
    { L'1', L'2', L'3', L'4', L'5', L'6', L'7' }
};
const StringDescriptor_t LanguageDescriptor ={
	4
	,DESC_TYPE_STRING
	,{0x0409}
};

};//desc class