#pragma once
#include "fifo_ring.hpp"
#include "serial_print.hpp"

//////////////////////////////////////////////////////
extern "C"{
#include <stdbool.h>
#include <stdint.h>
#include<string.h>
#include "sysctl.h"
#include "usb.h"
#include "timer.h"
#include "hw_usb.h"
//#define TARGET_IS_TEMPEST_RC1
#include "rom.h"
#include "rom_map.h"
}
#include "periferalInterruptsHandlers.hpp"
#include "wrappers_headers.hpp"
//#include "USB_THIS_PROGRAM_DEFS.hpp"
typedef enum
{
    CDC_SS_NONE        = 0x00, // ничего не активно
    CDC_SS_DCD         = 0x01, // Data Carrier Detect
    CDC_SS_DSR         = 0x02, // Data Set Ready
    CDC_SS_DCD_DSR     = 0x03, // DCD + DSR  (часто “порт жив”)
    CDC_SS_BREAK       = 0x04, // Break
    CDC_SS_RING        = 0x08, // Ring signal
    CDC_SS_FRAME_ERR   = 0x10, // Framing error
    CDC_SS_PARITY_ERR  = 0x20, // Parity error
    CDC_SS_OVERRUN     = 0x40  // Overrun error
} CDC_SerialState_t;

 union CDC_Flags{
  struct {
  bool COMMUNICATION_INT:1;
  bool DATA_IN_INT:1;
  bool DATA_OUT_INT:1;
  bool COMMUNICATION_BUSY:1;
  bool DATA_IN_BUSY:1;
  bool DATA_OUT_BUSY:1;
  bool HOST_LINE_STATE_CHANGED:1;
  bool PRIORITY_PENDING:1;
  bool DEV_LINE_STATE_CHANGED:1;
  bool DATA_IN_ON:1;
  bool f11:1;
  bool f12:1;
  bool f13:1;
  bool f14:1;
  bool f15:1;
  };
  uint16_t all;
};
struct _ImmediaetyTransferState{
    uint8_t* pr_buf;
    uint32_t pr_len;
    uint32_t pr_pos;
};


union CDC_LineCoding_t{
struct {uint32_t dwDTERate;   // скорость, little-endian
        uint8_t  bCharFormat; // стоп-биты
        uint8_t  bParityType; // паритет
        uint8_t  bDataBits;   // биты данных 
        };
        uint8_t arr[7];
};


template
<
CDC_INIT_t INIT
>

class CDC{
  FIFO_Ring<INIT.tx_fr_size> fr_RX; 
  FIFO_Ring<INIT.rx_fr_size> fr_TX;
  CDC_LineCoding_t LineCoding;
  Serial_Print Print;

  CDC_SerialState_t Host_Curr_State;
  CDC_SerialState_t Dev_Curr_State;
  CDC_Flags Flags;
  _ImmediaetyTransferState ImmediaetyTransferState;
  uint16_t ControlState;
  bool& TIMER_TX_INT_FLAG;
  bool& TIMER_COMMUNICATION_INT_FLAG;
public:
    CDC(bool& timer_tx_f,bool& timer_comm_f)
        : Print([this](uint8_t b){ fr_TX.add_byte(b); })
        ,TIMER_TX_INT_FLAG(timer_tx_f)
        ,TIMER_COMMUNICATION_INT_FLAG(timer_comm_f)
    {
   USB_COM_Handlers<INIT.USB_BASE>::Register(USBVndCnst::INTEP_IN(INIT.DATA_IN_EP),[this](){
  TX_InterrupHandler();
  });
   USB_COM_Handlers<INIT.USB_BASE>::Register(INIT.DATA_OUT_INT ,[this](){
  RX_InterrupHandler();
  });
   USB_COM_Handlers<INIT.USB_BASE>::Register(INIT.COMMUNICATION_INT ,[this](){
  Communication_InterrupHandler();
  });
    // принимаем host status line
    ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf, uint32_t& sup_data ){
                            this->TraceHostStatus(su_buf.wValue);
                            },
                            USB_CDC_SET_CONTROL_LINE_STATE,
                            0
    );

    //принимаем LineCoding от Hosta
 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                 memcpy(this->LineCoding.arr, buffer.arr, sup_data);
                            },
                            USB_CDC_SET_LINE_CODING,
                            0
    );
    // Отправляем текущую структуру Line Coding

 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                MAP_USBEndpointDataPut(INIT.USB_BASE, USB_EP_0,
                                       (uint8_t *)this->LineCoding.arr,sizeof(this->LineCoding.arr));
                MAP_USBEndpointDataSend(INIT.USB_BASE,USB_EP_0,USB_TRANS_IN_LAST);
                            },
                            USB_CDC_GET_LINE_CODING,
                            0
    );
