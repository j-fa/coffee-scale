add_library(bsp)
pico_generate_pio_header(bsp ${CMAKE_CURRENT_LIST_DIR}/hx711_read.pio)
target_link_libraries(bsp PUBLIC pico_stdlib hardware_pio)
