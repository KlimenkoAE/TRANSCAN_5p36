#pragma once
#include<cstdint>
#include "USB_CLASSES.hpp"

template <class USBBackEnd,class TargetMCU>
class MyUSB
{
public:
static constexpr uint16_t EndpointConfig( const PHYEndpoint<TargetMCU>& ep, uint32_t fifo_shift){

return USBBackEnd::vwEndpointConfig( ep,fifo_shift);
};

  static uint32_t IntStatusControl( const PHYEndpointBase<Stellaris>& endpoint)
  {
      return USBBackEnd::vwIntStatusControl(endpoint);
  }

  static uint32_t IntStatusEndpoint( const PHYEndpointBase<Stellaris>& endpoint)
  {
      return USBBackEnd::vwIntStatusEndpoint(endpoint);
  }


static void IntEnableEndpoint(
 const PHYEndpointBase<TargetMCU>& endpoint)
  {

      USBBackEnd::vwIntEnableEndpoint(endpoint);
  }

static void IntEnableControl(unsigned long ulBase, unsigned long ulFlags)
  {
      USBBackEnd::vwIntEnableControl(ulBase, ulFlags);
  }

    static void IntDisable(unsigned long base, unsigned long flags)
    {
        USBBackEnd::vwIntDisable(base, flags);
    }

    static void IntDisableControl(unsigned long base, unsigned long flags)
    {
        USBBackEnd::vwIntDisableControl(base, flags);
    }

    static void IntDisableEndpoint(const PHYEndpointBase<Stellaris>& endpoint)
    {
        USBBackEnd::vwIntDisableEndpoint(endpoint);
    }

    static void USBIntEnable(unsigned long base,unsigned long flags)
    {
        USBBackEnd::vwUSBIntEnable(base, flags);
    }

    static void EndpointDataToggleClear(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        USBBackEnd::vwEndpointDataToggleClear(endpoint);
    }

    static void EndpointDMAChannel(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long channel)
    {
        USBBackEnd::vwEndpointDMAChannel(base,endpoint, channel);
    }

    static void EndpointDMADisable(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::vwEndpointDMADisable(base,endpoint, flags);
    }

    static void EndpointDMAEnable(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::vwEndpointDMAEnable(base,endpoint, flags);
    }

    static unsigned long EndpointStatus(
         const PHYEndpoint<TargetMCU>& endpoint)

    {
        return USBBackEnd::vwEndpointStatus(endpoint);
    }

    static unsigned long FIFOAddrGet(
        unsigned long base,

        const PHYEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::vwFIFOAddrGet(base, endpoint);
    }

