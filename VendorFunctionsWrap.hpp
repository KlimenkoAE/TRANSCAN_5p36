#pragma once
#include <cstdarg>
#include <cstdint>
#include "wrappers_headers.hpp"

template <>
class FunctionWraper<Stellaris>{
public:
  class USB{
public:

static  uint16_t vwEndpointConfig( const PHYEndpoint<Stellaris>& ep, uint16_t fifo_shift){


vwSelectEndpoit(ep);

vwDevEndpointConfigSet(ep);
          //ep.USB_BASE,
          //ep.ALIAS, 
          //ep.SZ,
          //ep.FIFO.CFG_FLAGS);
          //USB_EP_MODE_INT|USB_EP_DEV_IN
          //|USB_EP_AUTO_SET|USB_EP_DMA_MODE_0
     

vwSetEndpoitFIFO_Size(ep);

  vwFIFOConfigSet(ep,fifo_shift);

return  fifo_shift+=ep.SZ*(ep.FIFO.DoubleBuffered?2:1);

};
#define USB_GEN_INT_EN USB_INTCTRL_RESET|USB_INTCTRL_SUSPEND|USB_INTCTRL_RESUME|USB_INTCTRL_SOF
static  void vwUsbInit(const PHYControlEndpoint<Stellaris>& ctr_ep ){

////////USB INIT
 MAP_SysCtlPeripheralEnable(ctr_ep.INIT_DATA.SysCtlPeriferal );



  MAP_SysCtlUSBPLLEnable();
 uint32_t base=ctr_ep.USB_BASE;
  uint32_t dev_int=ctr_ep.INIT_DATA.INT_USBDevice;
  MAP_IntEnable(dev_int);

  MAP_USBIntDisableControl(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_GEN_FlagsAll);
  MAP_USBIntEnableControl(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_GEN_Flags_Enable);

  MAP_USBIntDisableEndpoint(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_All);
  MAP_USBIntEnableEndpoint(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_EP0);

  MAP_USBIntEnable(ctr_ep.USB_BASE, ctr_ep.INIT_DATA.INT_All );

  MAP_USBDevConnect(ctr_ep.USB_BASE);
}

  static uint32_t vwIntStatusControl(const PHYEndpointBase<Stellaris>& endpoint)
  {
     return  MAP_USBIntStatusControl(endpoint.USB_BASE);
  }

  static uint32_t vwIntStatusEndpoint( const PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBIntStatusEndpoint(endpoint.USB_BASE);
  }
  ////////

static void vwIntEnableEndpoint(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBIntEnableEndpoint(endpoint.USB_BASE, endpoint.INTEP);
  }

static void vwIntEnableControl(const PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntEnableControl(endpoint.USB_BASE, ulFlags);
  }

  static void vwIntDisable(const PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntDisable(endpoint.USB_BASE, ulFlags);
  }

  static void vwIntDisableControl(const PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntDisableControl(endpoint.USB_BASE, ulFlags);
  }
/*static void vwIntEnableEndpoint(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBIntEnableEndpoint(endpoint.USB_BASE, endpoint.INTEP);
  }*/
  static void vwIntDisableEndpoint(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBIntDisableEndpoint(endpoint.USB_BASE, endpoint.INTEP);
  }

  static void vwIntEnable(const PHYEndpointBase<Stellaris>& endpoint,   unsigned long ulFlags)
  {
      MAP_USBIntEnable(endpoint.USB_BASE, ulFlags);
  }

  static void vwEndpointDataToggleClear(
      
      const PHYEndpoint<Stellaris>& endpoint)
  {
      MAP_USBEndpointDataToggleClear(endpoint.USB_BASE, endpoint.ALIAS, endpoint.FIFO.CFG_FLAGS);
  }

  static void vwEndpointDMAChannel(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulChannel)
  {
      MAP_USBEndpointDMAChannel(endpoint.USB_BASE, endpoint.ALIAS, ulChannel);
  }

