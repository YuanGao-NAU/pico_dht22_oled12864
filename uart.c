//
// Created by yg336 on 2025/3/22.
//
#include "uart.h"

extern int i;
extern uint8_t datetime[16];

void on_uart_rx() {
    while(uart_is_readable(UART_ID)) {
        datetime[i++] = uart_getc(UART_ID) - '0';
    }
    if(i == 16) {
        i=0;
        uint8_t year = datetime[0] * 1000 + datetime[1] * 100 + datetime[2] * 10 + datetime[3];
        uint8_t month = datetime[4] * 10 + datetime[5];
        uint8_t day = datetime[6] * 10 + datetime[7];
        uint8_t weekday = datetime[8] * 10 + datetime[9];
        uint8_t hour = datetime[10] * 10 + datetime[11];
        uint8_t minute = datetime[12] * 10 + datetime[13];
        uint8_t second = datetime[14] * 10 + datetime[15];
        ds3231SetTime(year, month, day, weekday, hour, minute, second);
        uart_puts(UART_ID, "\ntime has been set\n");
    }
}

void init_uart() {
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    // OK, all set up.
    // Lets send a basic string out, and then run a loop and wait for RX interrupts
    // The handler will count them, but also reflect the incoming data back with a slight change!
    uart_puts(UART_ID, "\ndatetime format yyyy-mm-dd-ww-hh-mm-ss\n");
}
