#include "LPC13xx.h"

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

static void init_timer(void){
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 9;

    LPC_TMR32B0->PR = 7200;
    LPC_TMR32B0->MR0 = 80;
    LPC_TMR32B0->MR3 = 100;
    LPC_TMR32B0->MCR = 1 | (1<<9) | (1<<10);
    LPC_TMR32B0->TCR = 1;
}

int main (void)
{
    init();
    init_timer();

	while(1)
    {
        if(LPC_TMR32B0->IR != 0)
        {
            if((LPC_TMR32B0->IR & 8) == 8)
            {
                pin_high();
                led_on();

                LPC_TMR32B0->IR = 8;
            }
            else if((LPC_TMR32B0->IR & 1) == 1)
            {
                pin_low();
                led_off();

                LPC_TMR32B0->IR = 1;
            }

        }
    }

}
