#pragma once
extern "C"{
#include <stdint.h>
#include <stdbool.h>
#include "usb.h"
#include "sysctl.h"
#include "rom.h"
#include "rom_map.h"
#include"interrupt.h"
}

#include <functional>
#include <algorithm>

extern "C"{
 void USBISR0();
 void USBISR1();
 void USBISR2();
 void USBISR3();
};

class USB_ISR {   // без static class
public:
    static uint8_t isr_count;
    static std::function<void()> lmd[4];
    static void (*ISR[4])();

    static void Registration(uint32_t b, std::function<void()> isr);
    static void InitTable();  // один раз при старте
};

/*

template<

>
class USB{


}*/