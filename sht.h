//
// Created by yg336 on 2022/9/4.
//

#ifndef MY_PROJECT_SHT_H
#define MY_PROJECT_SHT_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define SHT3X_ADDR 0x44
#define DATA_LEN 6

typedef struct {
    int humidity;
    int temp_celsius;
} dht_reading;

void read_from_sht(u_char *data);

void write_command(u_char command_high, u_char command_low);

#endif //MY_PROJECT_SHT_H
