#pragma once
#include <cstdint>
// ============================================================
// STM32 USB definitions generated from stm32f732xx.h
// ============================================================

// ============================================================
// USB instances
// ============================================================

enum class MyUSB_INSTANCE : uint8_t
{
};

static constexpr uint32_t USB_INSTANCE_BASES[] =
{
};

static constexpr uint32_t USB_INSTANCE_BASE(MyUSB_INSTANCE instance)
{
    return USB_INSTANCE_BASES[static_cast<uint8_t>(instance)];
}

// ============================================================
// USB geometry
// ============================================================

static constexpr uint32_t GLOBAL_BASE = 0x0000;
static constexpr uint32_t DEVICE_BASE = 0x0800;
static constexpr uint32_t IN_ENDPOINT_BASE = 0x0900;
static constexpr uint32_t OUT_ENDPOINT_BASE = 0x0B00;
static constexpr uint32_t EP_REG_SIZE = 0x0020;
static constexpr uint32_t HOST_BASE = 0x0400;
static constexpr uint32_t HOST_PORT_BASE = 0x0440;
static constexpr uint32_t HOST_CHANNEL_BASE = 0x0500;
static constexpr uint32_t HOST_CHANNEL_SIZE = 0x0020;
static constexpr uint32_t PCGCCTL_BASE = 0x0E00;
static constexpr uint32_t FIFO_BASE = 0x1000;
static constexpr uint32_t FIFO_SIZE = 0x1000;

enum class MyUSB_GLOBAL_REG : uint8_t
{
    JOFR1,
    JOFR2,
    JOFR3,
    JOFR4,
    HTR,
    LTR,
    DHR12R1,
    DHR12L1,
    DHR8R1,
    DHR12R2,
    DHR12L2,
    DHR8R2,
    DOR1,
    DOR2,
    PSMAR,
    GOTGCTL,
    GOTGINT,
    GAHBCFG,
    GUSBCFG,
    GRSTCTL,
    GINTSTS,
    GINTMSK,
    GRXSTSR,
    GRXSTSP,
    GRXFSIZ,
    DIEPTXF0_HNPTXFSIZ,
    HNPTXSTS,
    GCCFG,
    CID,
    GHWCFG3,
    GLPMCFG,
    GDFIFOCFG,
    HPTXFSIZ,
};

static constexpr uint32_t USBGlobalReg[] =
{
    0x000C, // JOFR1
    0x000C, // JOFR2
    0x000C, // JOFR3
    0x000C, // JOFR4
    0x000C, // HTR
    0x000C, // LTR
    0x000C, // DHR12R1
    0x000C, // DHR12L1
    0x000C, // DHR8R1
    0x000C, // DHR12R2
    0x000C, // DHR12L2
    0x000C, // DHR8R2
    0x000C, // DOR1
    0x000C, // DOR2
    0x000C, // PSMAR
    0x0000, // GOTGCTL
    0x0004, // GOTGINT
    0x0008, // GAHBCFG
    0x000C, // GUSBCFG
    0x0010, // GRSTCTL
    0x0014, // GINTSTS
    0x0018, // GINTMSK
    0x001C, // GRXSTSR
    0x0020, // GRXSTSP
    0x0024, // GRXFSIZ
    0x0028, // DIEPTXF0_HNPTXFSIZ
    0x002C, // HNPTXSTS
    0x0038, // GCCFG
    0x003C, // CID
    0x004C, // GHWCFG3
    0x0054, // GLPMCFG
    0x005C, // GDFIFOCFG
    0x0100, // HPTXFSIZ
};

static constexpr uint32_t USBGlobalReg(MyUSB_GLOBAL_REG reg)
{
    return USBGlobalReg[static_cast<uint8_t>(reg)];
}

enum class MyUSB_DEVICE_REG : uint8_t
{
    JOFR1,
    JOFR2,
    JOFR3,
    JOFR4,
    HTR,
    LTR,
    DHR12R1,
    DHR12L1,
    DHR8R1,
    DHR12R2,
    DHR12L2,
    DHR8R2,
    DOR1,
    DOR2,
    PSMAR,
    GOTGCTL,
    GOTGINT,
    GAHBCFG,
    GUSBCFG,
    GRSTCTL,
    GINTSTS,
    GINTMSK,
    GRXSTSR,
    GRXSTSP,
    GRXFSIZ,
    DIEPTXF0_HNPTXFSIZ,
    HNPTXSTS,
    GCCFG,
    CID,
    GHWCFG3,
    GLPMCFG,
    GDFIFOCFG,
    HPTXFSIZ,
    DCFG,
    DCTL,
    DSTS,
    DIEPMSK,
    DOEPMSK,
    DAINT,
    DAINTMSK,
    DVBUSDIS,
    DVBUSPULSE,
    DTHRCTL,
    DIEPEMPMSK,
    DEACHINT,
    DEACHMSK,
    DINEP1MSK,
    DOUTEP1MSK,
};

