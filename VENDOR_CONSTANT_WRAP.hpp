#pragma once
#include "StellarisWareWrap.hpp"
enum MyUSB_EP{EP0,EP1,EP2,EP3,EP4,EP5,EP6,EP7,EP8,EP9,EP10,EP11,EP12,EP13,EP14,EP15,EP16,EP17,EP18,EP19,EP20,EP21,EP22,EP23,EP24,EP25,EP26,EP27,EP28,EP29,EP30,EP31,EP32};


template <class Wrap>
class VendorConsts{
public:
static constexpr unsigned long Endpoint(
        MyUSB_EP ep)
{
        return ep<<4;
}
};
using VndCnst = VendorConsts<StellarisWrap>;