//flags

 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
    	if((enum _device_state)sup_data== _device_state::Configurated){
                Flags.all=0;
                USBWRP::FIFOFlush(INIT.USB_BASE, INIT.COMMUNICATION_EP , USB_EP_DEV_IN);
                USBWRP::FIFOFlush(INIT.USB_BASE, INIT.DATA_IN_EP, USB_EP_DEV_IN);
                USBWRP::FIFOFlush(INIT.USB_BASE, INIT.DATA_OUT_EP, USB_EP_DEV_OUT);
               sup_data=(uint32_t)_device_state::Default;
                }	
               set_usb_cfg();
               Flags.DATA_IN_ON=false;
                            },
                            SET_CONFIGURATION,
                            0
    );


     ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                              Flags.COMMUNICATION_BUSY = false; 
                              Flags.COMMUNICATION_INT=false;
                            },
                            CLEAR_FEATURE_ENDPNT,
                            CDC_INIT.COMMUNICATION_EP_ADDR
    );
         ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                              fr_TX.clear();
                              Flags.DATA_IN_BUSY = false; 
                              Flags.DATA_IN_INT=false;
                              Flags.PRIORITY_PENDING= false;
                              TraceHostStatus(CDC_SS_DCD_DSR);
                            },
                            CLEAR_FEATURE_ENDPNT,
                            CDC_INIT.DATA_IN_EP_ADDR
    );
         ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                              fr_RX.clear();
                              Flags.DATA_OUT_BUSY = false; 
                              Flags.DATA_OUT_INT=false;
                            },
                            CLEAR_FEATURE_ENDPNT,
                            CDC_INIT.DATA_OUT_EP_ADDR
    );

}//constructor
                           
void set_usb_cfg() {
unsigned long ep_config[1];
unsigned long max_pak_sz[1];
unsigned long ep_status;

USBWRP::SelectEndpoit(1);

  USBWRP::DevEndpointConfigSet(
          INIT.USB_BASE,
          INIT.COMMUNICATION_EP 
          ,INIT.COMMUNICATION_EP_SZ,
          USB_EP_MODE_INT|USB_EP_DEV_IN
          );/*|USB_EP_AUTO_SET|USB_EP_DMA_MODE_0*//*);
/*  USB0_TXMAXP1_R=16;
//ep0-sz64
  MAP_USBFIFOConfigSet(USB0_BASE, USB_EP_1, 64, USB_FIFO_SZ_16, USB_EP_DEV_IN);

//while(!(USB0_TXCSRH1_R&USB_TXCSRH1_DMAEN));

MAP_USBIntEnableEndpoint(USB0_BASE,USB_INTEP_DEV_IN_1);
////////////////////
USB0_EPIDX_R=2;
//ep0 64 +ep1 8*2=80
//USBDevEndpointConfigSet(USB0_BASE, USB_EP_1, 64, DISABLE_NAK_LIMIT,
//USB_EP_MODE_BULK | USB_EP_DEV_IN);
  MAP_USBDevEndpointConfigSet(USB0_BASE, USB_EP_2,64,USB_EP_MODE_BULK|USB_EP_DEV_IN/*|USB_EP_AUTO_SET|USB_EP_DMA_MODE_0*//*);
  USB0_TXMAXP2_R=64;

  MAP_USBFIFOConfigSet(USB0_BASE, USB_EP_2, 80, USB_FIFO_SZ_64_DB, USB_EP_DEV_IN);

//while(!(USB0_TXCSRH2_R&USB_TXCSRH2_DMAEN));
MAP_USBIntEnableEndpoint(USB0_BASE,USB_INTEP_DEV_IN_2);
/////////////
USB0_EPIDX_R=2;

  MAP_USBDevEndpointConfigSet(USB0_BASE, USB_EP_2,64,USB_EP_MODE_BULK|USB_EP_DEV_OUT/*|USB_EP_AUTO_SET|USB_EP_DMA_MODE_0*//*);
  USB0_RXMAXP2_R=64;
//ep0=64+ep1=8*2+64*2=208
  MAP_USBFIFOConfigSet(USB0_BASE, USB_EP_2,208, USB_FIFO_SZ_64_DB, USB_EP_DEV_OUT);
//while(!(USB0_RXCSRH3_R&USB_RXCSRH3_DMAEN));
MAP_USBIntEnableEndpoint(USB0_BASE,USB_INTEP_DEV_OUT_2);

MAP_USBIntEnableEndpoint(USB0_BASE,
    USB_INTEP_DEV_IN_2 | USB_INTEP_DEV_OUT_2 | USB_INTEP_DEV_IN_1 | USB_INT_EP0);

//DMA_Start();

device_state=Configurated;
CDC_Host_Curr_State = 0;
CDC_Dev_Curr_State = CDC_SS_DCD; // только присутствие
print_d(__FUNCTION__,'\n');
*/
  return;
}
///////
void Send_Device_State(CDC_SerialState_t b8)
{

    static uint8_t notify[10] = {
        0xA1, 0x20,
        0x00, 0x00,
        0x00, 0x00,       // interface 0
        0x02, 0x00,
        0x02, 0x00        // DSR = 1
    };
    notify[8] = b8;       // DCD/DSR/Break/errors
    notify[9] = 0x00;
if(USBWRP::EndpointDataPut(INIT.USB_BASE, INIT.COMMUNICATION_EP, notify, 10)!=0)return;
    USBWRP::EndpointDataSend(INIT.USB_BASE, INIT.COMMUNICATION_EP, USB_TRANS_IN);
}


