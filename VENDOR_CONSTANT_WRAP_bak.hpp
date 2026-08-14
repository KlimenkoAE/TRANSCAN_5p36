#pragma once

#include <cstdint>
#include "USB_CLASSES.hpp"
#include "wrappers_headers.hpp"

//#include "USB_THIS_PROGRAM_DEFS.hpp"


template <>
class VendorConsts<Stellaris>{
public:
static constexpr unsigned long Endpoint(
        MyUSB_EP ep)
{
        return (uint32_t)ep<<4;
}
static constexpr uint32_t INTEP_IN(MyUSB_EP  ep)
    {
        constexpr uint32_t mask[] =
        {
            USB_INTEP_0 ,
            USB_INTEP_DEV_IN_1,
            USB_INTEP_DEV_IN_2,
            USB_INTEP_DEV_IN_3,
            USB_INTEP_DEV_IN_4,
            USB_INTEP_DEV_IN_5,
            USB_INTEP_DEV_IN_6,
            USB_INTEP_DEV_IN_7,
            USB_INTEP_DEV_IN_8,
            USB_INTEP_DEV_IN_9,
            USB_INTEP_DEV_IN_10,
            USB_INTEP_DEV_IN_11,
            USB_INTEP_DEV_IN_12,
            USB_INTEP_DEV_IN_13,
            USB_INTEP_DEV_IN_14,
            USB_INTEP_DEV_IN_15

        };

        return mask[static_cast<uint8_t>(ep)];
    }
static constexpr uint32_t INTEP_OUT(MyUSB_EP  ep)
    {
        constexpr uint32_t mask[] =
        {
            USB_INTEP_0 ,
            USB_INTEP_DEV_OUT_1,
            USB_INTEP_DEV_OUT_2,
            USB_INTEP_DEV_OUT_3,
            USB_INTEP_DEV_OUT_4,
            USB_INTEP_DEV_OUT_5,
            USB_INTEP_DEV_OUT_6,
            USB_INTEP_DEV_OUT_7,
            USB_INTEP_DEV_OUT_8,
            USB_INTEP_DEV_OUT_9,
            USB_INTEP_DEV_OUT_10,
            USB_INTEP_DEV_OUT_11,
            USB_INTEP_DEV_OUT_12,
            USB_INTEP_DEV_OUT_13,
            USB_INTEP_DEV_OUT_14,
            USB_INTEP_DEV_OUT_15

        };

        return mask[static_cast<uint8_t>(ep)];
    }
    static constexpr uint32_t EP_CFG(MyUSB_EP_CFG  cf)
      {
        constexpr uint32_t mask[] =
        {
          USB_EP_AUTO_SET         ,  // Auto set feature enabled
          USB_EP_AUTO_REQUEST     ,  // Auto request feature enabled
          USB_EP_AUTO_CLEAR       ,  // Auto clear feature enabled
          USB_EP_DMA_MODE_0       ,  // Enable DMA access using mode 0
          USB_EP_DMA_MODE_1       ,  // Enable DMA access using mode 1
          USB_EP_MODE_ISOC        ,  // Isochronous endpoint
          USB_EP_MODE_BULK        ,  // Bulk endpoint
          USB_EP_MODE_INT         ,  // Interrupt endpoint
          USB_EP_MODE_CTRL        ,  // Control endpoint
          USB_EP_MODE_MASK        ,  // Mode Mask
          USB_EP_SPEED_LOW        ,  // Low Speed
          USB_EP_SPEED_FULL       ,  // Full Speed
          USB_EP_HOST_IN          ,  // Host IN endpoint
          USB_EP_HOST_OUT         ,  // Host OUT endpoint
          USB_EP_DEV_IN           ,  // Device IN endpoint
          USB_EP_DEV_OUT          ,  // Device OUT endpoint
                  };
         return mask[static_cast<uint32_t>(cf)];
      }

enum USB_REGS{//в том порядке в котором в структуре и не в столбик-8 штук в линию
};
static constexpr uint32_t USB_REG(USB_REGS  ur)
      {
        constexpr uint32_t mask[] =
        {
 ///сюда то что мы уже умеем получать
        };
        return mask[static_cast<uint8_t>(ur)];;
}
};








