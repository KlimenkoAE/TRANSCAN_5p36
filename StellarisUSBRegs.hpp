#pragma once

#include <cstdint>

enum class MyUSB_EP : uint8_t
{
    EP0,
    EP1,
    EP2,
    EP3,
    EP4,
    EP5,
    EP6,
    EP7,
    EP8,
    EP9,
    EP10,
    EP11,
    EP12,
    EP13,
    EP14,
    EP15,
};

enum class MyUSB_INTCTRL : uint8_t
{
    ALL,
    STATUS,
    VBUS_ERR,
    SESSION,
    DISCONNECT,
    CONNECT,
    SOF,
    BABBLE,
    RESUME,
    SUSPEND,
    MODE_DETECT,
    POWER_FAULT,
};

enum class MyUSB_EP_CFG : uint8_t
{
    AUTO_SET,
    AUTO_REQUEST,
    AUTO_CLEAR,
    DMA_MODE_0,
    DMA_MODE_1,
    MODE_ISOC,
    MODE_BULK,
    MODE_INT,
    MODE_CTRL,
    MODE_MASK,
    SPEED_LOW,
    SPEED_FULL,
    HOST_IN,
    HOST_OUT,
    DEV_IN,
    DEV_OUT,
};

template <>
class VendorConsts<Stellaris>
{
public:

    static constexpr uint32_t Endpoint(MyUSB_EP ep)
    {
        return static_cast<uint32_t>(ep) << 4;
    }

    static constexpr uint32_t INTEP_IN(MyUSB_EP ep)
    {
        constexpr uint32_t mask[] =
        {
            USB_INTEP_0,
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
            USB_INTEP_DEV_IN_15,
        };
        return mask[static_cast<uint8_t>(ep)];
    }

    static constexpr uint32_t INTEP_OUT(MyUSB_EP ep)
    {
        constexpr uint32_t mask[] =
        {
            USB_INTEP_0,
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
            USB_INTEP_DEV_OUT_15,
        };
        return mask[static_cast<uint8_t>(ep)];
    }

    static constexpr uint32_t INTCTRL(MyUSB_INTCTRL flag)
    {
        constexpr uint32_t mask[] =
        {
            USB_INTCTRL_ALL,
            USB_INTCTRL_STATUS,
            USB_INTCTRL_VBUS_ERR,
            USB_INTCTRL_SESSION,
            USB_INTCTRL_DISCONNECT,
            USB_INTCTRL_CONNECT,
            USB_INTCTRL_SOF,
            USB_INTCTRL_BABBLE,
            USB_INTCTRL_RESUME,
            USB_INTCTRL_SUSPEND,
            USB_INTCTRL_MODE_DETECT,
            USB_INTCTRL_POWER_FAULT,
        };
        return mask[static_cast<uint8_t>(flag)];
    }

    static constexpr uint32_t EP_CFG(MyUSB_EP_CFG cf)
    {
        constexpr uint32_t mask[] =
        {
            USB_EP_AUTO_SET,
            USB_EP_AUTO_REQUEST,
            USB_EP_AUTO_CLEAR,
            USB_EP_DMA_MODE_0,
            USB_EP_DMA_MODE_1,
            USB_EP_MODE_ISOC,
            USB_EP_MODE_BULK,
            USB_EP_MODE_INT,
            USB_EP_MODE_CTRL,
            USB_EP_MODE_MASK,
            USB_EP_SPEED_LOW,
            USB_EP_SPEED_FULL,
            USB_EP_HOST_IN,
            USB_EP_HOST_OUT,
            USB_EP_DEV_IN,
            USB_EP_DEV_OUT,
        };
        return mask[static_cast<uint8_t>(cf)];
    }

};
