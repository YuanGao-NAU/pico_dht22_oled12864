cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
#

include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(blink
        blink.c
        oled.h oled.c oledfont.h sht.h sht.c i2c.h max7219.h max7219.c ds3231.c ds3231.h uart.c uart.h ds3231.h)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(blink pico_stdlib hardware_i2c hardware_spi)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(blink)