void TX_Immediacy( uint8_t* buf, uint32_t sz) {
    if(!Flags.DATA_IN_BUSY/*&&CDC_Host_Curr_State==CDC_SS_DCD_DSR*/) {
        // сразу отправляем первый кусок
        uint32_t chunk = (sz > INIT.DATA_IN_EP_SZ) ? INIT.DATA_IN_EP_SZ : sz;
        USBWRP::EndpointDataPut(INIT.USB_BASE, INIT.DATA_IN_EP, buf, chunk);
        USBWRP::EndpointDataSend(INIT.USB_BASE, INIT.DATA_IN_EP, USB_TRANS_IN);
        Flags.DATA_IN_BUSY = true;

        // если буфер длиннее — запомним остаток
        if(sz > chunk) {
            Flags.PRIORITY_PENDING = true;
            ImmediaetyTransferState.pr_buf = buf;
            ImmediaetyTransferState.pr_len = sz;
            ImmediaetyTransferState.pr_pos = chunk;
        }
    } else {
        // endpoint занят → отложим весь буфер
        Flags.PRIORITY_PENDING = true;
        ImmediaetyTransferState.pr_buf = buf;
        ImmediaetyTransferState.pr_len = sz;
        ImmediaetyTransferState.pr_pos = 0;
    }
}
// Передача из кольцевого буфера FIFO
void TX() {
if(fr_TX->Count()==0)return;
uint16_t cnt_for_tx=0;
// Если endpoint занят — выходим, чтобы не потерять приоритетные данные

    if(Host_Curr_State!=CDC_SS_DCD_DSR){
      Dev_Change_Status(CDC_SS_DCD_DSR);//это отправит 0x03 и по идее изменится CDC_Host_Curr_State
     // SysCtlDelay(DELAY_LOAD_1us*100);
    }
    if (Flags.DATA_IN_BUSY||!Flags.DATA_IN_ON) {
        return;
    }
    // Пока есть полный пакет
    while(fr_TX->Count() >= INIT.DATA_IN_EP_SZ) {
        uint8_t pkt[INIT.DATA_IN_EP_SZ];

        cnt_for_tx =fr_TX->read_range(pkt, INIT.DATA_IN_EP_SZ);   // вытащить из кольца
        TX_Immediacy(pkt, cnt_for_tx);
    }

    // Остаток < CDC0_TX_SZ
    if(fr_TX->Count() > 0) {
        uint8_t pkt[INIT.DATA_IN_EP_SZ];
        cnt_for_tx = fr_TX->read_range (pkt, fr_TX->Count());
        TX_Immediacy(pkt, cnt_for_tx);
    }
    else if(cnt_for_tx%INIT.DATA_IN_EP_SZ==0){
     USBWRP::EndpointDataPut(INIT.USB_BASE, INIT.DATA_IN_EP, NULL, 0);
      USBWRP::EndpointDataSend(INIT.USB_BASE, INIT.DATA_IN_EP, USB_TRANS_IN);
      Flags.DATA_IN_BUSY = true;
    }
}
// Вспомогательная inline-функция: отправка следующего куска приоритетного буфера
 void SendPriorityChunk(void){
    if(Flags.PRIORITY_PENDING) {
        if(ImmediaetyTransferState.pr_pos < ImmediaetyTransferState.pr_len) {
            uint32_t remaining = ImmediaetyTransferState.pr_len - ImmediaetyTransferState.pr_pos;
            uint32_t chunk = (remaining > INIT.DATA_IN_EP_SZ) ? INIT.DATA_IN_EP_SZ : remaining;

            USBWRP::EndpointDataPut(INIT.USB_BASE, INIT.DATA_IN_EP,
                                   ImmediaetyTransferState.pr_buf + ImmediaetyTransferState.pr_pos,
                                   chunk);
            USBWRP::EndpointDataSend(INIT.USB_BASE, INIT.DATA_IN_EP, USB_TRANS_IN);
            Flags.DATA_IN_BUSY = true;
            ImmediaetyTransferState.pr_pos += chunk;
        } else {
            // весь буфер ушёл
            Flags.PRIORITY_PENDING = false;
        }
    }
}

