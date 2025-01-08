cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(hx711_read_project)

enable_language(ASM)

pico_sdk_init()

add_executable(hx711_read
    main.cpp
    hx711_read.pio
    HX711.cpp
    Scale.cpp
)

pico_generate_pio_header(hx711_read ${CMAKE_CURRENT_LIST_DIR}/hx711_read.pio)

target_link_libraries(hx711_read pico_stdlib hardware_pio)

pico_add_extra_outputs(hx711_read)