static constexpr uint32_t USBDeviceReg[] =
{
    0x000C, // JOFR1
    0x000C, // JOFR2
    0x000C, // JOFR3
    0x000C, // JOFR4
    0x000C, // HTR
    0x000C, // LTR
    0x000C, // DHR12R1
    0x000C, // DHR12L1
    0x000C, // DHR8R1
    0x000C, // DHR12R2
    0x000C, // DHR12L2
    0x000C, // DHR8R2
    0x000C, // DOR1
    0x000C, // DOR2
    0x000C, // PSMAR
    0x0000, // GOTGCTL
    0x0004, // GOTGINT
    0x0008, // GAHBCFG
    0x000C, // GUSBCFG
    0x0010, // GRSTCTL
    0x0014, // GINTSTS
    0x0018, // GINTMSK
    0x001C, // GRXSTSR
    0x0020, // GRXSTSP
    0x0024, // GRXFSIZ
    0x0028, // DIEPTXF0_HNPTXFSIZ
    0x002C, // HNPTXSTS
    0x0038, // GCCFG
    0x003C, // CID
    0x004C, // GHWCFG3
    0x0054, // GLPMCFG
    0x005C, // GDFIFOCFG
    0x0100, // HPTXFSIZ
    0x0800, // DCFG
    0x0804, // DCTL
    0x0808, // DSTS
    0x0810, // DIEPMSK
    0x0814, // DOEPMSK
    0x0818, // DAINT
    0x081C, // DAINTMSK
    0x000C, // DVBUSDIS
    0x082C, // DVBUSPULSE
    0x0830, // DTHRCTL
    0x0834, // DIEPEMPMSK
    0x0838, // DEACHINT
    0x083C, // DEACHMSK
    0x0844, // DINEP1MSK
    0x0884, // DOUTEP1MSK
};

static constexpr uint32_t USBDeviceReg(MyUSB_DEVICE_REG reg)
{
    return USBDeviceReg[static_cast<uint8_t>(reg)];
}

// ============================================================
// USB IN endpoint registers
// ============================================================

enum class MyUSB_IN_EP_REG : uint8_t
{
    JOFR1,
    JOFR2,
    JOFR3,
    JOFR4,
    HTR,
    LTR,
    DHR12R1,
    DHR12L1,
    DHR8R1,
    DHR12R2,
    DHR12L2,
    DHR8R2,
    DOR1,
    DOR2,
    PSMAR,
    GOTGCTL,
    GOTGINT,
    GAHBCFG,
    GUSBCFG,
    GRSTCTL,
    GINTSTS,
    GINTMSK,
    GRXSTSR,
    GRXSTSP,
    GRXFSIZ,
    DIEPTXF0_HNPTXFSIZ,
    HNPTXSTS,
    GCCFG,
    CID,
    GHWCFG3,
    GLPMCFG,
    GDFIFOCFG,
    HPTXFSIZ,
    DCFG,
    DCTL,
    DSTS,
    DIEPMSK,
    DOEPMSK,
    DAINT,
    DAINTMSK,
    DVBUSDIS,
    DVBUSPULSE,
    DTHRCTL,
    DIEPEMPMSK,
    DEACHINT,
    DEACHMSK,
    DINEP1MSK,
    DOUTEP1MSK,
    DIEPCTL,
    DIEPINT,
    DIEPTSIZ,
    DIEPDMA,
    DTXFSTS,
};

static constexpr uint32_t USBInEPRegOffsets[] =
{
    0x000C, // JOFR1
    0x000C, // JOFR2
    0x000C, // JOFR3
    0x000C, // JOFR4
    0x000C, // HTR
    0x000C, // LTR
    0x000C, // DHR12R1
    0x000C, // DHR12L1
    0x000C, // DHR8R1
    0x000C, // DHR12R2
    0x000C, // DHR12L2
    0x000C, // DHR8R2
    0x000C, // DOR1
    0x000C, // DOR2
    0x000C, // PSMAR
    0x0000, // GOTGCTL
    0x0004, // GOTGINT
    0x0008, // GAHBCFG
    0x000C, // GUSBCFG
    0x0010, // GRSTCTL
    0x0014, // GINTSTS
    0x0018, // GINTMSK
    0x001C, // GRXSTSR
    0x0020, // GRXSTSP
    0x0024, // GRXFSIZ
    0x0028, // DIEPTXF0_HNPTXFSIZ
    0x002C, // HNPTXSTS
    0x0038, // GCCFG
    0x003C, // CID
    0x004C, // GHWCFG3
    0x0054, // GLPMCFG
    0x005C, // GDFIFOCFG
    0x0100, // HPTXFSIZ
    0x0800, // DCFG
    0x0804, // DCTL
    0x0808, // DSTS
    0x0810, // DIEPMSK
    0x0814, // DOEPMSK
    0x0818, // DAINT
    0x081C, // DAINTMSK
    0x000C, // DVBUSDIS
    0x082C, // DVBUSPULSE
    0x0830, // DTHRCTL
    0x0834, // DIEPEMPMSK
    0x0838, // DEACHINT
    0x083C, // DEACHMSK
    0x0844, // DINEP1MSK
    0x0884, // DOUTEP1MSK
    0x0000, // DIEPCTL
    0x0008, // DIEPINT
    0x0010, // DIEPTSIZ
    0x0014, // DIEPDMA
    0x0018, // DTXFSTS
};

