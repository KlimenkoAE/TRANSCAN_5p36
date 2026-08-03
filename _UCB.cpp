
#include "hw_types.h"
#include "_USB.hpp"
void UsbISR::Registration(std::function<void()> isr, uint32_t sw_def, ...){
 va_list args;
    va_start(args, sw_def);

    // первый параметр
    uint32_t b = sw_def;

    if (isr_count >= 32) {
        va_end(args);
        return;
    }

    lmd[isr_count] = std::move(isr);
    USBIntRegister(b, ISR[isr_count]);
    ++isr_count;

    va_end(args);
}

