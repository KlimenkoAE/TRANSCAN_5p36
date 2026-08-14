#pragma once
#include <cstdarg>
#include <cstdint>

#include "wrappers_headers.hpp"

template <>
class FunctionWraper<Stellaris>{
public:
  class USB{
public:

static constexpr uint16_t EndpointConfig(PHYEndpoint<Stellaris>& ep, uint16_t fifo_shift){


SelectEndpoit(ep);

DevEndpointConfigSet(ep);
          //ep.USB_BASE,
          //ep.ALIAS, 
          //ep.SZ,
          //ep.FIFO.CFG_FLAGS);
          //USB_EP_MODE_INT|USB_EP_DEV_IN
          //|USB_EP_AUTO_SET|USB_EP_DMA_MODE_0
     

SetEndpoitFIFO_Size(ep);

  FIFOConfigSet(ep,fifo_shift);

return  fifo_shift+=ep.SZ*(ep.FIFO.DoubleBuffered?2:1);

};

static constexpr void UsbInit(const PHYControlEndpoint<Stellaris>& ctr_ep ){

////////USB INIT
 MAP_SysCtlPeripheralEnable(ctr_ep.INIT_DATA.SysCtlPeriferal );



  MAP_SysCtlUSBPLLEnable();
  
  MAP_USBIntDisable(ctr_ep.USB_BASE, ctr_ep.INIT_DATA.INT_USBDevice);

  MAP_USBIntDisableControl(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_GEN_FlagsAll);
  MAP_USBIntEnableControl(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_GEN_Flags_Enable);

  MAP_USBIntDisableEndpoint(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_All);
  MAP_USBIntEnableEndpoint(ctr_ep.USB_BASE,ctr_ep.INIT_DATA.INT_EP0);

  MAP_USBIntEnable(ctr_ep.USB_BASE, ctr_ep.INIT_DATA.INT_USBDevice );

  MAP_USBDevConnect(ctr_ep.USB_BASE);
}


  static uint32_t IntStatusControl(PHYEndpointBase<Stellaris>& endpoint)
  {
     return  MAP_USBIntStatusControl(endpoint.USB_BASE);
  }

  static uint32_t IntStatusEndpoint(PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBIntStatusEndpoint(endpoint.USB_BASE);
  }
  ////////

static void IntEnableEndpoint(PHYEndpointBase<Stellaris>& endpoint ,unsigned long ulFlags)
  {
      MAP_USBIntEnableEndpoint(endpoint.USB_BASE, ulFlags);
  }

static void IntEnableControl(PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntEnableControl(endpoint.USB_BASE, ulFlags);
  }

  static void IntDisable(PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntDisable(endpoint.USB_BASE, ulFlags);
  }

  static void IntDisableControl(PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntDisableControl(endpoint.USB_BASE, ulFlags);
  }

  static void IntDisableEndpoint(PHYEndpointBase<Stellaris>& endpoint, unsigned long ulFlags)
  {
      MAP_USBIntDisableEndpoint(endpoint.USB_BASE, ulFlags);
  }

  static void IntEnable(PHYEndpointBase<Stellaris>& endpoint,   unsigned long ulFlags)
  {
      MAP_USBIntEnable(endpoint.USB_BASE, ulFlags);
  }

