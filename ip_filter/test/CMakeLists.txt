cmake_minimum_required(VERSION 3.1)

project(ip_filter_test CXX)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(.. ${Boost_INCLUDE_DIRS})
add_executable(ip_filter_test main_test.cpp ../ip_filter.cpp)
target_link_libraries(ip_filter_test ${Boost_LIBRARIES})

enable_testing()
add_test(NAME ip_filter COMMAND ip_filter_test)