  static void vwEndpointDMADisable(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMADisable(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static void vwEndpointDMAEnable(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMAEnable(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static unsigned long vwEndpointStatus(
      
      const PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBEndpointStatus(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static unsigned long vwFIFOAddrGet(
      
      const PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBFIFOAddrGet(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static void vwFIFOConfigGet(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long* pulFIFOAddress,
      unsigned long* pulFIFOSize,
      unsigned long ulFlags)
  {
      MAP_USBFIFOConfigGet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          pulFIFOAddress,
          pulFIFOSize,
          ulFlags);
  }

  static void vwFIFOConfigSet(
      
       const PHYEndpoint<Stellaris>& endpoint,
      unsigned long ulFIFOAddress)
  {
      MAP_USBFIFOConfigSet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFIFOAddress,
          endpoint.FIFO.SZ,
          endpoint.FIFO.CFG_FLAGS);
  }

  static void vwFIFOFlush(
      
      const PHYEndpoint<Stellaris>& endpoint
      )
  {
      MAP_USBFIFOFlush(endpoint.USB_BASE, endpoint.ALIAS, endpoint.FIFO.CFG_FLAGS);
  }

  static unsigned long vwFrameNumberGet(const PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBFrameNumberGet(endpoint.USB_BASE);
  }

  static unsigned long vwHostAddrGet(    
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      return MAP_USBHostAddrGet(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static void vwHostAddrSet(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulAddr,
      unsigned long ulFlags)
  {
      MAP_USBHostAddrSet(endpoint.USB_BASE, endpoint.ALIAS, ulAddr, ulFlags);
  }

  static void vwHostEndpointConfig(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulMaxPayload,
      unsigned long ulNAKPollInterval,
      unsigned long ulTargetEndpoint,
      unsigned long ulFlags)
  {
      USBHostEndpointConfig(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulMaxPayload,
          ulNAKPollInterval,
          ulTargetEndpoint,
          ulFlags);
  }

  static void vwHostEndpointDataAck(
      
      const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBHostEndpointDataAck(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static void vwHostEndpointDataToggle(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      bool bDataToggle,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointDataToggle(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          bDataToggle,
          ulFlags);
  }

  static void vwHostEndpointStatusClear(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointStatusClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static unsigned long vwDevAddrGet(const PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBDevAddrGet(endpoint.USB_BASE);
  }

  static void vwDevAddrSet(
      const PHYEndpointBase<Stellaris>& endpoint,     
      unsigned long ulAddress)
  {
      MAP_USBDevAddrSet(endpoint.USB_BASE, ulAddress);
  }

  static void vwDevConnect(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevConnect(endpoint.USB_BASE);
  }

  static void vwDevDisconnect(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevDisconnect(endpoint.USB_BASE);
  }

  static void vwDevEndpointConfigGet(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long* pulMaxPacketSize,
      unsigned long* pulFlags)
  {
      MAP_USBDevEndpointConfigGet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          pulMaxPacketSize,
          pulFlags);
  }

  static void vwDevEndpointConfigSet(
      
      const PHYEndpoint<Stellaris>& endpoint)
  {
      MAP_USBDevEndpointConfigSet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          endpoint.SZ,
          endpoint.CFG_FLAGS);
  }

  static void vwDevEndpointDataAck(
      const PHYEndpointBase<Stellaris>& endpoint,
      bool bIsLastPacket)
  {
      MAP_USBDevEndpointDataAck(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          bIsLastPacket);
  }
////USBDevEndpointDataAck(USB0_BASE, 0,true);
  static void vwDevEndpointStall(
       const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevEndpointStall(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          endpoint.CFG_FLAGS);
  }

  static void vwDevEndpointStallClear(
       const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevEndpointStallClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          endpoint.CFG_FLAGS);
  }

  static void vwDevEndpointStatusClear(
      
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStatusClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static void vwDevMode(const PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevMode(endpoint.USB_BASE);
  }

  static unsigned long vwEndpointDataAvail(
      const PHYEndpointBase<Stellaris>& endpoint )
  {
      return MAP_USBEndpointDataAvail(
          endpoint.USB_BASE,
          endpoint.ALIAS);
  }
  static unsigned long vwEndpointDataAvail(
      PHYControlEndpoint<Stellaris>& endpoint)
  {
      return MAP_USBEndpointDataAvail(
          endpoint.USB_BASE,
          endpoint.ALIAS);
  }
  static long vwEndpointDataGet(
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned char* pucData,
      unsigned long* pulSize)
    {
        return MAP_USBEndpointDataGet(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            pucData,
            pulSize);
    }

    static long vwEndpointDataPut(
        const PHYEndpointBase<Stellaris>& endpoint,
        unsigned char* pucData,
        unsigned long ulSize)
    {
        return MAP_USBEndpointDataPut(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            pucData,
            ulSize);
    }

    static long vwEndpointDataSend(        
        const PHYEndpointBase<Stellaris>& endpoint,
        unsigned long ulTransType)
    {
        return MAP_USBEndpointDataSend(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            ulTransType);
    }
static void vwSelectEndpoit( const PHYEndpointBase<Stellaris>& endpoint){


   //   USB0_EPIDX_R=1;//(uint8_t)endpoint.IDX;
 //(*((volatile unsigned char *)0x4005000E))
auto gbg1=USBVndCnst::MyUSB_REG::EPIDX;
auto gbg=USBVndCnst::USB_REG(USBVndCnst::MyUSB_REG::EPIDX);
        *((uint8_t*)(endpoint.USB_BASE+USBVndCnst::USB_REG(USBVndCnst::MyUSB_REG::EPIDX)))=(uint8_t)endpoint.IDX;
      }

static void vwSetEndpoitFIFO_Size(
         const PHYEndpoint<Stellaris>& endpoint)
    {
    uint8_t ep_dir=endpoint.ADDR>>8;
    uint32_t regRTX=ep_dir==8?USBVndCnst::TXMAXP((USBVndCnst::MyUSB_EP)endpoint.IDX):USBVndCnst::RXMAXP((USBVndCnst::MyUSB_EP)endpoint.IDX);

       *((uint32_t*)(endpoint.USB_BASE+ep_dir))=endpoint.SZ;
    }
static   unsigned vwCOMInterruptIndex(uint32_t int_COM_status)//плучаем номер младшего установленного бита
    {                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
        unsigned b = std::__countr_zero(int_COM_status);

uint32_t dbg=
         (b < 16) ? (b - 1)       // IN
                        : (31 - b + 15);// OUT
                        return dbg;
    }
    static void vwEP_StatusClear( const PHYEndpointBase<Stellaris>& ep){
    uint32_t st  = MAP_USBEndpointStatus(ep.USB_BASE, ep.ALIAS);
    MAP_USBDevEndpointStatusClear(ep.USB_BASE, ep.ALIAS, st);
}
  };//USB
 class CAN{

 public:
  // ------------------------------------------------------------------------
    // Runtime transmission
    // ------------------------------------------------------------------------

    static void Send(const CAN_Message* msg)
    {

        // Hardware-specific implementation.
        //
        // msg.ID
        // msg.DLC
        // msg.Data
        //
        // Здесь уже можно сформировать tCANMsgObject
        // или непосредственно записать регистры Stellaris.
    }


    // ------------------------------------------------------------------------
    // Compile-time filter configuration
    // ------------------------------------------------------------------------

    template<CANFilter Filter>
    static void ConfigureRX()
    {
        
        // Filter::id
        // Filter::mask
        //
        // Здесь Stellaris-specific code:
        //
        // CAN message object
        // CANIntEnable()
        // CANMessageSet()
        // hardware ID mask
        // etc.
    }

 /*  void vwCAN_Init(){};

//прерывания
 void vwCAN_IntEnable()
 {
 };
 void vwCANIntDesable()
 {
 };
//настройка частоты по умолчанию
 void vwCAN_SetFrequency(unsigned long CANf)
 {
 };
//сброс
 void vwCAN_Reset();
 bool vwCAN_MerssageConfigureDefaultRX
 (uint8_t msg_obj_num,
 tCANMsgObject* Msg)
 {
 };

 bool vwCANMessageConfigureTX
 (uint32_t ID,
  uint32_t msg_obj_num,
  uint32_t flags,
  tCANMsgObject* Msg,
  uint8_t buf_len)
  {

 };
 bool vwCAN_MessageConfigureRX
 (uint8_t msg_obj_num, 
 uint32_t ID,
 uint32_t msk,
 uint32_t flags,
 tCANMsgObject* Msg,
 uint8_t buf_len)
 {
 
 };

 void CAN_SetSpeed(uint32_t bitrate);
  }//CAN


extern void CANBitTimingGet(unsigned long ulBase, tCANBitClkParms *pClkParms);
extern void CANBitTimingSet(unsigned long ulBase, tCANBitClkParms *pClkParms);
extern unsigned long CANBitRateSet(unsigned long ulBase,
                                   unsigned long ulSourceClock,
                                   unsigned long ulBitRate);
extern void CANDisable(unsigned long ulBase);
extern void CANEnable(unsigned long ulBase);
extern tBoolean CANErrCntrGet(unsigned long ulBase, unsigned long *pulRxCount,
                              unsigned long *pulTxCount);
extern void CANInit(unsigned long ulBase);
extern void CANIntClear(unsigned long ulBase, unsigned long ulIntClr);
extern void CANIntDisable(unsigned long ulBase, unsigned long ulIntFlags);
extern void CANIntEnable(unsigned long ulBase, unsigned long ulIntFlags);
extern void CANIntRegister(unsigned long ulBase, void (*pfnHandler)(void));
extern unsigned long CANIntStatus(unsigned long ulBase,
                                  tCANIntStsReg eIntStsReg);
extern void CANIntUnregister(unsigned long ulBase);
extern void CANMessageClear(unsigned long ulBase, unsigned long ulObjID);
extern void CANMessageGet(unsigned long ulBase, unsigned long ulObjID,
                          tCANMsgObject *pMsgObject, tBoolean bClrPendingInt);
extern void CANMessageSet(unsigned long ulBase, unsigned long ulObjID,
                          tCANMsgObject *pMsgObject, tMsgObjType eMsgType);
extern tBoolean CANRetryGet(unsigned long ulBase);
extern void CANRetrySet(unsigned long ulBase, tBoolean bAutoRetry);
extern unsigned long CANStatusGet(unsigned long ulBase, tCANStsReg eStatusReg);
*/
};
};//WRAP
/*
namespace example1 {

tCANBitClkParms CANBitClk;
tCANMsgObject sMsgObjectRx;
unsigned char ucBufferIn[8];
unsigned char ucBufferOut[8];
//
// Reset the state of all the message objects and the state of the CAN
// module to a known state.
//
CANInit(CAN0_BASE);
//
// Configure the controller for 1 Mbit operation.
//
CANBitRateSet(CAN0_BASE, 8000000, 1000000);
//
// Take the CAN0 device out of INIT state.

CANEnable(CAN0_BASE);
//
// Configure a receive object this CAN FIFO to receive message objects with
// message ID 0x400-0x407.
//
sMsgObjectRx.ulMsgID = (0x400);
sMsgObjectRx.ulMsgIDMask = 0x7f8;
sMsgObjectRx.ulFlags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_FIFO;
//
// The first three message objects have the MSG_OBJ_FIFO set to indicate
// that they are part of a FIFO.
//
CANMessageSet(CAN0_BASE, 1, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
CANMessageSet(CAN0_BASE, 2, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
CANMessageSet(CAN0_BASE, 3, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
//
// Last message object does not have the MSG_OBJ_FIFO set to indicate that
// this is the last message.
//
sMsgObjectRx.ulFlags = MSG_OBJ_USE_ID_FILTER;
CANMessageSet(CAN0_BASE, 4, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


tCANBitClkParms CANBitClk;
tCANMsgObject sMsgObjectRx;
tCANMsgObject sMsgObjectTx;
unsigned char ucBufferIn[8];
unsigned char ucBufferOut[8];
//
// Reset the state of all the message objects and the state of the CAN
// module to a known state.
//
CANInit(CAN0_BASE);
CANInit(CAN1_BASE);
//
// Configure the controller for 1 Mbit operation.
//
CANSetBitTiming(CAN1_BASE, &CANBitClk);
//
// Take the CAN0 device out of INIT state.
//
CANEnable(CAN0_BASE);
CANEnable(CAN1_BASE);
//
// Configure a receive object.
//
sMsgObjectRx.ulMsgID = (0x400);

sMsgObjectRx.ulMsgIDMask = 0x7f8;
sMsgObjectRx.ulFlags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_FIFO;
//
// The first three message objects have the MSG_OBJ_FIFO set to indicate
// that they are part of a FIFO.
//
CANMessageSet(CAN0_BASE, 1, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
CANMessageSet(CAN0_BASE, 2, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
CANMessageSet(CAN0_BASE, 3, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
//
// Last message object does not have the MSG_OBJ_FIFO set to indicate that
// this is the last message.
//
sMsgObjectRx.ulFlags = MSG_OBJ_USE_ID_FILTER;
CANMessageSet(CAN0_BASE, 4, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
//
// Configure and start transmit of message object.
//
sMsgObjectTx.ulMsgID = 0x400;
sMsgObjectTx.ulFlags = 0;
sMsgObjectTx.ulMsgLen = 8;
sMsgObjectTx.pucMsgData = ucBufferOut;
CANMessageSet(CAN0_BASE, 2, &sMsgObjectTx, MSG_OBJ_TYPE_TX);
//
// Wait for new data to become available.
//
while((CANStatusGet(CAN1_BASE, CAN_STS_NEWDAT) & 1) == 0)
{
//
// Read the message out of the message object.
//
CANMessageGet(CAN1_BASE, 1, &sMsgObjectRx, true);
}
//
// Process new data in sMsgObjectRx.pucMsgData.
//
...


}*/