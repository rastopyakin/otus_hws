cmake_minimum_required(VERSION 3.1)

project(helloworld_test CXX)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(.. ${Boost_INCLUDE_DIRS})
add_executable(helloworld_test main_test.cpp)
target_link_libraries(helloworld_test hw ${Boost_LIBRARIES})

enable_testing()
add_test(NAME version COMMAND helloworld_test)
