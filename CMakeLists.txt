cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(blink
        blink.c
        oled.h oled.c oledfont.h raspberry26x32.h dht.h dht.c)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(blink pico_stdlib hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(blink)