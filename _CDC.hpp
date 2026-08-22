#pragma once
#include "fifo_ring.hpp"
#include "serial_print.hpp"
#include "CMD.hpp"

//////////////////////////////////////////////////////
extern "C"{
#include <stdio.h>
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
// Передача из кольцевого буфера FIFO
void TX();

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
  bool ECHO:1;
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

constexpr    uint8_t MAX_CMD_LEN=15;
constexpr    uint8_t MAX_CMD_ARGS=2;
constexpr    uint8_t MAX_CMD_CNT=10;
constexpr    uint8_t CMD_SEPARATOR='#';
using CMDProc=
CommandSeparator<
     MAX_CMD_LEN,
     MAX_CMD_ARGS,
     MAX_CMD_CNT,
     CMD_SEPARATOR
    > ;

template
<
auto EP_CTR,
CDC_INIT_t INIT
>

class CDC{
  FIFO_Ring<INIT.tx_fr_size> fr_RX; 
  FIFO_Ring<INIT.rx_fr_size> fr_TX;
  CDC_LineCoding_t LineCoding;
  public:
  Serial_Print Print;
private:
  CDC_SerialState_t Host_Curr_State;
  CDC_SerialState_t Dev_Curr_State;
  CDC_Flags Flags;
  _ImmediaetyTransferState ImmediaetyTransferState;
  uint16_t ControlState;
  bool DbgEcho=false;
  bool& TIMER_TX_INT_FLAG;
  bool& TIMER_COMMUNICATION_INT_FLAG;
public:
    CDC(bool& timer_tx_f,bool& timer_comm_f)
        : Print([this](uint8_t b){ fr_TX.add_byte(b); })
        ,TIMER_TX_INT_FLAG(timer_tx_f)
        ,TIMER_COMMUNICATION_INT_FLAG(timer_comm_f)      
  {  Flags.all=0;  
   //это значения USB_INTEP_INT возвращаются в сеелларис через статус прерывания
   USB_COM_Handlers<INIT.PHY_EP_DATA_IN.USB_BASE>::Register(USBVndCnst::INTEP_IN(static_cast<USBVndCnst::MyUSB_EP>(INIT.PHY_EP_DATA_IN.IDX)),[this](){
  TX_InterrupHandler();
  });
   USB_COM_Handlers<INIT.PHY_EP_DATA_OUT.USB_BASE>::Register(USBVndCnst::INTEP_OUT(static_cast<USBVndCnst::MyUSB_EP>(INIT.PHY_EP_DATA_OUT.IDX)) ,[this](){
  RX_InterrupHandler();
  });
  
   USB_COM_Handlers<INIT.PHY_EP_COMMUNICATION.USB_BASE>::Register(USBVndCnst::INTEP_IN(static_cast<USBVndCnst::MyUSB_EP>(INIT.PHY_EP_COMMUNICATION.IDX)) ,[this](){
  Communication_InterrupHandler();
  });

///////////////////CMD Register




CMDProc::CmdHandlerRegister<7>(
        "echoon",
        [this](const uint8_t*,uint8_t l){Flags.ECHO=true;}
        );
CMDProc::CmdHandlerRegister<8>(
        "echooff",
        [this](const uint8_t*,uint8_t){Flags.ECHO=false;});
/////////////////////////////////
    // принимаем host status line
    ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf, uint32_t& sup_data ){
                            this->TraceHostStatus(su_buf.wValue);
                     //       printf("0x2221 data  \n");
                            },
                            USB_CDC_SET_CONTROL_LINE_STATE,
                            0
    );

    //принимаем LineCoding от Hosta
 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
    uint32_t sz=sizeof(this->LineCoding.arr);

      for (int i=0;i<sz;++i){
//printf("0x2021 data  \n");
      this->LineCoding.arr[i]=su_buf.arr[i];

      }
                           
                            },
                            USB_CDC_SET_LINE_CODING,
                            0
    );
    // Отправляем текущую структуру Line Coding

 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                USBWRP::EndpointDataPut(EP_CTR,(uint8_t *)this->LineCoding.arr,sizeof(this->LineCoding.arr));
                USBWRP::EndpointDataSend(EP_CTR,USB_TRANS_IN_LAST);
                            },
                            USB_CDC_GET_LINE_CODING,
                            0
    );
