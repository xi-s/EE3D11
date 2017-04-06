/*
    name:   ARM assignment 3_3
    date:   1-4-2017
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
#include <stdint.h>
#include <stdbool.h>

#include "LPC13xx.h"
#include "leddriver.h"
#include "delay.h"

#define I2C_CLOCK_SPEED     100000
#define TMP201_ADDRESS      0x48

#define I2C_AA          (1 << 2)
#define I2C_SI          (1 << 3)
#define I2C_STO         (1 << 4)
#define I2C_STA         (1 << 5)
#define I2C_I2EN        (1 << 6)

// Master transmit mode status
#define I2CSTAT_START         0x08        // Start condition sent
#define I2CSTAT_RSTART        0x10        // Repeated start

#define I2CSTAT_MR_SLAWSENT      0x18        // SLA+W sent, ACK
#define I2CSTAT_MR_SLAWSENTNAK   0x20        // SLA+W sent, NOT ACK
#define I2CSTAT_MR_DATASENT      0x28        // Data byte in I2DAT sent, ACK
#define I2CSTAT_MR_DATASENTNAK   0x30        // Data byte in I2DAT sent, NOT ACK
#define I2CSTAT_MR_LOST          0x38        // Problem with sending data

#define I2CSTAT_MT_SLARSENT      0x40        // SLA+R sent, ACK
#define I2CSTAT_MT_SLARSENTNAK   0x48        // SLA+R sent, NOT ACK
#define I2CSTAT_MT_DATAREC       0x50        // Data received, ACK sent
#define I2CSTAT_MT_DATARECNAK    0x58        // Data received, NOT ACK sent

uint8_t I2C_status[20];
uint8_t I2C_statusCount = 0;

void resetArray(void)
{
    I2C_statusCount = 0;
    for(int i = 0; i < 20; i++)
    {
        I2C_status[i] = 0xFF;
    }
}

void I2C_init(int clockSpeed)
{
     // Configure pins
    LPC_IOCON->PIO0_4 = 1;  // I2C SCL FUNC standard mode
    LPC_IOCON->PIO0_5 = 1;  // I2C SDA FUNC standard mode
    // Configure I2C peripheral
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 5;    // Enable I2C clock
    LPC_SYSCON->PRESETCTRL |= 1 << 1;       // De-assert I2C reset

    // Configure clock speed/dutycycle
    LPC_I2C->SCLH = SystemCoreClock/(clockSpeed * 2);
    LPC_I2C->SCLL = LPC_I2C->SCLH;

    LPC_I2C->CONSET |= 1 << 6;  // Enable the I2C interface
}



int8_t I2C_writeData(uint8_t address, uint8_t data[], uint8_t len)
{
    bool loop = true;
    uint8_t i = 0;

    // Send start condition
    LPC_I2C->CONCLR = I2C_SI;
    LPC_I2C->CONSET = I2C_STA;  //Set STA bit

    while(loop)
    {
        // Wait until state changed(something happened)
        while((LPC_I2C->CONSET & I2C_SI) == 0);

        switch(LPC_I2C->STAT)
        {
        case I2CSTAT_START:
        case I2CSTAT_RSTART:
            LPC_I2C->DAT = address << 1;
            LPC_I2C->CONCLR = I2C_STA | I2C_SI;         // Clear STA bit and SI bit
            break;
        case I2CSTAT_MR_SLAWSENT:
        case I2CSTAT_MR_DATASENT:
            LPC_I2C->DAT = data[i++];
            LPC_I2C->CONCLR = I2C_SI;                       // Clear SI bit
            break;
        default:
            // We shouldn't receive another type of status so clear bit and send stop
            LPC_I2C->CONCLR = I2C_SI | I2C_STA | I2C_AA;         // Clear all bits
            return -1;
            break;
        }

        if(i >= len)
            loop = false;
    }
    return 0;
}

int8_t I2C_readData(uint8_t address, uint8_t data[], uint8_t len)
{
    uint8_t rxCount = 0;
    //  Send start condition
    LPC_I2C->CONCLR = I2C_SI;         // Clear SI bit
    LPC_I2C->CONSET = I2C_STA;

    while(rxCount < len)
    {
        //set_leds(8);
        // Wait until state changed(something happened)
        while((LPC_I2C->CONSET & I2C_SI) == 0);

        switch(LPC_I2C->STAT)
        {
        case I2CSTAT_START:
        case I2CSTAT_RSTART:
            LPC_I2C->DAT = (address << 1) | 1;
            LPC_I2C->CONCLR = I2C_STA | I2C_SI;         // Clear STA bit and SI bit
            break;
        case I2CSTAT_MT_SLARSENT:
            LPC_I2C->CONSET = I2C_AA;                       // Ack the data
            LPC_I2C->CONCLR = I2C_SI;                       // Clear SI bit
            break;
        case I2CSTAT_MT_DATAREC:
            data[rxCount++] = LPC_I2C->DAT;
            // Don't sent ACK when this is the last bit
            if(rxCount+1 == len)
                LPC_I2C->CONCLR = I2C_AA;                   // Clear ack bit
            LPC_I2C->CONCLR = I2C_SI;                       // Clear SI bit
            break;
        case I2CSTAT_MT_DATARECNAK:
            // Data received + NO ACK sent, send stop condition
            data[rxCount++] = LPC_I2C->DAT;
            LPC_I2C->CONSET = I2C_STO;
            LPC_I2C->CONCLR = I2C_SI;                       // Clear SI bit
            break;
        default:
            // We shouldn't receive another type of status so clear bit and send stop
            LPC_I2C->CONCLR = I2C_SI | I2C_STA | I2C_AA;         // Clear all bits
            return -1;
            break;
        }
    }

    return 0;
}

uint16_t readTemp(uint8_t address)
{
    uint8_t temp[2];
    uint8_t writeAddress = (address << 1);
    uint8_t readAddress = (address << 1) | 1;

    // Send start condition
    LPC_I2C->CONSET = I2C_STA;  //Set STA bit
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while(LPC_I2C->STAT != I2CSTAT_START);
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;

    // Send write address
    LPC_I2C->DAT = writeAddress;
    LPC_I2C->CONCLR = I2C_STA | I2C_SI;         // Clear STA bit and SI bit
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while(LPC_I2C->STAT != I2CSTAT_MR_SLAWSENT);         // Wait until data byte is transmitted
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;

    // sent write register(temperature)
    LPC_I2C->DAT = 0;
    LPC_I2C->CONCLR = I2C_STA | I2C_SI;         // Clear STA bit and SI bit
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while(LPC_I2C->STAT != I2CSTAT_MR_DATASENT);
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;        // Wait until data byte is transmitted

    // Repeated start
    LPC_I2C->CONCLR = I2C_SI;         // Clear STA bit and SI bit
    LPC_I2C->CONSET = I2C_STA;
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while(LPC_I2C->STAT != I2CSTAT_RSTART);
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;            //Wait until restart is sent

    // Start read message
    LPC_I2C->DAT = readAddress;
    LPC_I2C->CONCLR = I2C_STA | I2C_SI;     // Clear STA bit and SI bit
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while(LPC_I2C->STAT != I2CSTAT_MT_SLARSENT);
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;     // Wait for SLA+R transmit + ACK

    LPC_I2C->CONCLR = I2C_STA | I2C_SI;     // Clear STA bit and SI bit
    LPC_I2C->CONSET = I2C_AA;                   // Ack the data
    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while (LPC_I2C->STAT != I2CSTAT_MT_DATAREC);
    I2C_status[I2C_statusCount++] = LPC_I2C->STAT;   // Wait until data ACK
    temp[0] = LPC_I2C->DAT;

    LPC_I2C->CONCLR = I2C_STA | I2C_SI | I2C_AA;     // Clear STA bit and SI bit

    while((LPC_I2C->CONSET & I2C_SI) == 0);
    while (LPC_I2C->STAT != I2CSTAT_MT_DATARECNAK);
     I2C_status[I2C_statusCount++] = LPC_I2C->STAT;     // Wait until data ACK
    temp[1] = LPC_I2C->DAT;

    //stop
    LPC_I2C->CONSET = I2C_STO;                  // Stop transmission
    LPC_I2C->CONCLR = I2C_SI;
       I2C_status[I2C_statusCount++] = LPC_I2C->STAT;

    uint16_t temperature = ((temp[0] << 4) | (temp[1] >> 4));

    return temperature;
}

int main (void)
{
    init_leds();
    set_leds(0xFF);
    delay_ms(3000);
    I2C_init(I2C_CLOCK_SPEED);
    set_leds(1);

    delay_ms(500);
     while(1)
    {
        readTemp(TMP201_ADDRESS);

        int i = 0;
        while((i < 20) && (I2C_status[i]!= 0xFF))
        {
            set_leds(I2C_status[i++]);
            delay_ms(3000);
            set_leds(0xFF);
            delay_ms(50);
        }
        resetArray();
        for(int i = 0; i < 3; i++)
        {
            set_leds(0xFF);
            delay_ms(50);
            set_leds(0);
            delay_ms(50);
        }
    }
}
