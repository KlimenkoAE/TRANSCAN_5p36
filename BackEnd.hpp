#pragma once
#include<cstdint>
#include "USB_CLASSES.hpp"
#include "CAN_CLASSES.hpp"

template <class BackEnd,class TargetMCU>
class TBackEnd{
public:
class USB
{
public:
static constexpr uint16_t EndpointConfig( const PHYEndpoint<TargetMCU>& ep, uint32_t fifo_shift){

return BackEnd::USB::vwEndpointConfig( ep,fifo_shift);
};

  static uint32_t IntStatusControl( const PHYEndpointBase<Stellaris>& endpoint)
  {
      return BackEnd::USB::vwIntStatusControl(endpoint);
  }

  static uint32_t IntStatusEndpoint( const PHYEndpointBase<Stellaris>& endpoint)
  {
      return BackEnd::USB::vwIntStatusEndpoint(endpoint);
  }


static void IntEnableEndpoint(
 const PHYEndpointBase<TargetMCU>& endpoint)
  {

      BackEnd::USB::vwIntEnableEndpoint(endpoint);
  }

static void IntEnableControl(unsigned long ulBase, unsigned long ulFlags)
  {
      BackEnd::USB::vwIntEnableControl(ulBase, ulFlags);
  }

    static void IntDisable(unsigned long base, unsigned long flags)
    {
        BackEnd::USB::vwIntDisable(base, flags);
    }

    static void IntDisableControl(unsigned long base, unsigned long flags)
    {
        BackEnd::USB::vwIntDisableControl(base, flags);
    }

    static void IntDisableEndpoint(const PHYEndpointBase<Stellaris>& endpoint)
    {
        BackEnd::USB::vwIntDisableEndpoint(endpoint);
    }

    static void USBIntEnable(unsigned long base,unsigned long flags)
    {
        BackEnd::USB::vwUSBIntEnable(base, flags);
    }

    static void EndpointDataToggleClear(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        BackEnd::USB::vwEndpointDataToggleClear(endpoint);
    }

    static void EndpointDMAChannel(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long channel)
    {
        BackEnd::USB::vwEndpointDMAChannel(base,endpoint, channel);
    }

    static void EndpointDMADisable(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        BackEnd::USB::vwEndpointDMADisable(base,endpoint, flags);
    }

    static void EndpointDMAEnable(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        BackEnd::USB::vwEndpointDMAEnable(base,endpoint, flags);
    }

    static unsigned long EndpointStatus(
         const PHYEndpoint<TargetMCU>& endpoint)

    {
        return BackEnd::USB::vwEndpointStatus(endpoint);
    }

    static unsigned long FIFOAddrGet(
        unsigned long base,

        const PHYEndpoint<TargetMCU>& endpoint)
    {
        return BackEnd::USB::vwFIFOAddrGet(base, endpoint);
    }

