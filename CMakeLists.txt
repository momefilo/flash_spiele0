cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD yd_rp2040)
include(pico_sdk_import.cmake)
project(flash_spiele0_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(flash_spiele0
flash_spiele0.c
)

add_subdirectory(./ili9341)
pico_add_extra_outputs(flash_spiele0)
target_link_libraries(flash_spiele0
							pico_stdlib
							ili9341
							hardware_flash
							hardware_sync)
