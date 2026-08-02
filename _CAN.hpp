#pragma once

template <>
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

extern void CAN_SetSpeed(uint32_t bitrate);