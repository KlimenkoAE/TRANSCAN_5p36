#pragma once
#include <cstdarg>
#include <cstdint>
extern "C"{
#include "hw_types.h"
#include "usb.h"
//#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
}



class StellarisWrap{



public:
  struct StellarisUSB
  {


  static uint32_t IntStatusControl(unsigned long ulBase)
  {
     return  MAP_USBIntStatusControl(ulBase);
  }

  static uint32_t IntStatusEndpoint(unsigned long ulBase)
  {
      return MAP_USBIntStatusEndpoint(ulBase);
  }
  ////////

static void IntEnableEndpoint(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntEnableEndpoint(ulBase, ulFlags);
  }

static void IntEnableControl(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntEnableControl(ulBase, ulFlags);
  }

  static void IntDisable(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntDisable(ulBase, ulFlags);
  }

  static void IntDisableControl(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntDisableControl(ulBase, ulFlags);
  }

  static void IntDisableEndpoint(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntDisableEndpoint(ulBase, ulFlags);
  }

  static void IntEnable(unsigned long ulBase, unsigned long ulFlags)
  {
      MAP_USBIntEnable(ulBase, ulFlags);
  }

  static void EndpointDataToggleClear(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDataToggleClear(ulBase, ulEndpoint, ulFlags);
  }

  static void EndpointDMAChannel(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulChannel)
  {
      MAP_USBEndpointDMAChannel(ulBase, ulEndpoint, ulChannel);
  }

  static void EndpointDMADisable(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMADisable(ulBase, ulEndpoint, ulFlags);
  }

  static void EndpointDMAEnable(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBEndpointDMAEnable(ulBase, ulEndpoint, ulFlags);
  }

  static unsigned long EndpointStatus(
      unsigned long ulBase,
      unsigned long ulEndpoint)
  {
      return MAP_USBEndpointStatus(ulBase, ulEndpoint);
  }

  static unsigned long FIFOAddrGet(
      unsigned long ulBase,
      unsigned long ulEndpoint)
  {
      return MAP_USBFIFOAddrGet(ulBase, ulEndpoint);
  }

  static void FIFOConfigGet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long* pulFIFOAddress,
      unsigned long* pulFIFOSize,
      unsigned long ulFlags)
  {
      MAP_USBFIFOConfigGet(
          ulBase,
          ulEndpoint,
          pulFIFOAddress,
          pulFIFOSize,
          ulFlags);
  }

  static void FIFOConfigSet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFIFOAddress,
      unsigned long ulFIFOSize,
      unsigned long ulFlags)
  {
      MAP_USBFIFOConfigSet(
          ulBase,
          ulEndpoint,
          ulFIFOAddress,
          ulFIFOSize,
          ulFlags);
  }

  static void FIFOFlush(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBFIFOFlush(ulBase, ulEndpoint, ulFlags);
  }

  static unsigned long FrameNumberGet(unsigned long ulBase)
  {
      return MAP_USBFrameNumberGet(ulBase);
  }

  static unsigned long HostAddrGet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      return MAP_USBHostAddrGet(ulBase, ulEndpoint, ulFlags);
  }

  static void HostAddrSet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulAddr,
      unsigned long ulFlags)
  {
      MAP_USBHostAddrSet(ulBase, ulEndpoint, ulAddr, ulFlags);
  }

  static void HostEndpointConfig(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulMaxPayload,
      unsigned long ulNAKPollInterval,
      unsigned long ulTargetEndpoint,
      unsigned long ulFlags)
  {
      USBHostEndpointConfig(
          ulBase,
          ulEndpoint,
          ulMaxPayload,
          ulNAKPollInterval,
          ulTargetEndpoint,
          ulFlags);
  }

  static void HostEndpointDataAck(
      unsigned long ulBase,
      unsigned long ulEndpoint)
  {
      MAP_USBHostEndpointDataAck(ulBase, ulEndpoint);
  }

  static void HostEndpointDataToggle(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      bool bDataToggle,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointDataToggle(
          ulBase,
          ulEndpoint,
          bDataToggle,
          ulFlags);
  }

  static void HostEndpointStatusClear(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBHostEndpointStatusClear(
          ulBase,
          ulEndpoint,
          ulFlags);
  }

  static unsigned long DevAddrGet(unsigned long ulBase)
  {
      return MAP_USBDevAddrGet(ulBase);
  }

  static void DevAddrSet(
      unsigned long ulBase,
      unsigned long ulAddress)
  {
      MAP_USBDevAddrSet(ulBase, ulAddress);
  }

  static void DevConnect(unsigned long ulBase)
  {
      MAP_USBDevConnect(ulBase);
  }

  static void DevDisconnect(unsigned long ulBase)
  {
      MAP_USBDevDisconnect(ulBase);
  }

  static void DevEndpointConfigGet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long* pulMaxPacketSize,
      unsigned long* pulFlags)
  {
      MAP_USBDevEndpointConfigGet(
          ulBase,
          ulEndpoint,
          pulMaxPacketSize,
          pulFlags);
  }

  static void DevEndpointConfigSet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulMaxPacketSize,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointConfigSet(
          ulBase,
          ulEndpoint,
          ulMaxPacketSize,
          ulFlags);
  }

  static void DevEndpointDataAck(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      bool bIsLastPacket)
  {
      MAP_USBDevEndpointDataAck(
          ulBase,
          ulEndpoint,
          bIsLastPacket);
  }

  static void DevEndpointStall(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStall(
          ulBase,
          ulEndpoint,
          ulFlags);
  }

  static void DevEndpointStallClear(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStallClear(
          ulBase,
          ulEndpoint,
          ulFlags);
  }

  static void DevEndpointStatusClear(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned long ulFlags)
  {
      MAP_USBDevEndpointStatusClear(
          ulBase,
          ulEndpoint,
          ulFlags);
  }

  static void DevMode(unsigned long ulBase)
  {
      MAP_USBDevMode(ulBase);
  }

  static unsigned long EndpointDataAvail(
      unsigned long ulBase,
      unsigned long ulEndpoint)
  {
      return MAP_USBEndpointDataAvail(
          ulBase,
          ulEndpoint);
  }

  static long EndpointDataGet(
      unsigned long ulBase,
      unsigned long ulEndpoint,
      unsigned char* pucData,
      unsigned long* pulSize)
    {
        return MAP_USBEndpointDataGet(
            ulBase,
            ulEndpoint,
            pucData,
            pulSize);
    }

    static long EndpointDataPut(
        unsigned long ulBase,
        unsigned long ulEndpoint,
        unsigned char* pucData,
        unsigned long ulSize)
    {
        return MAP_USBEndpointDataPut(
            ulBase,
            ulEndpoint,
            pucData,
            ulSize);
    }

    static long EndpointDataSend(
        unsigned long ulBase,
        unsigned long ulEndpoint,
        unsigned long ulTransType)
    {
        return MAP_USBEndpointDataSend(
            ulBase,
            ulEndpoint,
            ulTransType);
    }

  };
};


