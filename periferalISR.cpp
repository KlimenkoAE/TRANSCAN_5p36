#include "periferalISR.hpp"
extern "C"{

void _ISR0() { if (IPeriferalISR::lmd[0]) IPeriferalISR::lmd[0](); }
void _ISR1() { if (IPeriferalISR::lmd[1]) IPeriferalISR::lmd[1](); }
void _ISR2() { if (IPeriferalISR::lmd[2]) IPeriferalISR::lmd[2](); }
void _ISR3() { if (IPeriferalISR::lmd[3]) IPeriferalISR::lmd[3](); }
void _ISR4() { if (IPeriferalISR::lmd[4]) IPeriferalISR::lmd[4](); }
void _ISR5() { if (IPeriferalISR::lmd[5]) IPeriferalISR::lmd[5](); }
void _ISR6() { if (IPeriferalISR::lmd[6]) IPeriferalISR::lmd[6](); }
void _ISR7() { if (IPeriferalISR::lmd[7]) IPeriferalISR::lmd[7](); }
void _ISR8() { if (IPeriferalISR::lmd[8]) IPeriferalISR::lmd[8](); }
void _ISR9() { if (IPeriferalISR::lmd[9]) IPeriferalISR::lmd[9](); }

void _ISR10() { if (IPeriferalISR::lmd[10]) IPeriferalISR::lmd[10](); }
void _ISR11() { if (IPeriferalISR::lmd[11]) IPeriferalISR::lmd[11](); }
void _ISR12() { if (IPeriferalISR::lmd[12]) IPeriferalISR::lmd[12](); }
void _ISR13() { if (IPeriferalISR::lmd[13]) IPeriferalISR::lmd[13](); }
void _ISR14() { if (IPeriferalISR::lmd[14]) IPeriferalISR::lmd[14](); }
void _ISR15() { if (IPeriferalISR::lmd[15]) IPeriferalISR::lmd[15](); }
void _ISR16() { if (IPeriferalISR::lmd[16]) IPeriferalISR::lmd[16](); }
void _ISR17() { if (IPeriferalISR::lmd[17]) IPeriferalISR::lmd[17](); }
void _ISR18() { if (IPeriferalISR::lmd[18]) IPeriferalISR::lmd[18](); }
void _ISR19() { if (IPeriferalISR::lmd[19]) IPeriferalISR::lmd[19](); }

void _ISR20() { if (IPeriferalISR::lmd[20]) IPeriferalISR::lmd[20](); }
void _ISR21() { if (IPeriferalISR::lmd[21]) IPeriferalISR::lmd[21](); }
void _ISR22() { if (IPeriferalISR::lmd[22]) IPeriferalISR::lmd[22](); }
void _ISR23() { if (IPeriferalISR::lmd[23]) IPeriferalISR::lmd[23](); }
void _ISR24() { if (IPeriferalISR::lmd[24]) IPeriferalISR::lmd[24](); }
void _ISR25() { if (IPeriferalISR::lmd[25]) IPeriferalISR::lmd[25](); }
void _ISR26() { if (IPeriferalISR::lmd[26]) IPeriferalISR::lmd[26](); }
void _ISR27() { if (IPeriferalISR::lmd[27]) IPeriferalISR::lmd[27](); }
void _ISR28() { if (IPeriferalISR::lmd[28]) IPeriferalISR::lmd[28](); }
void _ISR29() { if (IPeriferalISR::lmd[29]) IPeriferalISR::lmd[29](); }

void _ISR30() { if (IPeriferalISR::lmd[30]) IPeriferalISR::lmd[30](); }
void _ISR31() { if (IPeriferalISR::lmd[31]) IPeriferalISR::lmd[31](); }
}//ext c


void(*IPeriferalISR::ISR[32])()={
_ISR0, _ISR1, _ISR2, _ISR3, _ISR4,
    _ISR5, _ISR6, _ISR7, _ISR8, _ISR9,   
    _ISR10, _ISR11, _ISR12, _ISR13, _ISR14,
    _ISR15, _ISR16, _ISR17, _ISR18, _ISR19,    
    _ISR20, _ISR21, _ISR22, _ISR23, _ISR24,
    _ISR25, _ISR26, _ISR27, _ISR28, _ISR29,   
    _ISR30, _ISR31  
};

uint8_t IPeriferalISR::isr_count = 0;
std::function<void()> IPeriferalISR::lmd[32];