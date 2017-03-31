#include "LPC13xx.h"

/*
    HW 12.4.1:
    ISR is named TIMER_32_0_Handler according to Code::Blocks autocomplete

    Both the argument and return type are void.

    We need to enable it by passing the index to the NVIC (as in the code snippet)
    NVIC_EnableIRQ(TIMER_32_0_IRQn);


*/

static void init(void){
    // Configure PIO3_0 to be output
    LPC_GPIO3->DIR |= (1 << 0);
}
static void led_off(void){
    // Write 1 to PIO3_0 to turn LED off
    LPC_GPIO3->DATA |= (1 << 0);
}
static void led_on(void){
    // Write 0 to PIO3_0 to turn LED on
    LPC_GPIO3->DATA &= ~(1 << 0);
}

void pin_high(void)
{
    LPC_GPIO1->DATA &= ~(1 << 6);
}

void pin_low(void)
{
    LPC_GPIO1->DATA |= (1 << 6);
}

void TIMER_32_0_Handler(void){
    // If match on MR3, we want to
    // set the pin high
    if((LPC_TMR32B0->IR & 8) == 8)
    {
        pin_high();
        led_on();

        LPC_TMR32B0->IR = 8;
    }
    // If match on MR0, set pin to low
    else if((LPC_TMR32B0->IR & 1) == 1)
    {
        pin_low();
        led_off();

        LPC_TMR32B0->IR = 1;
    }
}


static void init_timer(void){
    // Enable clock for 32-bit counter/timer 0
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 9;

    LPC_TMR32B0->PR = 7200;
    LPC_TMR32B0->MR0 = 80;
    LPC_TMR32B0->MR3 = 10;

    // We want:
    // Interrupt when MR0 matches TC, bit 1
    // Interrupt when MR3 matches TC, bit 9
    // Reset TC when MR3 matches it, bit 10

    LPC_TMR32B0->MCR = 1 | (1<<9) | (1<<10);
    LPC_TMR32B0->TCR = 1;

    // Enable IRQ
    NVIC_EnableIRQ(TIMER_32_0_IRQn);
}

int main (void)
{
    init();
    init_timer();

	while(1)
    {
        __WFI();
    }
}