void TX_InterrupHandler(){
    uint32_t st  = USBWRP::EndpointStatus(INIT.USB_BASE, INIT.DATA_IN_EP);
    USBWRP::DevEndpointStatusClear(INIT.USB_BASE, INIT.DATA_IN_EP, st);
    

    Flags.DATA_IN_INT = true;   // бросаем флаг "было прерывание"
    Flags.DATA_IN_BUSY = false; // освобождаем endpoint

    SendPriorityChunk();        // проверяем и отправляем срочный кусок
}

void RX_InterrupHandler(){
   uint32_t st =USBWRP::EndpointStatus(INIT.USB_BASE, INIT.DATA_OUT_EP);
   USBWRP::DevEndpointStatusClear(INIT.USB_BASE, INIT.DATA_OUT_EP, st);
       unsigned long len = USBWRP::EndpointDataAvail(INIT.USB_BASE,INIT. DATA_OUT_EP);
        if (len > 0)
        {
    
            uint8_t rx_buf[INIT.DATA_OUT_EP_SZ];        
            USBWRP::EndpointDataGet(INIT.USB_BASE, INIT.DATA_OUT_EP, rx_buf, &len);
            // Здесь извлекаю из фифо в fr_CDC_RX
            fr_RX.write_range(rx_buf,len);                 
        }
    // Обязательно разрешаем следующий приём
     USBWRP::DevEndpointDataAck(INIT.USB_BASE, INIT.DATA_OUT_EP, false);
     Flags.DATA_OUT_INT=true;

}

void Communication_InterrupHandler(){
    uint32_t st=USBWRP::EndpointStatus(INIT.USB_BASE, INIT.COMMUNICATION_EP);
    USBWRP::DevEndpointStatusClear(INIT.USB_BASE, INIT.COMMUNICATION_EP, st);
    Flags.COMMUNICATION_BUSY = false;
    Flags.COMMUNICATION_INT=true;
    }

void TraceHostStatus(uint16_t lineStatus){//это из прерывания 2122 USB_CDC_SET_CONTROL_LINE_STATE
  Host_Curr_State=(CDC_SerialState_t)(lineStatus&0x0003);//в TX/RX проверять состояние (CDC_Curr_State)
  Flags.all=0;
  Flags.HOST_LINE_STATE_CHANGED=true;
}

void CangeHostLineState_Handler(){
    if(!Flags.HOST_LINE_STATE_CHANGED) return;

    // здесь решаем, какое DEV состояние выставить
    if(Host_Curr_State & 0x01) { // DTR=1 → порт открыт
        Dev_Change_Status(CDC_SS_DCD_DSR);
    } else {
        Dev_Change_Status(CDC_SS_DCD); // только присутствие
    }
    Flags.HOST_LINE_STATE_CHANGED = false;
}


void Dev_Change_Status(CDC_SerialState_t status){
if(status==Dev_Curr_State)return;
Dev_Curr_State=status;
DevStatusAnswer(true);
  switch (status) {
    case CDC_SS_NONE:
    break;
    case CDC_SS_DCD:
    break;
    case CDC_SS_DSR:
    break;
    case CDC_SS_DCD_DSR:
    Flags.DATA_IN_ON=true;
    break;
    case CDC_SS_OVERRUN:
    break;
    case CDC_SS_RING:
    break;
    case CDC_SS_PARITY_ERR:
    break;
    case CDC_SS_FRAME_ERR:
    break;
    case CDC_SS_BREAK:
    break;
    default:
    return;
  }
}
void DevStatusAnswer(bool wait){//это из главного цикла
static const uint32_t delay_load = DELAY_LOAD_1us*150;
    Send_Device_State(Dev_Curr_State);
    if(!Flags.COMMUNICATION_BUSY){
      Send_Device_State(Dev_Curr_State);
    Flags.COMMUNICATION_BUSY=true;
    }
  else if(wait)
   SysCtlDelay (delay_load);
    if(!Flags.COMMUNICATION_BUSY){
    Flags.COMMUNICATION_BUSY=true;
    Send_Device_State(Dev_Curr_State);
    }
}
void Process_TX_Timer()
{
if(!TIMER_TX_INT_FLAG)return;
TX();
TIMER_TX_INT_FLAG=false;
}

void Communication_Send(){
if(!TIMER_COMMUNICATION_INT_FLAG)return;
      if(!Flags.COMMUNICATION_BUSY)
      {
      DevStatusAnswer(false);
      }
  TIMER_COMMUNICATION_INT_FLAG=false;
  Flags.COMMUNICATION_BUSY=true;
  }
};


