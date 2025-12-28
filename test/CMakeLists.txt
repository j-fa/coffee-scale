include(FetchContent)

# Download Catch2 from GitHub. Using a specific tag ensures reproducibility.
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(Catch2)

# Create the test executable that will run on your host machine
add_executable(unit_tests
    test_example.cpp
    # Add more test files here
)

# Link your code (e.g., the 'bsp' library) and Catch2.
# Catch2::Catch2WithMain provides the main() function for the test runner.
#
# NOTE: For host-based tests, your 'bsp' library must be buildable on the host.
# This may require using preprocessor guards (#ifdef) to exclude Pico-specific
# hardware calls when not compiling for the Pico.
target_link_libraries(unit_tests PRIVATE
    Catch2::Catch2WithMain
    CoffeeScale
)

# Enable test discovery with CTest
include(CTest)
add_test(NAME unit_tests COMMAND unit_tests)
