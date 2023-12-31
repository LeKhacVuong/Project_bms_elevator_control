/*MIT License

Copyright (c) 2016 Roger Dahl

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*/
/*
 * TM1637_.c
 *
 *  Created and Modified on: 20-Oct-2018
 *      Author: Vidura Embedded
 */
#include "TM1637.h"
#include "main.h"
//#include "gpio.h"

#include "stm32l1xx_hal.h"

const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, // 0->9
	0x77, 0x7c, 0x39, 0x5E, 0x79, 0x71, 0x5C, 0x3e, 0x73, 0x08, // A-F (d = 13, o = 16, u = 17, p = 18 _ = 19
    0x00, 0b0111000, 0b0111110, 1 , 1<<3, 1<<1, 1<<4, 1<<2, 1<<5, 1<<4,
	1<<1, 0b1110111
};

void TM1637_ClkHigh(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}

void TM1637_ClkLow(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
}

void TM1637_DataHigh(void)
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
}

void TM1637_DataLow(void)
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
}

void TM1637_Demo(void)
{
	uint8_t i = 0;

	TM1637_Init();
	TM1637_SetBrightness(8);

	while(1){
		TM1637_DisplayDecimal(i++, 0);
	}
}


void TM1637_Init(void)
{
    TM1637_SetBrightness(8);
}

void TM1637_Display_4_char(uint8_t char1,uint8_t char2, uint8_t char3, uint8_t char4, int displaySeparator)
{
    unsigned char digitArr[4];

    digitArr[0] = segmentMap[char1];
    digitArr[1] = segmentMap[char2];
    digitArr[2] = segmentMap[char3];
    digitArr[3] = segmentMap[char4];

    if(displaySeparator){
        digitArr[2] |= 1 << 7;
    }

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}

void TM1637_DisplayDecimal(int v, int displaySeparator)
{
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void TM1637_SetBrightness(char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    TM1637_Start();
    TM1637_WriteByte(0x87 + brightness);
    TM1637_ReadResult();
    TM1637_Stop();
}

void TM1637_Start(void)
{
    TM1637_ClkHigh();
    TM1637_DataHigh();
    TM1637_DelayUsec(2);
    TM1637_DataLow();
}

void TM1637_Stop(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(2);
    TM1637_DataLow();
    TM1637_DelayUsec(2);
    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_DataHigh();
}

void TM1637_ReadResult(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);

    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_ClkLow();
}

void TM1637_WriteByte(unsigned char b)
{
	for (int i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (b & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(3);
		b >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(3);
	}
}

void TM1637_DelayUsec(unsigned int i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 100; ++j) {
					__NOP();
        }
    }
}


