#pragma onse

#include <stdint.h>
#include <stdbool.h>
#include <functional>
#include <algorithm>

extern "C"{
 void _ISR0();
 void _ISR1();
 void _ISR2();
 void _ISR3();
 void _ISR4();
 void _ISR5();
 void _ISR6();
 void _ISR7();
 void _ISR8();
 void _ISR9();

  void _ISR10();
 void _ISR11();
 void _ISR12();
 void _ISR13();
 void _ISR14();
 void _ISR15();
 void _ISR16();
 void _ISR17();
 void _ISR18();
 void _ISR19();

  void _ISR20();
 void _ISR21();
 void _ISR22();
 void _ISR23();
 void _ISR24();
 void _ISR25();
 void _ISR26();
 void _ISR27();
 void _ISR28();
 void _ISR29();

 void _ISR30();
 void _ISR31();
};

class IPeriferalISR {   
public:
    static uint8_t isr_count;
    static std::function<void()> lmd[32];
    static void (*ISR[32])();
    virtual void  Registration(std::function<void()> isr ,uint32_t sw_def... ){};
};