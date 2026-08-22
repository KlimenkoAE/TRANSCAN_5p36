#pragma once
#include <cstdint>
#include "wrappers_headers.hpp"

/*enum class  TIMER_MODE:uint8_t{OVF,PWM};

template <typename cpu,TIMER_MODE mode>
struct PHYTimerBase{
 uint32_t MainPeriod;
 uint32_t BASE_ADDR;
 uint32_t MODE;
 uint32_t CFG;
 uint32_t TIMER_PERIPH_ENABLE;
};

/*
// TIM2 overflow interrupt
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
TIM2->PSC = 16000 - 1;   // делитель
TIM2->ARR = 1000 - 1;    // период
TIM2->DIER |= TIM_DIER_UIE;
TIM2->CR1 |= TIM_CR1_CEN;
NVIC_EnableIRQ(TIM2_IRQn);

extern "C" void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        // твой код
    }
}



// Timer0 overflow interrupt
TCCR0A = 0;
TCCR0B = (1 << CS02) | (1 << CS00); // делитель 1024
TIMSK0 = (1 << TOIE0);
sei();

ISR(TIMER0_OVF_vect) {
    // твой код
}



// TC0 overflow interrupt (SAM)
PMC->PMC_PCER0 |= (1 << ID_TC0);
TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4; // делитель /128
TC0->TC_CHANNEL[0].TC_IER = TC_IER_COVFS;
TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
NVIC_EnableIRQ(TC0_IRQn);

void TC0_Handler(void) {
    if (TC0->TC_CHANNEL[0].TC_SR & TC_SR_COVFS) {
        // твой код
    }
}



// LPC176x Timer0 overflow interrupt
LPC_SC->PCONP |= (1 << 1);        // включить питание Timer0
LPC_TIM0->PR = 0;                 // предделитель
LPC_TIM0->MR0 = 1000000;          // match value (1 сек при 1 МГц)
LPC_TIM0->MCR = (1 << 0) | (1 << 1); // interrupt + reset on MR0
LPC_TIM0->TCR = 1;                // включить таймер
NVIC_EnableIRQ(TIMER0_IRQn);

void TIMER0_IRQHandler(void) {
    if (LPC_TIM0->IR & 0x1) {
        LPC_TIM0->IR = 0x1;       // сброс флага
        // твой код
    }
}
*/

/*

template <Stellaris,TIMER_MODE mode>
struct PHYTimer:PHYTimerBase<Stellaris,mode>{ 
 uint32_t PART_AB;
 bool Init(){
  if(mode==TIMER_MODE::OVF){


  };
};

};*/