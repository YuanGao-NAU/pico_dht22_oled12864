#include "pico/stdlib.h"
#include <stdio.h>
#include "oled.h"
#include "sht.h"
#include "max7219.h"
#include "ds3231.h"
#include "uart.h"

#define FONT_SIZE 16

extern char buf[];
int i = 0;
uint8_t datetime[16];
u_char result[6];
uint8_t strT[6];
uint8_t strH[6];
uint8_t flag = 0;

void get_and_display_data();
void register_timer();
bool repeating_timer_callback(__unused struct repeating_timer *t);

int main() {
    stdio_init_all();
    gpio_init(22);
    gpio_set_dir(22, GPIO_OUT);
    gpio_put(22, flag);
    i2c_port_1_init();
    i2c_port_0_init();
    init_uart();
    oledInit();
    oledClear();
    sleep_ms(1000);
    oledOn();
    sleep_ms(1000);
    oledClear();
    init_max7219();
    repeating_timer_t timer;
    add_repeating_timer_us(-1000000, repeating_timer_callback, NULL, &timer);

    while(1) {

//        read_from_sht(&result);
//        ds3231ReadTime();
//        u_int temp = ((result[0] << 8 | result[1]) * 175 / 65535.0 - 45) * 10;
//        u_int humi = ((result[3] << 8 | result[4]) * 100 / 65535.0) * 10;
//
//        buf[0] = (buf[0] >> 4) * 10 + (buf[0] & 0x0f); //sec
//        buf[1] = (buf[1] >> 4) * 10 + (buf[1] & 0x0f); //min
//        buf[2] = (buf[2] >> 4) * 10 + (buf[2] & 0x0f); //hour
//        buf[3] = (buf[3] >> 4) * 10 + (buf[3] & 0x0f); //week
//        buf[4] = (buf[4] >> 4) * 10 + (buf[4] & 0x0f); //day
//        buf[5] = (buf[5] >> 4) * 10 + (buf[5] & 0x0f); //mouth
//
//        strT[0] = temp / 100 + '0';
//        strT[1] = temp / 100 % 10 + '0';
//        strT[2] = 46;
//        strT[3] = temp % 10 + '0';
//        strT[4] = 67;
//        strT[5] = '\0';
//        strH[0] = humi / 100 + '0';
//        strH[1] = humi / 100 % 10 + '0';
//        strH[2] = 46;
//        strH[3] = humi % 10 + '0';
//        strH[4] = 37;
//        strH[5] = '\0';
//
////        if(FONT_SIZE == 32) {
////            for(u_int i = 0; i < 5; i++) {
////                strT[i] -= '0';
////                strH[i] -= '0';
////            }
////            strT[2] = 12;
////            strH[2] = 12;
////            strT[4] = 10;
////            strH[4] = 11;
////        }
//
//        oledShowString(0, 0, strT, FONT_SIZE);
//        oledShowString(0, 4, strH, FONT_SIZE);
//
//        if(buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x22) {
//            send_data_raw(CMD_BRIGHTNESS, 0);
//        }
//        if(buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x08) {
//            send_data_raw(CMD_BRIGHTNESS, 15);
//        }
//
//        max7219_send_data(1, buf[0] % 10);
//        max7219_send_data(2, buf[0] / 10);
//        max7219_send_data(3, 0b00001010);
//        max7219_send_data(4, buf[1] % 10);
//        max7219_send_data(5, buf[1] / 10);
//        max7219_send_data(6, 0b00001010);
//        max7219_send_data(7, buf[2] % 10);
//        max7219_send_data(8, buf[2] / 10);

    }
}

bool repeating_timer_callback(__unused struct repeating_timer *t) {
//    printf("Repeat at %lld\n", time_us_64());
    flag = ~flag;
    gpio_put(22, flag);
    get_and_display_data();
    return true;
}

void get_and_display_data() {
    read_from_sht(&result);
    ds3231ReadTime();
    u_int temp = ((result[0] << 8 | result[1]) * 175 / 65535.0 - 45) * 10;
    u_int humi = ((result[3] << 8 | result[4]) * 100 / 65535.0) * 10;

    buf[0] = (buf[0] >> 4) * 10 + (buf[0] & 0x0f); //sec
    buf[1] = (buf[1] >> 4) * 10 + (buf[1] & 0x0f); //min
    buf[2] = (buf[2] >> 4) * 10 + (buf[2] & 0x0f); //hour
    buf[3] = (buf[3] >> 4) * 10 + (buf[3] & 0x0f); //week
    buf[4] = (buf[4] >> 4) * 10 + (buf[4] & 0x0f); //day
    buf[5] = (buf[5] >> 4) * 10 + (buf[5] & 0x0f); //mouth

    strT[0] = temp / 100 + '0';
    strT[1] = temp / 100 % 10 + '0';
    strT[2] = 46;
    strT[3] = temp % 10 + '0';
    strT[4] = 67;
    strT[5] = '\0';
    strH[0] = humi / 100 + '0';
    strH[1] = humi / 100 % 10 + '0';
    strH[2] = 46;
    strH[3] = humi % 10 + '0';
    strH[4] = 37;
    strH[5] = '\0';

//        if(FONT_SIZE == 32) {
//            for(u_int i = 0; i < 5; i++) {
//                strT[i] -= '0';
//                strH[i] -= '0';
//            }
//            strT[2] = 12;
//            strH[2] = 12;
//            strT[4] = 10;
//            strH[4] = 11;
//        }

    oledShowString(0, 0, strT, FONT_SIZE);
    oledShowString(0, 4, strH, FONT_SIZE);

    if(buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x22) {
        send_data_raw(CMD_BRIGHTNESS, 0);
    }
    if(buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x08) {
        send_data_raw(CMD_BRIGHTNESS, 15);
    }

    max7219_send_data(1, buf[0] % 10);
    max7219_send_data(2, buf[0] / 10);
    max7219_send_data(3, 0b00001010);
    max7219_send_data(4, buf[1] % 10);
    max7219_send_data(5, buf[1] / 10);
    max7219_send_data(6, 0b00001010);
    max7219_send_data(7, buf[2] % 10);
    max7219_send_data(8, buf[2] / 10);
}
