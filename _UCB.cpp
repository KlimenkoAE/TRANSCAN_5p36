
#include "hw_types.h"
#include "_USB.hpp"
/*
extern "C" {
void USBISR0() { if (USB_ISR::lmd[0]) USB_ISR::lmd[0](); }
void USBISR1() { if (USB_ISR::lmd[1]) USB_ISR::lmd[1](); }
void USBISR2() { if (USB_ISR::lmd[2]) USB_ISR::lmd[2](); }
void USBISR3() { if (USB_ISR::lmd[3]) USB_ISR::lmd[3](); }
}

// ===== вот то, чего не хватает линкеру =====
uint8_t USB_ISR::isr_count = 0;
std::function<void()> USB_ISR::lmd[4];
void (*USB_ISR::ISR[4])() = {
    USBISR0, USBISR1, USBISR2, USBISR3
};

void USB_ISR::InitTable()
{
    // таблица уже инициализирована выше; isr_count сброс при желании
    isr_count = 0;
}

void USB_ISR::Registration(uint32_t b, std::function<void()> isr)
{
    if (isr_count >= 4)
        return; // переполнение

    lmd[isr_count] = std::move(isr);
    TimerIntRegister(b,  USBISR[isr_count]);
    ++isr_count;
};*/