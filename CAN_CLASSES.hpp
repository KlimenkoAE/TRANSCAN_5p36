#pragma once
#include <cstdint>
#include <concepts>
#include "wrappers_headers.hpp"
#include <bit>
enum class CAN_FilterFlags : uint32_t
{
    NONE            = 0,

    USE_ID          = 1u << 0,
    USE_EXTENDED_ID = 1u << 1,
    USE_DIRECTION   = 1u << 2
};

enum class CAN_Interrupt : uint32_t
{
    NONE = 0,

    RX   = 1u << 0,
    TX   = 1u << 1
};


// ============================================================================
// CAN — universal protocol layer
//
// Здесь НЕ должно быть ничего, что относится к конкретному MCU:
// регистров, mailbox, ulFlags, CAN controller modes и т.п.
//
// Идея:
//
//     compile time                    run time
//     ------------                   ---------
//     Filter type                   Message data
//     CAN_Filter<ID, Mask>          ID / DLC / Data
//            │                           │
//            └──────────┬────────────────┘
//                       ▼
//                   CAN<Backend>
//                       │
//                       ▼
//               Backend-specific HW
// ============================================================================


// ============================================================================
// Compile-time CAN filter
//
// ID и Mask известны во время компиляции.
// Такой объект не требует хранения ID/Mask в runtime.
// ============================================================================

template<uint16_t ID, uint16_t Mask, bool _remote=false, bool _extended=false>
struct CAN_Filter
{
    static constexpr uint16_t id   = ID;
    static constexpr uint16_t mask = Mask;
    static constexpr bool remote=_remote;
    static constexpr bool extended=_extended;
};


// ============================================================================
// CAN filter concept
//
// Любой тип, используемый как compile-time filter, должен предоставлять:
//
//     Filter::id
//     Filter::mask
//
// Это не привязывает CAN к конкретной реализации фильтра.
// ============================================================================

template<class T>
concept CANFilter =
    requires
    {
        T::id;
        T::mask;
        T::remote;
        T::extended;
    };



struct CAN_Message
{
    uint8_t  dlc;
    uint8_t*  data;
};



using CAN_DataPool = DataPool<8, 32>;
struct CAN_MessageStorage
{
    static void Init(CAN_Message& msg)
    {
        msg.dlc = 0;
        msg.data = CAN_DataPool::Get();
    }

    static void Release(CAN_Message& msg)
    {
        CAN_DataPool::Release(msg.data);

        msg.data = nullptr;
        msg.dlc = 0;
    }
};
using CAN_MessagePool =
    MemPool<CAN_Message, CAN_MessageStorage>;

//struct CAN_Data
//{
//    uint8_t data[8];
//    uint8_t dlc;
//};


// ============================================================
// CAN message
// ============================================================

// ============================================================================
// CAN backend interface
//
// Backend знает конкретное железо.
//
// Например:
//
//     CAN<StellarisBackend>
//     CAN<STM32Backend>
//     CAN<AVRBackend>
//
// Универсальный CAN-код не знает, каким образом backend работает
// с регистрами контроллера.
// ============================================================================

/*template<class Backend>
class CAN
{
public:

    // ------------------------------------------------------------------------
    // Передача runtime message
    // ------------------------------------------------------------------------

    static void Send(const CAN_Message& msg)
    {
        Backend::Send(msg);
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
        Backend::ConfigureFilter<Filter>();
    }
};*/


// ============================================================================
// Example: compile-time filters
//
// Никаких runtime переменных для ID/Mask здесь не требуется.
 //============================================================================

//using EngineFilter   = CAN_Filter<0x201, 0x7FF>;
//using IgnitionFilter = CAN_Filter<0x430, 0x7FF>;


// ============================================================================
// Example backend
//
// Это уже условная реализация конкретного CAN-контроллера.
//
// Здесь появляются вещи, специфичные для MCU:
// mailbox, message object, аппаратные фильтры, регистры и т.д.
// ============================================================================

/*struct StellarisCANBackend
{
    // ------------------------------------------------------------------------
    // Runtime transmission
    // ------------------------------------------------------------------------

    static void Send(const CAN_Message& msg)
    {
        // Hardware-specific implementation.
        //
        // msg.ID
        // msg.DLC
        // msg.Data
        //
        // Здесь уже можно сформировать tCANMsgObject
        // или непосредственно записать регистры Stellaris.
    }


    // ------------------------------------------------------------------------
    // Compile-time filter configuration
    // ------------------------------------------------------------------------

    template<CANFilter Filter>
    static void ConfigureFilter()
    {
        // Filter::id
        // Filter::mask
        //
        // Здесь Stellaris-specific code:
        //
        // CAN message object
        // CANIntEnable()
        // CANMessageSet()
        // hardware ID mask
        // etc.
    }
};*/


// ============================================================================
// Application
// ============================================================================

//using MyCAN = CAN<StellarisCANBackend>;


// -----------------------------------------------------------------------------
// Compile-time configuration
// -----------------------------------------------------------------------------
/*
void CAN_Init()
{
    MyCAN::ConfigureFilter<EngineFilter>();
    MyCAN::ConfigureFilter<IgnitionFilter>();
}
*/

// -----------------------------------------------------------------------------
// Runtime operation
// -----------------------------------------------------------------------------
/*
void SendRPM(uint16_t rpm)
{
    CAN_Message msg{};

    msg.ID  = 0x201;
    msg.DLC = 8;

    msg.Data[0] = 0x02;
    msg.Data[1] = 0x00;

    msg.Data[2] = 0x00;
    msg.Data[3] = 0x00;

    msg.Data[4] = static_cast<uint8_t>(rpm >> 8);
    msg.Data[5] = static_cast<uint8_t>(rpm);

    msg.Data[6] = 0x00;
    msg.Data[7] = 0x00;

    MyCAN::Send(msg);
}*/