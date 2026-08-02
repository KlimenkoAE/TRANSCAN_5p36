
#include "hw_types.h"
#include "_TIMERS.hpp"

extern "C" {
void ISR0() { if (TimerISR::lmd[0]) TimerISR::lmd[0](); }
void ISR1() { if (TimerISR::lmd[1]) TimerISR::lmd[1](); }
void ISR2() { if (TimerISR::lmd[2]) TimerISR::lmd[2](); }
void ISR3() { if (TimerISR::lmd[3]) TimerISR::lmd[3](); }
void ISR4() { if (TimerISR::lmd[4]) TimerISR::lmd[4](); }
void ISR5() { if (TimerISR::lmd[5]) TimerISR::lmd[5](); }
void ISR6() { if (TimerISR::lmd[6]) TimerISR::lmd[6](); }
void ISR7() { if (TimerISR::lmd[7]) TimerISR::lmd[7](); }
void ISR8() { if (TimerISR::lmd[8]) TimerISR::lmd[8](); }
void ISR9() { if (TimerISR::lmd[9]) TimerISR::lmd[9](); }
}

// ===== вот то, чего не хватает линкеру =====
uint8_t TimerISR::isr_count = 0;
std::function<void()> TimerISR::lmd[10];
void (*TimerISR::ISR[10])() = {
    ISR0, ISR1, ISR2, ISR3, ISR4,
    ISR5, ISR6, ISR7, ISR8, ISR9
};

void TimerISR::InitTable()
{
    // таблица уже инициализирована выше; isr_count сброс при желании
    isr_count = 0;
}

void TimerISR::Registration(uint32_t b, uint32_t t, std::function<void()> isr)
{
    if (isr_count >= 10)
        return; // переполнение

    lmd[isr_count] = std::move(isr);
    TimerIntRegister(b, t, ISR[isr_count]);
    ++isr_count;
}



