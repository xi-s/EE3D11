/*
    name:   ARM assignment 1_2
    date:   10-3-2017
    author: Remy Jaspers 4499336

*/

#include "LPC13xx.h"

#include "delay.h"

static void init(void){
    // Configure PIO3_0 to be output
    *(volatile uint32_t *) 0x50038000 = 1;
}
static void led_off(void){
    // Write 1 to PIO3_0 to turn LED off
    *(volatile uint32_t *) 0x50033FFC = 1;
}
static void led_on(void){
    // Write 0 to PIO3_0 to turn LED on
    *(volatile uint32_t *) 0x50033FFC = 0;
}

int main (void)
{
    init();
    led_on();
    delay_ms(1000);
    led_off();

	while (1) { }
}
