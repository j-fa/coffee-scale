add_library(CoffeeScale
    CoffeeScale.cpp
)
target_link_libraries(CoffeeScale PUBLIC core)
target_include_directories(CoffeeScale PUBLIC .)

if(BUILD_PICO)
    add_executable(app
        main.cpp
    )
    target_link_libraries(app PRIVATE CoffeeScale bsp hal)
    pico_add_extra_outputs(app)
    # target_link_libraries(CoffeeScale PUBLIC bsp hal)
endif()