//flags

 ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
   EP_INT_ON_OFF(false);
    	if((enum _device_state)sup_data== _device_state::Configurated){
                Flags.all=0; 
                USBWRP::FIFOFlush(INIT.PHY_EP_COMMUNICATION);
                USBWRP::FIFOFlush(INIT.PHY_EP_DATA_IN);
                USBWRP::FIFOFlush(INIT.PHY_EP_DATA_OUT);
               sup_data=(uint32_t)_device_state::Default;
                }
                //else{
              //  set_usb_cfg();
               // }	                                             
               Flags.DATA_IN_ON=false;
                   printf("clear Flags.DATA_IN_ON %d \r\n",Flags.DATA_IN_ON);
               sup_data=_device_state::Configurated;
               Host_Curr_State = CDC_SS_NONE;
               Dev_Curr_State = CDC_SS_DCD; // только присутствие
               EP_INT_ON_OFF(true);
               Flags.DATA_IN_ON=true;
               printf("set Flags.DATA_IN_ON %d \r\n",Flags.DATA_IN_ON);
                            },
                            SET_CONFIGURATION,
                            0
    );


     ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                              Flags.COMMUNICATION_BUSY = false; 
                              Flags.COMMUNICATION_INT=false;
                              USBWRP::EP_StatusClear(INIT.PHY_EP_COMMUNICATION);
                              USBWRP::DevEndpointDataAck(INIT.PHY_EP_COMMUNICATION, true);
                            },
                            CLEAR_FEATURE_ENDPNT,
                            INIT.PHY_EP_COMMUNICATION.ADDR
    );
         ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                            
                            USBWRP::EP_StatusClear(INIT.PHY_EP_DATA_IN);
                            USBWRP::DevEndpointStallClear(INIT.PHY_EP_DATA_IN);
                            USBWRP::EndpointDataToggleClear(INIT.PHY_EP_DATA_IN);
                              fr_TX.clear();
                              Flags.DATA_IN_BUSY = false; 
                              Flags.DATA_IN_INT=false;
                              Flags.PRIORITY_PENDING= false;
                              TraceHostStatus(CDC_SS_DCD_DSR);
                              SysCtlDelay(DELAY_LOAD_1us*100);
                              USBWRP::DevEndpointDataAck(INIT.PHY_EP_DATA_IN, true);
                            },
                            CLEAR_FEATURE_ENDPNT,
                            INIT.PHY_EP_DATA_IN.ADDR
    );

         ExtSetupHandlerRegister
    (
    [this](const _Buffer& su_buf,uint32_t& sup_data){
                              USBWRP::EP_StatusClear(INIT.PHY_EP_DATA_OUT);                           
                              USBWRP::DevEndpointStallClear(INIT.PHY_EP_DATA_OUT);
                              USBWRP::EndpointDataToggleClear(INIT.PHY_EP_DATA_OUT);
                              fr_RX.clear();
                              Flags.DATA_OUT_BUSY = false; 
                              Flags.DATA_OUT_INT=false;
                              USBWRP::DevEndpointDataAck(INIT.PHY_EP_DATA_OUT, true);
                              USBWRP::DevEndpointDataAck(INIT.PHY_EP_DATA_OUT, false);
                            },
                            CLEAR_FEATURE_ENDPNT,
                            INIT.PHY_EP_DATA_OUT.ADDR
                            );
set_usb_cfg();
}//constructor
     