    static void FIFOConfigGet(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* fifoAddress,
        unsigned long* fifoSize,
        unsigned long flags)
    {
        USBBackEnd::vwFIFOConfigGet(
            base,
            endpoint,
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOConfigSet(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long fifoAddress,
        unsigned long fifoSize,
        unsigned long flags)
    {
        USBBackEnd::vwFIFOConfigSet(
            base,
            endpoint,
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOFlush(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        USBBackEnd::vwFIFOFlush(endpoint);
    }

    static unsigned long FrameNumberGet(unsigned long base)
    {
        return USBBackEnd::vwFrameNumberGet(base);
    }

    static unsigned long HostAddrGet(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        return USBBackEnd::vwHostAddrGet(base, endpoint, flags);
    }

    static void HostAddrSet(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long address,
        unsigned long flags)
    {
        USBBackEnd::vwHostAddrSet(
            base,
            endpoint,
            address,
            flags);
    }

    static void HostEndpointConfig(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long maxPayload,
        unsigned long nakPollInterval,
        unsigned long targetEndpoint,
        unsigned long flags)
    {
        USBBackEnd::vwHostEndpointConfig(
            base,
            endpoint,
            maxPayload,
            nakPollInterval,
            targetEndpoint,
            flags);
    }

    static void HostEndpointDataAck(
        unsigned long base,
         const PHYEndpoint<TargetMCU>&endpoint)
    {
        USBBackEnd::vwHostEndpointDataAck(base, endpoint);
    }

    static void HostEndpointDataToggle(
        unsigned long base,
         const PHYEndpoint<TargetMCU>&endpoint,
        bool dataToggle,
        unsigned long flags)
    {
        USBBackEnd::vwHostEndpointDataToggle(
            base,
            endpoint,
            dataToggle,
            flags);
    }

    static void HostEndpointStatusClear(
        unsigned long base,
         const PHYEndpoint<TargetMCU>&endpoint,
        unsigned long flags)
    {
        USBBackEnd::vwHostEndpointStatusClear(
            base,
            endpoint,
            flags);
    }

    static unsigned long DevAddrGet(unsigned long base)
    {
        return USBBackEnd::vwDevAddrGet(base);
    }

    static void DevAddrSet(
        const PHYEndpointBase<Stellaris>& endpoint,
        unsigned long address)
    {
        USBBackEnd::vwDevAddrSet(endpoint, address);
    }

    static void DevConnect(unsigned long base)
    {
        USBBackEnd::vwDevConnect(base);
    }

    static void DevDisconnect(unsigned long base)
    {
        USBBackEnd::vwDevDisconnect(base);
    }

    static void DevEndpointConfigGet(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* maxPacketSize,
        unsigned long* flags)
    {
        USBBackEnd::vwDevEndpointConfigGet(
            base,
            endpoint,
            maxPacketSize,
            flags);
    }

    static void DevEndpointConfigSet(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        USBBackEnd::vwDevEndpointConfigSet(
            endpoint);
    }

    static void DevEndpointDataAck(
         const PHYEndpointBase<TargetMCU>& endpoint,
        bool isLastPacket)
    {
        USBBackEnd::vwDevEndpointDataAck(
            endpoint,
            isLastPacket);
    }


    static void DevEndpointStall(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        USBBackEnd::vwDevEndpointStall(
            endpoint);
    }

    static void DevEndpointStallClear(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        USBBackEnd::vwDevEndpointStallClear(
            endpoint);
    }

    static void DevEndpointStatusClear(
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::vwDevEndpointStatusClear(
            endpoint,
            flags);
    }

    static void DevMode(unsigned long base)
    {
        USBBackEnd::vwDevMode(base);
    }

    static unsigned long EndpointDataAvail(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        return USBBackEnd::vwEndpointDataAvail(endpoint);
    }
    static unsigned long EndpointDataAvail(
        unsigned long base,
         const PHYControlEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::vwEndpointDataAvail(endpoint);
    }
    static long EndpointDataGet(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long* size)
    {
        return USBBackEnd::vwEndpointDataGet(
            endpoint,
            data,
            size);
    }

    static long EndpointDataPut(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long size)
    {
        return USBBackEnd::vwEndpointDataPut(
            endpoint,
            data,
            size);
    }

    static long EndpointDataSend(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned long transferType)
    {
        return USBBackEnd::vwEndpointDataSend(
            endpoint,
            transferType);
    }

       static void SelectEndpoit(const PHYEndpoint<TargetMCU>& epn)
    {
        USBBackEnd::vwSelectEndpoit( epn);
    }  
    
      
       static void SetEndpoitFIFO_Size(
        const PHYEndpoint<TargetMCU>& epn,size_t size)
    {
        USBBackEnd::vwSelectEndpoit( epn,size);
    }
  static    unsigned long COMInterruptIndex(uint32_t int_COM_status)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
  return  USBBackEnd::vwCOMInterruptIndex(int_COM_status);
};

static void UsbInit( const PHYControlEndpoint<Stellaris>& ctr_ep ){
USBBackEnd::vwUsbInit( ctr_ep );
}

static void EP_StatusClear(  const PHYEndpoint<TargetMCU>& ep){

    USBBackEnd::vwEP_StatusClear(ep);
}
};