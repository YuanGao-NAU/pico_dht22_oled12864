//
// Created by yg336 on 2025/3/22.
// to receive datetime info, in yyyy-mm-dd-ww-hh-mm-ss format

#ifndef MY_PROJECT_UART_H
#define MY_PROJECT_UART_H

#include "hardware/uart.h"
#include "hardware/irq.h"
#include "ds3231.h"
#include "pico/stdlib.h"

#define UART_ID uart0
#define UART_TX_PIN 16
#define UART_RX_PIN 17
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

void on_uart_rx();
void init_uart();

#endif //MY_PROJECT_UART_H
