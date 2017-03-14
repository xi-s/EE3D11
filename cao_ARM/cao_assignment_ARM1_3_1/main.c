/*
    name:   ARM assignment 1_3_Button
    date:   10-3-2017
    author: Remy Jaspers 4499336

*/

#include <stdbool.h>

#include "LPC13xx.h"
#include "delay.h"

static void init(void){
    // Configure PIO3_0 to be output
    LPC_GPIO3->DIR |= (1 << 0);
}

static void led_toggle(void){
    LPC_GPIO3->DATA ^= (1 << 0);
}

static void init_button(void){
    // Set GPIO2_9 to INPUT
    LPC_GPIO2->DIR |= (0 << 9);
}

static bool but1_pressed(void){
    if(LPC_GPIO2->DATA & (1 << 9)){
        return false;
    }
    else{
        return true;
    }
}

int main (void)
{
    init();
    init_button();
    while(1){
        if(but1_pressed()){
            delay_ms(100);
            led_toggle();
        }
    }

}
