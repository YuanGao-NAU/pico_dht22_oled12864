//
// Created by yg336 on 2025/3/22.
//
#include "max7219.h"

void send_data_raw(u_char reg, u_char data) {

    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);
    for(u_char i = 0; i < 16; i++) {
        gpio_put(PICO_DEFAULT_SPI_SCK_PIN, 0);
        if(i < 8) {
            gpio_put(PICO_DEFAULT_SPI_TX_PIN, (reg >> 7) & 0x01);
            reg = reg << 1;
        } else {
            gpio_put(PICO_DEFAULT_SPI_TX_PIN, (data >> 7) & 0x01);
            data = data << 1;
        }
        gpio_put(PICO_DEFAULT_SPI_SCK_PIN, 1);
    }
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
}

void max7219_send_data(u_char addr, u_char data) {
    send_data_raw(addr, data);
}

static inline void select_cs() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void deselect_cs() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

void init_max7219() {

    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_init(PICO_DEFAULT_SPI_TX_PIN);
    gpio_init(PICO_DEFAULT_SPI_SCK_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_SPI_TX_PIN, GPIO_OUT);
    gpio_set_dir(PICO_DEFAULT_SPI_SCK_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    gpio_put(PICO_DEFAULT_SPI_TX_PIN, 0);
    gpio_put(PICO_DEFAULT_SPI_SCK_PIN, 0);

    send_data_raw(CMD_SHUTDOWN, 0);
    send_data_raw(CMD_DISPLAYTEST, 0);
    send_data_raw(CMD_SCANLIMIT, 7);
    send_data_raw(CMD_DECODEMODE, 255);
    send_data_raw(CMD_SHUTDOWN, 1);
    send_data_raw(CMD_BRIGHTNESS, 15);
}