    static void FIFOConfigGet(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* fifoAddress,
        unsigned long* fifoSize,
        unsigned long flags)
    {
        BackEnd::USB::vwFIFOConfigGet(
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
        BackEnd::USB::vwFIFOConfigSet(
            base,
            endpoint,
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOFlush(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        BackEnd::USB::vwFIFOFlush(endpoint);
    }

    static unsigned long FrameNumberGet(unsigned long base)
    {
        return BackEnd::USB::vwFrameNumberGet(base);
    }

    static unsigned long HostAddrGet(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        return BackEnd::USB::vwHostAddrGet(base, endpoint, flags);
    }

    static void HostAddrSet(
        unsigned long base,
         const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long address,
        unsigned long flags)
    {
        BackEnd::USB::vwHostAddrSet(
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
        BackEnd::USB::vwHostEndpointConfig(
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
        BackEnd::USB::vwHostEndpointDataAck(base, endpoint);
    }

    static void HostEndpointDataToggle(
        unsigned long base,
         const PHYEndpoint<TargetMCU>&endpoint,
        bool dataToggle,
        unsigned long flags)
    {
        BackEnd::USB::vwHostEndpointDataToggle(
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
        BackEnd::USB::vwHostEndpointStatusClear(
            base,
            endpoint,
            flags);
    }

    static unsigned long DevAddrGet(unsigned long base)
    {
        return BackEnd::USB::vwDevAddrGet(base);
    }

    static void DevAddrSet(
        const PHYEndpointBase<Stellaris>& endpoint,
        unsigned long address)
    {
        BackEnd::USB::vwDevAddrSet(endpoint, address);
    }

    static void DevConnect(unsigned long base)
    {
        BackEnd::USB::vwDevConnect(base);
    }

    static void DevDisconnect(unsigned long base)
    {
        BackEnd::USB::vwDevDisconnect(base);
    }

    static void DevEndpointConfigGet(
        unsigned long base,
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long* maxPacketSize,
        unsigned long* flags)
    {
        BackEnd::USB::vwDevEndpointConfigGet(
            base,
            endpoint,
            maxPacketSize,
            flags);
    }

    static void DevEndpointConfigSet(
        const PHYEndpoint<TargetMCU>& endpoint)
    {
        BackEnd::USB::vwDevEndpointConfigSet(
            endpoint);
    }

    static void DevEndpointDataAck(
         const PHYEndpointBase<TargetMCU>& endpoint,
        bool isLastPacket)
    {
        BackEnd::USB::vwDevEndpointDataAck(
            endpoint,
            isLastPacket);
    }


    static void DevEndpointStall(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        BackEnd::USB::vwDevEndpointStall(
            endpoint);
    }

    static void DevEndpointStallClear(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        BackEnd::USB::vwDevEndpointStallClear(
            endpoint);
    }

    static void DevEndpointStatusClear(
        const PHYEndpoint<TargetMCU>& endpoint,
        unsigned long flags)
    {
        BackEnd::USB::vwDevEndpointStatusClear(
            endpoint,
            flags);
    }

    static void DevMode(unsigned long base)
    {
        BackEnd::USB::vwDevMode(base);
    }

    static unsigned long EndpointDataAvail(
         const PHYEndpointBase<TargetMCU>& endpoint)
    {
        return BackEnd::USB::vwEndpointDataAvail(endpoint);
    }
    static unsigned long EndpointDataAvail(
        unsigned long base,
         const PHYControlEndpoint<TargetMCU>& endpoint)
    {
        return BackEnd::USB::vwEndpointDataAvail(endpoint);
    }
    static long EndpointDataGet(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long* size)
    {
        return BackEnd::USB::vwEndpointDataGet(
            endpoint,
            data,
            size);
    }

    static long EndpointDataPut(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned char* data,
        unsigned long size)
    {
        return BackEnd::USB::vwEndpointDataPut(
            endpoint,
            data,
            size);
    }

    static long EndpointDataSend(
         const PHYEndpointBase<TargetMCU>& endpoint,
        unsigned long transferType)
    {
        return BackEnd::USB::vwEndpointDataSend(
            endpoint,
            transferType);
    }

       static void SelectEndpoit(const PHYEndpoint<TargetMCU>& epn)
    {
        BackEnd::USB::vwSelectEndpoit( epn);
    }  
    
      
       static void SetEndpoitFIFO_Size(
        const PHYEndpoint<TargetMCU>& epn,size_t size)
    {
        BackEnd::USB::vwSelectEndpoit( epn,size);
    }
  static    unsigned long COMInterruptIndex(uint32_t int_COM_status)//плучаем номер младшего установленного бита
{                                     //на этапе компиляции вычислит и присвоит лямбды в какомто порядке- не важно
  return  BackEnd::USB::vwCOMInterruptIndex(int_COM_status);
};

static void UsbInit( const PHYControlEndpoint<Stellaris>& ctr_ep ){
BackEnd::USB::vwUsbInit( ctr_ep );
}

static void EP_StatusClear(  const PHYEndpoint<TargetMCU>& ep){

    BackEnd::USB::vwEP_StatusClear(ep);
}
};
class CAN{
    // Передача runtime message
    // ------------------------------------------------------------------------
public:
    static void Send(const CAN_Message* msg)
    {
        BackEnd::CAN::Send(msg);
    }


    // ------------------------------------------------------------------------
    // Установка compile-time filter
    //
    // ID и Mask известны уже при компиляции.
    // Backend получает их как параметры типа.
    // ------------------------------------------------------------------------

    template<CANFilter Filter>
    static void ConfigureFilter()
    {
        BackEnd::CAN::template ConfigureRX<Filter>();
    }
};
};
