#pragma once
#include <cstdint>
#include "wrappers_headers.hpp"
// ============================================================================
// Example: compile-time filters
//
// Никаких runtime переменных для ID/Mask здесь не требуется.
// ============================================================================

using TestFilter = CAN_Filter<0x00, 0x00>;
//const uint8_t dataDefault[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};//test
inline CAN_Message* _dataDefault1=CAN_MessagePool::Get();
//_dataDefault1->data[0]=1;//{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}
_dataDefault1->dlc=8;

using EngineFilter   = CAN_Filter<0x201, 0x7FF>;
using IgnitionFilter = CAN_Filter<0x430, 0x7FF>;
using SpeedFilter = CAN_Filter<0x4B0, 0x7FF>;



const uint8_t dataRPM[8] = {0x02, 0x00, 0x00, 0x00, 0x1F, 0x40, 0x00, 0x00};
const uint8_t dataIgn[8] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};
const uint8_t dataSpeed[8] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00};



using BackEnd=TBackEnd<FunctionWraper<PROC>,PROC>;

using USBWRP=BackEnd::USB;
using CANWRP=BackEnd::CAN;