//
// Created by yg336 on 2025/3/22.
//

#ifndef MY_PROJECT_MAX7219_H
#define MY_PROJECT_MAX7219_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"
#include "time.h"

#define PICO_DEFAULT_SPI_TX_PIN 3
#define PICO_DEFAULT_SPI_SCK_PIN 2
#define DEFAULT_SPI spi0
#define PICO_DEFAULT_SPI_CSN_PIN 1

#define CMD_NOOP 0
#define CMD_DECODEMODE 9
#define CMD_BRIGHTNESS 10
#define CMD_SCANLIMIT 11
#define CMD_SHUTDOWN 12
#define CMD_DISPLAYTEST 15

void init_max7219();
void max7219_send_data(u_char addr, u_char data);
void send_data_raw(u_char reg, u_char data);
static inline void select_cs();
static inline void deselect_cs();

#endif //MY_PROJECT_MAX7219_H
