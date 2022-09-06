#include "pico/stdlib.h"
#include <stdio.h>
#include "oled.h"
#include "raspberry26x32.h"
#include "dht.h"

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_init(DHT_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    i2c_port_1_init();
    oledInit();
    oledClear();
    sleep_ms(1000);
    oledOn();
    sleep_ms(1000);
    oledClear();
    char test[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    oledShowString(0, 0, test, 16);
    sleep_ms(1000);
    oledClear();
    oledDrawBMP(0, 0, IMG_WIDTH, IMG_HEIGHT, raspberry26x32);
    dht_reading result;
    uint8_t strT[6];
    uint8_t strH[6];
    while(1) {
        //gpio_init(DHT_PIN);
        read_from_dht(&result);
        strT[0] = result.temp_celsius / 100 + '0';
        strT[1] = result.temp_celsius / 100 % 10 + '0';
        strT[2] = 46;
        strT[3] = result.temp_celsius % 10 + '0';
        strT[4] = 67;
        strT[5] = '\0';
        strH[0] = result.humidity / 100 + '0';
        strH[1] = result.humidity / 100 % 10 + '0';
        strH[2] = 46;
        strH[3] = result.humidity % 10 + '0';
        strH[4] = 37;
        strH[5] = '\0';
        oledShowString(50, 2, strT, 16);
        oledShowString(50, 4, strH, 16);
        sleep_ms(2000);
    }
}
