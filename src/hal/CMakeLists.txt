add_library(hal HX711.cpp)
target_link_libraries(hal PRIVATE
    bsp
    core
)
target_include_directories(hal PUBLIC .)