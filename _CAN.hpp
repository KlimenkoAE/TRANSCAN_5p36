#pragma once
#include <cstdint>
//#include "wrappers_headers.hpp"
/*
template<uint16_t ID, uint16_t Mask>
struct CAN_Filter
{
    static constexpr uint16_t id   = ID;
    static constexpr uint16_t mask = Mask;
};
using EngineFilter = CAN_Filter<0x201, 0x7FF>;


template< EngineFilter >
class CAN_MSG{
uint8_t data[8];
uint8_t DLC;
uint16_t ID;
//template<filter>
//struct Filter{};
};



template<
uint8_t rx_cnt, 
uint8_t tx_cnt
>
class CAN_MSG_BUFF{
 RX[rx_cnt];
};


template <
uint32_t base,

>
class CAN{


};


extern void CAN0_Init();

//прерывания
extern void CAN0_IntEnable();
extern void CAN0IntDesable();
//настройка частоты по умолчанию
extern void CAN_SetFrequency(unsigned long CANf);
//сброс
extern void CAN0_Reset();
extern tBoolean CAN_MerssageConfigureDefaultRX(uint8_t msg_obj_num,tCANMsgObject* Msg);
extern tBoolean CANMessageConfigureTX(uint32_t ID,uint32_t msg_obj_num,uint32_t flags,tCANMsgObject* Msg, uint8_t buf_len);
extern tBoolean CAN_MessageConfigureRX(uint8_t msg_obj_num, uint32_t ID,uint32_t msk,uint32_t flags,tCANMsgObject* Msg,uint8_t buf_len);

extern void CAN_SetSpeed(uint32_t bitrate);*/