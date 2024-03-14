// @File		AD5601.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		13/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//

#ifndef AD5601_H
#define AD5601_H

#define AD5601_CLK PORTCbits.RC0
#define AD5601_DIN PORTCbits.RC1
#define AD5601_DOUT PORTCbits.RC2
#define AD5601_CS PORTCbits.RC3

#define AD5601_CLK_TRIS TRISCbits.RC0
#define AD5601_DIN_TRIS TRISCbits.RC1
#define AD5601_DOUT_TRIS TRISCbits.RC2
#define AD5601_CS_TRIS TRISCbits.RC3

#define AD5601_NORMAL 0x00
#define AD5601_1K 0x01
#define AD5601_100K 0x02
#define AD5601_THREE_STATE 0x03

static const void SPI_transfer(unsigned int data)
{     
    for(unsigned int mask = 0x8000; mask; mask >>= 1)
    {
        if(data & mask) AD5601_DIN = 1; else AD5601_DIN = 0;
            
         __asm__ __volatile__("nop");
         AD5601_CLK = 1;
         __asm__ __volatile__("nop");
         AD5601_CLK = 0;
         __asm__ __volatile__("nop");    
    }
}

void AD5601_Write(unsigned char mode, unsigned int value)
{
    unsigned int data = 0;
    
    data |= (mode << 14);
    data |= (value << 2);
    
    AD5601_CS = 0;
    SPI_transfer(data);
    AD5601_CS = 1;   
}

void AD5601_Init(void)
{
    AD5601_CLK_TRIS = 0;
    AD5601_DIN_TRIS = 0;
    AD5601_DOUT_TRIS = 1;
    AD5601_CS_TRIS = 0;
    
    AD5601_CS = 1;
}

#endif 
