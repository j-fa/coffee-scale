add_executable(test_app)
target_sources(test_app PRIVATE
    Test_CoffeeScale.cpp
    Test_LoadCell.cpp
)
target_link_libraries(test_app PUBLIC CoffeeScale Catch2::Catch2WithMain)

catch_discover_tests(test_app)
