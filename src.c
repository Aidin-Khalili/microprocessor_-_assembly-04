#include "LPC17xx.h"

void initi_GPIO2(){
	LPC_GPIO2->FIODIR = 0xffffffff;
}

void TIMER2_IRQHandler ()
{
    LPC_TIM2->IR = 1;
    LPC_GPIO2->FIOPIN++;
}

int init_timer2()
{
    LPC_PINCON->PINSEL0 |= (0x3 << 8);    					//Select PIN0.4 as CAP2.0        
    LPC_TIM2->CTCR |= 0x3;                          //Be on Counter mode
    LPC_TIM2->PR = 0;
    LPC_TIM2->MR0 = 12;
    LPC_TIM2->MCR = (0x3<<6);                           // To set with intrrupt & reset On MR0
    NVIC_EnableIRQ(TIMER2_IRQn);
}

int main()
{
	initi_GPIO2();
  init_timer2();  
	LPC_TIM2->TCR = 1;
  while(1){}
	return 0;
}