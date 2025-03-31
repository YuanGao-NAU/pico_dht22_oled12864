//
// Created by yg336 on 2022/9/4.
//

#ifndef MY_PROJECT_OLED_H
#define MY_PROJECT_OLED_H

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "i2c.h"

#define MAX_COL	128
#define MAX_ROW	64

void oledInit();
void i2c_port_1_init();
void writeData(uint8_t i2cData);
void writeCommand(uint8_t i2cCommand);
void oledFill(uint8_t fillData);
void oledSetPos(uint8_t x, uint8_t y);
void oledShowNumber(uint8_t x, uint8_t y, uint8_t number);
void oledClear();
void oledOn();
void oledShowChar(uint8_t x, uint8_t y, uint8_t ch, uint8_t size);
void oledShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void oledShowString(uint8_t x,uint8_t y,uint8_t *str,uint8_t size);
void oledDrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]);


#endif //MY_PROJECT_OLED_H