static constexpr uint32_t USBInEPReg(uint8_t ep, MyUSB_IN_EP_REG reg)
{
    return USB_OTG_IN_ENDPOINT_BASE + static_cast<uint32_t>(ep) * USB_OTG_EP_REG_SIZE + USBInEPRegOffsets[static_cast<uint8_t>(reg)];
}

// ============================================================
// USB OUT endpoint registers
// ============================================================

enum class MyUSB_OUT_EP_REG : uint8_t
{
    JOFR1,
    JOFR2,
    JOFR3,
    JOFR4,
    HTR,
    LTR,
    DHR12R1,
    DHR12L1,
    DHR8R1,
    DHR12R2,
    DHR12L2,
    DHR8R2,
    DOR1,
    DOR2,
    PSMAR,
    GOTGCTL,
    GOTGINT,
    GAHBCFG,
    GUSBCFG,
    GRSTCTL,
    GINTSTS,
    GINTMSK,
    GRXSTSR,
    GRXSTSP,
    GRXFSIZ,
    DIEPTXF0_HNPTXFSIZ,
    HNPTXSTS,
    GCCFG,
    CID,
    GHWCFG3,
    GLPMCFG,
    GDFIFOCFG,
    HPTXFSIZ,
    DCFG,
    DCTL,
    DSTS,
    DIEPMSK,
    DOEPMSK,
    DAINT,
    DAINTMSK,
    DVBUSDIS,
    DVBUSPULSE,
    DTHRCTL,
    DIEPEMPMSK,
    DEACHINT,
    DEACHMSK,
    DINEP1MSK,
    DOUTEP1MSK,
    DIEPCTL,
    DIEPINT,
    DIEPTSIZ,
    DIEPDMA,
    DTXFSTS,
    DOEPCTL,
    DOEPINT,
    DOEPTSIZ,
    DOEPDMA,
};

static constexpr uint32_t USBOutEPRegOffsets[] =
{
    0x000C, // JOFR1
    0x000C, // JOFR2
    0x000C, // JOFR3
    0x000C, // JOFR4
    0x000C, // HTR
    0x000C, // LTR
    0x000C, // DHR12R1
    0x000C, // DHR12L1
    0x000C, // DHR8R1
    0x000C, // DHR12R2
    0x000C, // DHR12L2
    0x000C, // DHR8R2
    0x000C, // DOR1
    0x000C, // DOR2
    0x000C, // PSMAR
    0x0000, // GOTGCTL
    0x0004, // GOTGINT
    0x0008, // GAHBCFG
    0x000C, // GUSBCFG
    0x0010, // GRSTCTL
    0x0014, // GINTSTS
    0x0018, // GINTMSK
    0x001C, // GRXSTSR
    0x0020, // GRXSTSP
    0x0024, // GRXFSIZ
    0x0028, // DIEPTXF0_HNPTXFSIZ
    0x002C, // HNPTXSTS
    0x0038, // GCCFG
    0x003C, // CID
    0x004C, // GHWCFG3
    0x0054, // GLPMCFG
    0x005C, // GDFIFOCFG
    0x0100, // HPTXFSIZ
    0x0800, // DCFG
    0x0804, // DCTL
    0x0808, // DSTS
    0x0810, // DIEPMSK
    0x0814, // DOEPMSK
    0x0818, // DAINT
    0x081C, // DAINTMSK
    0x000C, // DVBUSDIS
    0x082C, // DVBUSPULSE
    0x0830, // DTHRCTL
    0x0834, // DIEPEMPMSK
    0x0838, // DEACHINT
    0x083C, // DEACHMSK
    0x0844, // DINEP1MSK
    0x0884, // DOUTEP1MSK
    0x0000, // DIEPCTL
    0x0008, // DIEPINT
    0x0010, // DIEPTSIZ
    0x0014, // DIEPDMA
    0x0018, // DTXFSTS
    0x0000, // DOEPCTL
    0x0008, // DOEPINT
    0x0010, // DOEPTSIZ
    0x0014, // DOEPDMA
};

static constexpr uint32_t USBOutEPReg(uint8_t ep, MyUSB_OUT_EP_REG reg)
{
    return USB_OTG_OUT_ENDPOINT_BASE + static_cast<uint32_t>(ep) * USB_OTG_EP_REG_SIZE + USBOutEPRegOffsets[static_cast<uint8_t>(reg)];
}

// ============================================================
// USB FIFO
// ============================================================

static constexpr uint32_t USBFIFO(uint32_t offset)
{
    return USB_OTG_FIFO_BASE + offset;
}

