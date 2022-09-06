//
// Created by yg336 on 2022/9/4.
//

#ifndef MY_PROJECT_DHT_H
#define MY_PROJECT_DHT_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define DHT_PIN 0
#define MAX_TIMINGS 85

typedef struct {
    int humidity;
    int temp_celsius;
} dht_reading;

void read_from_dht(dht_reading *result);

#endif //MY_PROJECT_DHT_H
