//
// Created by yg336 on 2022/9/4.
//
#include "sht.h"
#include "i2c.h"

void read_from_sht(u_char *data) {
    write_command(0x24, 0x00);
    i2c_read_blocking(I2C_PORT_1, SHT3X_ADDR, data, DATA_LEN, false);
}

void write_command(u_char command_high, u_char command_low) {
    uint8_t data[] = {command_high, command_low};
    i2c_write_blocking(I2C_PORT_1, SHT3X_ADDR, data, 2, false);
}
