#pragma once
#include<cstdint>
template <class USBBackEnd,class TargetMCU>
class MyUSB
{
public:


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
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDataToggleClear(base, VendorConsts<TargetMCU>::Endpoint(endpoint), flags);
    }

    static void EndpointDMAChannel(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long channel)
    {
        USBBackEnd::EndpointDMAChannel(base,VendorConsts<TargetMCU>::Endpoint(endpoint), channel);
    }

    static void EndpointDMADisable(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMADisable(base, VendorConsts<TargetMCU>::Endpoint(endpoint), flags);
    }

    static void EndpointDMAEnable(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMAEnable(base, VendorConsts<TargetMCU>::Endpoint(endpoint), flags);
    }

    static unsigned long EndpointStatus(
        unsigned long base,
        MyUSB_EP endpoint)
    {
        return USBBackEnd::EndpointStatus(base, VendorConsts<TargetMCU>::Endpoint(endpoint));
    }

    static unsigned long FIFOAddrGet(
        unsigned long base,
        MyUSB_EP endpoint)
    {
        return USBBackEnd::FIFOAddrGet(base, VendorConsts<TargetMCU>::Endpoint(endpoint));
    }

    static void FIFOConfigGet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long* fifoAddress,
        unsigned long* fifoSize,
        unsigned long flags)
    {
        USBBackEnd::FIFOConfigGet(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOConfigSet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long fifoAddress,
        unsigned long fifoSize,
        unsigned long flags)
    {
        USBBackEnd::FIFOConfigSet(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            fifoAddress,
            fifoSize,
            flags);
    }

    static void FIFOFlush(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::FIFOFlush(base, VendorConsts<TargetMCU>::Endpoint(endpoint), flags);
    }

    static unsigned long FrameNumberGet(unsigned long base)
    {
        return USBBackEnd::FrameNumberGet(base);
    }

    static unsigned long HostAddrGet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        return USBBackEnd::HostAddrGet(base, VendorConsts<USBBackEnd>::Endpoint(endpoint), flags);
    }

    static void HostAddrSet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long address,
        unsigned long flags)
    {
        USBBackEnd::HostAddrSet(
            base,
            VendorConsts<USBBackEnd>::Endpoint(endpoint),
            address,
            flags);
    }

    static void HostEndpointConfig(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long maxPayload,
        unsigned long nakPollInterval,
        unsigned long targetEndpoint,
        unsigned long flags)
    {
        USBBackEnd::HostEndpointConfig(
            base,
            VendorConsts<USBBackEnd>::Endpoint(endpoint),
            maxPayload,
            nakPollInterval,
            targetEndpoint,
            flags);
    }

    static void HostEndpointDataAck(
        unsigned long base,
        MyUSB_EP endpoint)
    {
        USBBackEnd::HostEndpointDataAck(base, VendorConsts<USBBackEnd>::Endpoint(endpoint));
    }

    static void HostEndpointDataToggle(
        unsigned long base,
        MyUSB_EP endpoint,
        bool dataToggle,
        unsigned long flags)
    {
        USBBackEnd::HostEndpointDataToggle(
            base,
            VendorConsts<USBBackEnd>::Endpoint(endpoint),
            dataToggle,
            flags);
    }

    static void HostEndpointStatusClear(
        unsigned long base,
        MyUSB_EP endpoint,
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
        MyUSB_EP endpoint,
        unsigned long* maxPacketSize,
        unsigned long* flags)
    {
        USBBackEnd::DevEndpointConfigGet(
            base,
            VendorConsts<USBBackEnd>::Endpoint(endpoint),
            maxPacketSize,
            flags);
    }

    static void DevEndpointConfigSet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long maxPacketSize,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointConfigSet(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            maxPacketSize,
            flags);
    }

    static void DevEndpointDataAck(
        unsigned long base,
        MyUSB_EP endpoint,
        bool isLastPacket)
    {
        USBBackEnd::DevEndpointDataAck(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            isLastPacket);
    }

    static void DevEndpointStall(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStall(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            flags);
    }

    static void DevEndpointStallClear(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStallClear(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            flags);
    }

    static void DevEndpointStatusClear(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStatusClear(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            flags);
    }

    static void DevMode(unsigned long base)
    {
        USBBackEnd::DevMode(base);
    }

    static unsigned long EndpointDataAvail(
        unsigned long base,
        MyUSB_EP endpoint)
    {
        return USBBackEnd::EndpointDataAvail(base, VendorConsts<TargetMCU>::Endpoint(endpoint));
    }

    static long EndpointDataGet(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned char* data,
        unsigned long* size)
    {
        return USBBackEnd::EndpointDataGet(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            data,
            size);
    }

    static long EndpointDataPut(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned char* data,
        unsigned long size)
    {
        return USBBackEnd::EndpointDataPut(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            data,
            size);
    }

    static long EndpointDataSend(
        unsigned long base,
        MyUSB_EP endpoint,
        unsigned long transferType)
    {
        return USBBackEnd::EndpointDataSend(
            base,
            VendorConsts<TargetMCU>::Endpoint(endpoint),
            transferType);
    }

       static void SelectEndpoit(
        uint8_t epn)
    {
        USBBackEnd::SelectEndpoit( epn);
    }
};