template <class USBBackEnd>
class MyUSB
{
public:


  static uint32_t IntStatusControl(unsigned long ulBase)
  {
      USBBackEnd::IntStatusControl(ulBase);
  }

  static uint32_t IntStatusEndpoint(unsigned long ulBase)
  {
      USBBackEnd::IntStatusEndpoint(ulBase);
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

    static void IntEnable(unsigned long base, unsigned long flags)
    {
        USBBackEnd::IntEnable(base, flags);
    }

    static void EndpointDataToggleClear(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDataToggleClear(base, endpoint, flags);
    }

    static void EndpointDMAChannel(
        unsigned long base,
        unsigned long endpoint,
        unsigned long channel)
    {
        USBBackEnd::EndpointDMAChannel(base, endpoint, channel);
    }

    static void EndpointDMADisable(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMADisable(base, endpoint, flags);
    }

    static void EndpointDMAEnable(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::EndpointDMAEnable(base, endpoint, flags);
    }

    static unsigned long EndpointStatus(
        unsigned long base,
        unsigned long endpoint)
    {
        return USBBackEnd::EndpointStatus(base, endpoint);
    }

    static unsigned long FIFOAddrGet(
        unsigned long base,
        unsigned long endpoint)
    {
        return USBBackEnd::FIFOAddrGet(base, endpoint);
    }

    static void FIFOConfigGet(
        unsigned long base,
        unsigned long endpoint,
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
        unsigned long endpoint,
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
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::FIFOFlush(base, endpoint, flags);
    }

    static unsigned long FrameNumberGet(unsigned long base)
    {
        return USBBackEnd::FrameNumberGet(base);
    }

    static unsigned long HostAddrGet(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        return USBBackEnd::HostAddrGet(base, endpoint, flags);
    }

    static void HostAddrSet(
        unsigned long base,
        unsigned long endpoint,
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
        unsigned long endpoint,
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
        unsigned long endpoint)
    {
        USBBackEnd::HostEndpointDataAck(base, endpoint);
    }

    static void HostEndpointDataToggle(
        unsigned long base,
        unsigned long endpoint,
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
        unsigned long endpoint,
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
        unsigned long endpoint,
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
        unsigned long base,
        unsigned long endpoint,
        unsigned long maxPacketSize,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointConfigSet(
            base,
            endpoint,
            maxPacketSize,
            flags);
    }

    static void DevEndpointDataAck(
        unsigned long base,
        unsigned long endpoint,
        bool isLastPacket)
    {
        USBBackEnd::DevEndpointDataAck(
            base,
            endpoint,
            isLastPacket);
    }

    static void DevEndpointStall(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStall(
            base,
            endpoint,
            flags);
    }

    static void DevEndpointStallClear(
        unsigned long base,
        unsigned long endpoint,
        unsigned long flags)
    {
        USBBackEnd::DevEndpointStallClear(
            base,
            endpoint,
            flags);
    }

    static void DevEndpointStatusClear(
        unsigned long base,
        unsigned long endpoint,
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
        unsigned long endpoint)
    {
        return USBBackEnd::EndpointDataAvail(base, endpoint);
    }

    static long EndpointDataGet(
        unsigned long base,
        unsigned long endpoint,
        unsigned char* data,
        unsigned long* size)
    {
        return USBBackEnd::EndpointDataGet(
            base,
            endpoint,
            data,
            size);
    }

    static long EndpointDataPut(
        unsigned long base,
        unsigned long endpoint,
        unsigned char* data,
        unsigned long size)
    {
        return USBBackEnd::EndpointDataPut(
            base,
            endpoint,
            data,
            size);
    }

    static long EndpointDataSend(
        unsigned long base,
        unsigned long endpoint,
        unsigned long transferType)
    {
        return USBBackEnd::EndpointDataSend(
            base,
            endpoint,
            transferType);
    }
};






