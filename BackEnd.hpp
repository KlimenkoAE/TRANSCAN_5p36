#pragma once
#include<cstdint>
#include "USB_CLASSES.hpp"

template <class USBBackEnd,class TargetMCU>
class MyUSB
{
public:
static constexpr uint16_t EndpointConfig(PHYEndpoint<TargetMCU>& ep, uint32_t fifo_shift){

USBBackEnd::EndpointConfig( ep,fifo_shift);
};

  static uint32_t IntStatusControl(unsigned long ulBase)
  {
      return USBBackEnd::IntStatusControl(ulBase);
  }

  static uint32_t IntStatusEndpoint(unsigned long ulBase)
  {
      return USBBackEnd::IntStatusEndpoint(ulBase);
  }


static void IntEnableEndpoint(unsigned long ulBase, unsigned long ulFlags)
  {

      USBBackEnd::IntEnableEndpoint(ulBase, ulFlags);
  }

static void IntEnableControl(unsigned long ulBase, unsigned long ulFlags)
  {
      USBBackEnd::IntEnableControl(ulBase, ulFlags);
  }

    static void IntDisable(unsigned long base, unsigned long flags)
    {
        USBBackEnd::IntDisable(base, flags);
    }

    static void IntDisableControl(unsigned long base, unsigned long flags)
    {
        USBBackEnd::IntDisableControl(base, flags);
    }

    static void IntDisableEndpoint(unsigned long base, unsigned long flags)
    {
        USBBackEnd::IntDisableEndpoint(base, flags);
    }

    static void IntEnable(unsigned long base,unsigned long flags)
    {
        USBBackEnd::IntEnable(base, flags);
    }

    static void EndpointDataToggleClear(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDataToggleClear(base, endpoint, flags);
    }

    static void EndpointDMAChannel(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long channel)
    {
        USBBackEnd::EndpointDMAChannel(base,endpoint, channel);
    }

    static void EndpointDMADisable(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMADisable(base,endpoint, flags);
    }

    static void EndpointDMAEnable(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMAEnable(base,endpoint, flags);
    }

    static unsigned long EndpointStatus(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::EndpointStatus(base, endpoint);
    }

    static unsigned long FIFOAddrGet(
        unsigned long base,

        PHYEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::FIFOAddrGet(base, endpoint);
    }

    static void FIFOConfigGet(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* fifoAddress,
        unsigned long* fifoSize,
        unsigned long flags)
    {
        USBBackEnd::FIFOConfigGet(
            base,
            endpoint,
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOConfigSet(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long fifoAddress,
        unsigned long fifoSize,
        unsigned long flags)
    {
        USBBackEnd::FIFOConfigSet(
            base,
            endpoint,
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOFlush(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::FIFOFlush(base,endpoint, flags);
    }

    static unsigned long FrameNumberGet(unsigned long base)
    {
        return USBBackEnd::FrameNumberGet(base);
    }

    static unsigned long HostAddrGet(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        return USBBackEnd::HostAddrGet(base, endpoint, flags);
    }

    static void HostAddrSet(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long address,
        unsigned long flags)
    {
        USBBackEnd::HostAddrSet(
            base,
            endpoint,
            address,
            flags);
    }

    static void HostEndpointConfig(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long maxPayload,
        unsigned long nakPollInterval,
        unsigned long targetEndpoint,
        unsigned long flags)
    {
        USBBackEnd::HostEndpointConfig(
            base,
            endpoint,
            maxPayload,
            nakPollInterval,
            targetEndpoint,
            flags);
    }

    static void HostEndpointDataAck(
        unsigned long base,
         PHYEndpoint<TargetMCU>&endpoint)
    {
        USBBackEnd::HostEndpointDataAck(base, endpoint);
    }

    static void HostEndpointDataToggle(
        unsigned long base,
         PHYEndpoint<TargetMCU>&endpoint,
        bool dataToggle,
        unsigned long flags)
    {
        USBBackEnd::HostEndpointDataToggle(
            base,
            endpoint,
            dataToggle,
            flags);
    }

    static void HostEndpointStatusClear(
        unsigned long base,
         PHYEndpoint<TargetMCU>&endpoint,
        unsigned long flags)
    {
        USBBackEnd::HostEndpointStatusClear(
            base,
            endpoint,
            flags);
    }

    static unsigned long DevAddrGet(unsigned long base)
    {
        return USBBackEnd::DevAddrGet(base);
    }

    static void DevAddrSet(
        unsigned long base,
        unsigned long address)
    {
        USBBackEnd::DevAddrSet(base, address);
    }

    static void DevConnect(unsigned long base)
    {
        USBBackEnd::DevConnect(base);
    }

    static void DevDisconnect(unsigned long base)
    {
        USBBackEnd::DevDisconnect(base);
    }

    static void DevEndpointConfigGet(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* maxPacketSize,
        unsigned long* flags)
    {
        USBBackEnd::DevEndpointConfigGet(
            base,
            endpoint,
            maxPacketSize,
            flags);
    }

    static void DevEndpointConfigSet(
        PHYEndpoint<TargetMCU>& endpoint)
    {
        USBBackEnd::DevEndpointConfigSet(
            endpoint);
    }

    static void DevEndpointDataAck(
        const PHYEndpointBase<TargetMCU>& endpoint,
        bool isLastPacket)
    {
        USBBackEnd::DevEndpointDataAck(
            endpoint,
            isLastPacket);
    }


    static void DevEndpointStall(
        unsigned long base,
         PHYEndpointBase<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStall(
            endpoint,
            flags);
    }

    static void DevEndpointStallClear(
         PHYEndpointBase<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStallClear(
            endpoint,
            flags);
    }

    static void DevEndpointStatusClear(
        unsigned long base,
        PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStatusClear(
            base,
            endpoint,
            flags);
    }

    static void DevMode(unsigned long base)
    {
        USBBackEnd::DevMode(base);
    }

    static unsigned long EndpointDataAvail(
        unsigned long base,
       const  PHYEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::EndpointDataAvail(base,endpoint);
    }
    static unsigned long EndpointDataAvail(
        unsigned long base,
       const  PHYControlEndpoint<TargetMCU>& endpoint)
    {
        return USBBackEnd::EndpointDataAvail(base, endpoint);
    }
    static long EndpointDataGet(
         PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long* size)
    {
        return USBBackEnd::EndpointDataGet(
            endpoint,
            data,
            size);
    }

    static long EndpointDataPut(
        PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long size)
    {
        return USBBackEnd::EndpointDataPut(
            endpoint,
            data,
            size);
    }

    static long EndpointDataSend(
        unsigned long base,
         PHYEndpoint<TargetMCU>& endpoint,
        unsigned long transferType)
    {
        return USBBackEnd::EndpointDataSend(
            base,
            endpoint,
            transferType);
    }

       static void SelectEndpoit(
         uint32_t base,PHYEndpoint<TargetMCU>& epn)
    {
        USBBackEnd::SelectEndpoit(base, epn);
    }  
    
      
       static void SetEndpoitFIFO_Size(
        PHYEndpoint<TargetMCU>& epn,size_t size)
    {
        USBBackEnd::SelectEndpoit( epn,size);
    }
  static    unsigned long COMInterruptIndex(uint32_t int_COM_status)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
    USBBackEnd::COMInterruptIndex(int_COM_status);
};

static void UsbInit(const PHYControlEndpoint<Stellaris>& ctr_ep ){
USBBackEnd::UsbInit( ctr_ep );
}

static void EP_StatusClear(PHYEndpointBase<TargetMCU>& ep){

    USBBackEnd::EP_StatusClear(ep);
}
};