constexpr void EP_INT_ON_OFF(bool on){
if(on)
  {
  USBWRP::IntEnableEndpoint(INIT.PHY_EP_COMMUNICATION);
  USBWRP::IntEnableEndpoint(INIT.PHY_EP_DATA_IN);
  USBWRP::IntEnableEndpoint(INIT.PHY_EP_DATA_OUT);
  }
else{
  USBWRP::IntDisableEndpoint(INIT.PHY_EP_COMMUNICATION);
  USBWRP::IntDisableEndpoint(INIT.PHY_EP_DATA_IN);
  USBWRP::IntDisableEndpoint(INIT.PHY_EP_DATA_OUT);
  };
};  
                           
constexpr void set_usb_cfg() {

 uint16_t  sh =  USBWRP::EndpointConfig(INIT.PHY_EP_COMMUNICATION,EP0_SZ);


  sh =  USBWRP::EndpointConfig(INIT.PHY_EP_DATA_IN,sh);

  USBWRP::EndpointConfig(INIT.PHY_EP_DATA_OUT,sh);



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
if(USBWRP::EndpointDataPut(INIT.PHY_EP_COMMUNICATION, notify, 10)!=0)return;
    USBWRP::EndpointDataSend(INIT.PHY_EP_COMMUNICATION, USB_TRANS_IN);
}