  static void EndpointDataToggleClear(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDataToggleClear(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static void EndpointDMAChannel(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulChannel)
  {
      MAP_USBEndpointDMAChannel(endpoint.USB_BASE, endpoint.ALIAS, ulChannel);
  }

  static void EndpointDMADisable(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMADisable(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static void EndpointDMAEnable(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMAEnable(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static unsigned long EndpointStatus(
      
      PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBEndpointStatus(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static unsigned long FIFOAddrGet(
      
      PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBFIFOAddrGet(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static void FIFOConfigGet(
      
      PHYEndpointBase<Stellaris>& endpoint,
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

  static void FIFOConfigSet(
      
      PHYEndpoint<Stellaris>& endpoint,
      unsigned long ulFIFOAddress)
  {
      MAP_USBFIFOConfigSet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFIFOAddress,
          endpoint.FIFO.SZ,
          endpoint.FIFO.CFG_FLAGS);
  }

  static void FIFOFlush(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBFIFOFlush(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static unsigned long FrameNumberGet(PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBFrameNumberGet(endpoint.USB_BASE);
  }

  static unsigned long HostAddrGet(    
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      return MAP_USBHostAddrGet(endpoint.USB_BASE, endpoint.ALIAS, ulFlags);
  }

  static void HostAddrSet(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulAddr,
      unsigned long ulFlags)
  {
      MAP_USBHostAddrSet(endpoint.USB_BASE, endpoint.ALIAS, ulAddr, ulFlags);
  }

  static void HostEndpointConfig(
      
      PHYEndpointBase<Stellaris>& endpoint,
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

  static void HostEndpointDataAck(
      
      PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBHostEndpointDataAck(endpoint.USB_BASE, endpoint.ALIAS);
  }

  static void HostEndpointDataToggle(
      
      PHYEndpointBase<Stellaris>& endpoint,
      bool bDataToggle,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointDataToggle(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          bDataToggle,
          ulFlags);
  }

  static void HostEndpointStatusClear(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointStatusClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static unsigned long DevAddrGet(PHYEndpointBase<Stellaris>& endpoint)
  {
      return MAP_USBDevAddrGet(endpoint.USB_BASE);
  }

  static void DevAddrSet(
      PHYEndpointBase<Stellaris>& endpoint,     
      unsigned long ulAddress)
  {
      MAP_USBDevAddrSet(endpoint.USB_BASE, ulAddress);
  }

  static void DevConnect(PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevConnect(endpoint.USB_BASE);
  }

  static void DevDisconnect(PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevDisconnect(endpoint.USB_BASE);
  }

  static void DevEndpointConfigGet(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long* pulMaxPacketSize,
      unsigned long* pulFlags)
  {
      MAP_USBDevEndpointConfigGet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          pulMaxPacketSize,
          pulFlags);
  }

  static void DevEndpointConfigSet(
      
      PHYEndpoint<Stellaris>& endpoint)
  {
      MAP_USBDevEndpointConfigSet(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          endpoint.SZ,
          endpoint.CFG_FLAGS);
  }

  static void DevEndpointDataAck(
      PHYEndpointBase<Stellaris>& endpoint,
      bool bIsLastPacket)
  {
      MAP_USBDevEndpointDataAck(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          bIsLastPacket);
  }

  static void DevEndpointStall(
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStall(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static void DevEndpointStallClear(
      const PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStallClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static void DevEndpointStatusClear(
      
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStatusClear(
          endpoint.USB_BASE,
          endpoint.ALIAS,
          ulFlags);
  }

  static void DevMode(PHYEndpointBase<Stellaris>& endpoint)
  {
      MAP_USBDevMode(endpoint.USB_BASE);
  }

  static unsigned long EndpointDataAvail(
     const PHYEndpointBase<Stellaris>& endpoint )
  {
      return MAP_USBEndpointDataAvail(
          endpoint.USB_BASE,
          endpoint.ALIAS);
  }
  static unsigned long EndpointDataAvail(
   const   PHYControlEndpoint<Stellaris>& endpoint)
  {
      return MAP_USBEndpointDataAvail(
          endpoint.USB_BASE,
          endpoint.ALIAS);
  }
  static long EndpointDataGet(
      PHYEndpointBase<Stellaris>& endpoint,
      unsigned char* pucData,
      unsigned long* pulSize)
    {
        return MAP_USBEndpointDataGet(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            pucData,
            pulSize);
    }

    static long EndpointDataPut(
        PHYEndpointBase<Stellaris>& endpoint,
        unsigned char* pucData,
        unsigned long ulSize)
    {
        return MAP_USBEndpointDataPut(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            pucData,
            ulSize);
    }

    static long EndpointDataSend(
        
        PHYEndpointBase<Stellaris>& endpoint,
        unsigned long ulTransType)
    {
        return MAP_USBEndpointDataSend(
            endpoint.USB_BASE,
            endpoint.ALIAS,
            ulTransType);
    }
static void SelectEndpoit(PHYEndpointBase<Stellaris>& endpoint){

//        USB0_EPIDX_R=epn;
        *((uint32_t*)(endpoint.USB_BASE+USBVndCnst::USB_REG(USBVndCnst::MyUSB_REG::EPIDX)))=endpoint.IDX;
      }

static void SetEndpoitFIFO_Size(
        PHYEndpoint<Stellaris>& endpoint)
    {
    uint8_t ep_dir=endpoint.ADDR>>8;

       *(
          (uint32_t*)(endpoint.USB_BASE+USBVndCnst::EP_REG(
                                                (endpoint.IDX, (ep_dir==8?USBVndCnst::MyUSB_EP_REG::TXMAXP:
                                                                               USBVndCnst::MyUSB_EP_REG::RXMAXP
                                                                               )
                                               )
                     )
        )=endpoint.FIFO.SZ;
    }
static  constexpr unsigned COMInterruptIndex(uint32_t int_COM_status)//плучаем номер младшего установленного бита
    {                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
        unsigned b = std::__countr_zero(int_COM_status);

        return (b < 16) ? (b - 1)       // IN
                        : (31 - b + 15);// OUT
    }
    static void EP_StatusClear(PHYEndpointBase<Stellaris>& ep){
    uint32_t st  = MAP_USBEndpointStatus(ep.USB_BASE, ep.ALIAS);
    MAP_USBDevEndpointStatusClear(ep.USB_BASE, ep.ALIAS, st);
}
  };//USB
};//WRAP

