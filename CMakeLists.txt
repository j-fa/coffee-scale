cmake_minimum_required(VERSION 3.13)

# Add an option to enable/disable tests, defaulting to ON for debug builds
option(BUILD_TESTING "Build the unit tests" OFF)
option(BUILD_PICO "Build for Raspberry Pi Pico" OFF)

if (PICO_SDK_PATH AND EXISTS "${PICO_SDK_PATH}/pico_sdk_init.cmake")
    set(BUILD_PICO ON)
    message(STATUS "Configuring for Pico target")
    include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()

project(coffee_scale)

# This logic separates the build configuration for the Pico (target)
# from the build configuration for your host machine (for tests).
if (BUILD_PICO)
    # --- TARGET BUILD (for Raspberry Pi Pico) ---
    pico_sdk_init()
    enable_language(ASM)

    add_subdirectory(src)
else()
    # --- HOST BUILD (for running unit tests) ---
    if(BUILD_TESTING)
        message(STATUS "Configuring for Host build (tests)")
        enable_testing()
        add_subdirectory(src)  # Add src to build host-compatible libraries
        add_subdirectory(test) # Add tests which will link against them
    endif()
endif()