void TX_Immediacy( uint8_t* buf, uint32_t sz) {
    if(!Flags.DATA_IN_BUSY/*&&CDC_Host_Curr_State==CDC_SS_DCD_DSR*/) {
        // сразу отправляем первый кусок
        uint32_t chunk = (sz > INIT.PHY_EP_DATA_IN.SZ) ? INIT.PHY_EP_DATA_IN.SZ : sz;
        USBWRP::EndpointDataPut(INIT.PHY_EP_DATA_IN, buf, chunk);
        USBWRP::EndpointDataSend(INIT.PHY_EP_DATA_IN,USBVndCnst::TRANS(USBVndCnst::MyUSB_TRANS::IN));
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
//printf("TX0\n");
if(fr_TX.Count()==0)return;
uint16_t cnt_for_tx=0;
// Если endpoint занят — выходим, чтобы не потерять приоритетные данные

    if(Host_Curr_State!=CDC_SS_DCD_DSR){
      Dev_Change_Status(CDC_SS_DCD_DSR);//это отправит 0x03 и по идее изменится CDC_Host_Curr_State
     // SysCtlDelay(DELAY_LOAD_1us*100);
    // printf("TX1\n");
    }
//if(Flags.DATA_IN_BUSY==true||Flags.DATA_IN_ON==false)printf("Flags.DATA_IN_BUSY= %d   Flags.DATA_IN_ON= %d\r\n",Flags.DATA_IN_BUSY,Flags.DATA_IN_ON);
    if (Flags.DATA_IN_BUSY/*||!Flags.DATA_IN_ON*/) {
    //printf("TX2\n");
        return;
    }
    // printf("TX3\n");
    // Пока есть полный пакет
    while(fr_TX.Count() >= INIT.PHY_EP_DATA_IN.SZ) {
        uint8_t pkt[INIT.PHY_EP_DATA_IN.SZ];

        cnt_for_tx =fr_TX.read_range(pkt, INIT.PHY_EP_DATA_IN.SZ);   // вытащить из кольца
        TX_Immediacy(pkt, cnt_for_tx);

 //for (const auto& byte : pkt) {
        // :02x formats the element as a 2-digit zero-padded lowercase hex block
  //      std::printf("%c ", byte); 
  //  }
  //  std::printf("  1\n");



    //    printf("p0   %s\r\n", (int)cnt_for_tx, reinterpret_cast<const char*>(pkt));
    }

    // Остаток < CDC0_TX_SZ
    if(fr_TX.Count() > 0) {
        uint8_t pkt[INIT.PHY_EP_DATA_IN.SZ];
        cnt_for_tx = fr_TX.read_range (pkt, fr_TX.Count());
        TX_Immediacy(pkt, cnt_for_tx);
       //  for (const auto& byte : pkt) {
        // :02x formats the element as a 2-digit zero-padded lowercase hex block
       // std::printf("%c ", byte); 
    //}
   // std::printf("  2\n");
    }
    else if(cnt_for_tx%INIT.PHY_EP_DATA_IN.SZ==0){
     USBWRP::EndpointDataPut(INIT.PHY_EP_DATA_IN, NULL, 0);
      USBWRP::EndpointDataSend(INIT.PHY_EP_DATA_IN, USB_TRANS_IN);
      Flags.DATA_IN_BUSY = true;
    }
}
// Вспомогательная inline-функция: отправка следующего куска приоритетного буфера
 void SendPriorityChunk(void){
    if(Flags.PRIORITY_PENDING) {
//printf("SP0 \r\n");
        if(ImmediaetyTransferState.pr_pos < ImmediaetyTransferState.pr_len) {
      //  printf("SP1 \r\n");
            uint32_t remaining = ImmediaetyTransferState.pr_len - ImmediaetyTransferState.pr_pos;
            uint32_t chunk = (remaining > INIT.PHY_EP_DATA_IN.SZ) ? INIT.PHY_EP_DATA_IN.SZ : remaining;

            USBWRP::EndpointDataPut(INIT.PHY_EP_DATA_IN,
                                   ImmediaetyTransferState.pr_buf + ImmediaetyTransferState.pr_pos,
                                   chunk);
            USBWRP::EndpointDataSend(INIT.PHY_EP_DATA_IN, USB_TRANS_IN);
            Flags.DATA_IN_BUSY = true;
            ImmediaetyTransferState.pr_pos += chunk;
        } else {
            // весь буфер ушёл
        //    printf("SP2 \r\n");
            Flags.PRIORITY_PENDING = false;
            Flags.DATA_IN_BUSY = false;
        }
    }
}

void TX_InterrupHandler(){
    USBWRP::EP_StatusClear(INIT.PHY_EP_DATA_IN); 

    Flags.DATA_IN_INT = true;   // бросаем флаг "было прерывание"
    Flags.DATA_IN_BUSY = false; // освобождаем endpoint
//printf("TXhandler\n");
//    SendPriorityChunk();        // проверяем и отправляем срочный кусок
}

void RX_InterrupHandler(){

 //printf("RXhandler\n");
   USBWRP::EP_StatusClear(INIT.PHY_EP_DATA_OUT);
       unsigned long len = USBWRP::EndpointDataAvail(INIT.PHY_EP_DATA_OUT);
        if (len == 0)return;
        
    
            uint8_t rx_buf[INIT.PHY_EP_DATA_OUT.SZ];        
            USBWRP::EndpointDataGet(INIT.PHY_EP_DATA_OUT, rx_buf, &len);
CMDProc::CMD_Filter(
         fr_RX,
         rx_buf,
         len);
 printf("Flags.ECHO= %d\n",Flags.ECHO);
//Flags.ECHO=true;
        if(Flags.ECHO){       
         uint8_t echo_buf[64];
            uint16_t echo_len = fr_RX.read_range(echo_buf,64);
        fr_TX.write_range(echo_buf,echo_len);
        TX(); 
        }  
  
//echo
///MAP_IntMasterEnable();
    // Обязательно разрешаем следующий приём
     USBWRP::DevEndpointDataAck(INIT.PHY_EP_DATA_OUT, false);
     Flags.DATA_OUT_INT=true;

}

void Communication_InterrupHandler(){
    USBWRP::EP_StatusClear(INIT.PHY_EP_COMMUNICATION);
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
   // printf("set Flags.DATA_IN_ON %d \r\n",Flags.DATA_IN_ON);
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
//printf("TX() \r\n");
    SendPriorityChunk();  
if(!TIMER_TX_INT_FLAG)return;
//printf("TXhandler \r\n");
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


