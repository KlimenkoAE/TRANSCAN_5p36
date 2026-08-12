#pragma once

#include <cstdint>
extern "C" {
#include "hw_types.h"
#include "usb.h"
}
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
};








