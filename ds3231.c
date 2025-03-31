#include "ds3231.h"

//regaddr,seconds,minutes,hours,weekdays,days,months,years
char  buf[]={0x00,0x50,0x59,0x17,0x04,0x05,0x03,0x21};
char  *week[]={"SUN","Mon","Tues","Wed","Thur","Fri","Sat"};

int ds3231SetTime(uint8_t year, uint8_t month, uint8_t day, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second)
{
    char buf[2];
    //set second
    buf[0]=0x00;
    buf[1]=dec2bcd(second);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set minute
    buf[0]=0x01;
    buf[1]=dec2bcd(minute);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set hour
    buf[0]=0x02;
    buf[1]=dec2bcd(hour);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set weekday
    buf[0]=0x03;
    buf[1]=dec2bcd(weekday);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set day
    buf[0]=0x04;
    buf[1]=dec2bcd(day);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set month
    buf[0]=0x05;
    buf[1]=dec2bcd(month);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    //set year
    buf[0]=0x06;
    buf[1]=dec2bcd(year);
    i2c_write_blocking(I2C_PORT,addr,buf,2,false);
    return 0;
}

void ds3231ReadTime() 
{   
	uint8_t val = 0x00;  
	i2c_write_blocking(I2C_PORT,addr,&val,1,true);
	i2c_read_blocking(I2C_PORT,addr,buf,7,false);
}

void i2c_port_0_init() {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

uint8_t bcd2dev(uint8_t bcd) {
    return (((bcd >> 4)) * 10) + (bcd & 0x0f);
}

uint8_t dec2bcd(uint8_t dec) {
    return ((dec/10) << 4) + (dec % 10);
}

