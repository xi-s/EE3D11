/*
    name:   ARM assignment 1_3_Button
    date:   10-3-2017
    author: Remy Jaspers 4499336

*/

/*
3.1:
SDA P0_5
SCL P0_4

Start flag can be set using CONSET:
LPC_I2C->CONSET = 1 << 5;

Clearing SI
LPC_I2C->CONCLR = 1 << 3;

Used for data reading/writing:
LPC_I2C->DAT

SI flag can be polled for events:
while(LPC_I2C->CONSET & 1 << 3);

3.2
The address of the TMP102 is 0x48
The write address is 0x90
The read address is 0x91


+30/(0.0625/1) = 480 = 0x1E0 = 0001 1110 0000
|-12|/0.0625 = 192 = 0x0C0 = 0000 1100 0000
1111 0011 1111 + 1 = 1111 0100 0000

In the default 12-bit format, which temperatures are represented by the numbers 0010 1010 1001 and 1101 0100 1000
0010 1010 1001 = 0x2A9 = 681 => 681*0.0625 = 42,5625 C
1101 0100 1000 - 1 = 1101 0100 0111 invert->
0010 1011 1000 = 0x2B8 = 696 => -696/0.0625 = -43,5 C

Temperature varies from -127 to 128, range is 256, thus we need 2^8 or 8 bits
*/
#include <stdbool.h>

#include "LPC13xx.h"
#include "delay.h"

void I2C_init()
{
    // Enable I2C clock and deassert I2C reset
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 5;
    LPC_SYSCON->PRESETCTRL |= 1 << 1;

    LPC_I2C->SCLH = SystemCoreClock/(100000* 2);
    LPC_I2C->SCLL = LPC_I2C->SCLH;

    // Configure pins
    LPC_IOCON->PIO0_4 = 1;  // SCL
    LPC_IOCON->PIO0_5 = 1;  // SDA

    LPC_I2C->CONSET |= 1 << 6;  // I2C enable
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
