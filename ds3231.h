#ifndef __DS3231_H
#define __DS3231_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define addr 0x68

/*the first verison use i2c1(GP6,GP7)*/
/*the new vesion use i2c0(GP20,GP21)*/
#define I2C_PORT	i2c0
#define I2C_SCL		20	
#define I2C_SDA		21

int ds3231SetTime(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second);
//int ds3231SetTime();
void ds3231ReadTime();
void i2c_port_0_init();
uint8_t bcd2dev(uint8_t bcd);
uint8_t dec2bcd(uint8_t dec);

#endif

