//
// Created by yg336 on 2022/9/4.
//
#include "oled.h"
#include "oledfont.h"

void writeCommand(uint8_t i2cCommand) {
    uint8_t command[] = {0x00, i2cCommand};
    i2c_write_blocking(I2C_PORT_1, ADDR, command, 2, false);
}

void i2c_port_1_init() {
    i2c_init(I2C_PORT_1, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void writeData(uint8_t i2cData) {
    uint8_t data[] = {0x40, i2cData};
    i2c_write_blocking(I2C_PORT_1, ADDR, data, 2, false);
}

void oledFill(uint8_t fillData) {
    uint8_t m, n;
    for(m = 0; m < 8; m++) {
        writeCommand(0xb0 + m);
        writeCommand(0x01);
        writeCommand(0x10);

        for(n = 0; n < 129; n++) {
            writeData(fillData);
        }
    }
}

void oledSetPos(uint8_t x, uint8_t y) {
    writeCommand(0xb0+y);
    writeCommand((((x+2)&0xf0)>>4)|0x10);
    writeCommand(((x+2)&0x0f));
}

void oledClear() {
    uint8_t i, n;
    for(i = 0; i < 8; i++) {
        writeCommand(0xb0+i);
        writeCommand(0x02);
        writeCommand(0x10);
        for(n=0;n<128;n++) writeData(0);
    }
}

void oledOn() {
    uint8_t i, n;
    for(i = 0; i < 8; i++) {
        writeCommand(0xb0+i);
        writeCommand(0x02);
        writeCommand(0x10);
        for(n=0;n<128;n++) writeData(1);
    }
}

void oledShowChar(uint8_t x, uint8_t y, uint8_t ch, uint8_t size) {
    uint8_t c = 0, i = 0;
    c = ch - ' ';
    if(x >= MAX_COL) {
        x = 0;
        y = y + 2;
    }
    if(size == 16) {
        oledSetPos(x, y);
        for(i = 0; i < 8; i ++) {
            writeData(F8X16[c*16+i]);
        }
        oledSetPos(x, y+1);
        for(i = 0; i < 8; i ++) {
            writeData(F8X16[c*16+i+8]);
        }
    } else {
        oledSetPos(x, y);
        for(i = 0; i < 6; i ++) {
            writeData(F6x8[c][i]);
        }
    }
}

void oledShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size) {

}

void oledShowString(uint8_t x,uint8_t y,uint8_t *str,uint8_t size) {
    uint8_t j=0;
    while (str[j]!='\0'){
        oledShowChar(x,y,str[j],size);
        x+=8;
        if(x>120){
            x=0;y+=2;
        }
        j++;
    }
}

void oledDrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]) {
    unsigned int j=0;
    unsigned char x,y;

    if(y1%8==0) y=y1/8;
    else y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        oledSetPos(x0,y);
        for(x=x0;x<x1;x++)
        {
            writeData(BMP[j++]);
        }
    }
}

void oledInit() {
    writeCommand(0xAE);//set display display ON/OFF,AFH/AEH
    writeCommand(0x02);
    writeCommand(0x10);
    writeCommand(0x40);//set display start line:COM0
    writeCommand(0xB0);
    writeCommand(0x81);//set contrast control
    writeCommand(0xCF);


    writeCommand(0xA1);//entire display on: A4H:OFF/A5H:ON
    writeCommand(0xC8); //该指令控制显示方向显示方向0xc8或者0xc0
    //writeCommand(0xC0);

    writeCommand(0xAF);
    writeCommand(0xA7);//set normal/inverse display: A6H:normal/A7H:inverse

    writeCommand(0xA8);//set multiplex ratio
    writeCommand(0x3F);//1/64duty
    writeCommand(0xD3);//set display offset
    writeCommand(0x00);//
    writeCommand(0xD5);//set display clock divide ratio/oscillator frequency
    writeCommand(0x80);//105Hz
    writeCommand(0xD9);//Dis-charge /Pre-charge Period Mode Set
    writeCommand(0xF1);//
    writeCommand(0xDA);//Common Pads Hardware Configuration Mode Set
    writeCommand(0x12);//
    writeCommand(0xDB);//set vcomh deselect level
    writeCommand(0x40);//VCOM = β X VREF = (0.430 + A[7:0] X 0.006415) X VREF
    writeCommand(0xA4);
    writeCommand(0xA6);
    writeCommand(0xAF);//set display display ON/OFF,AEH/AFH
}
