cmake_minimum_required(VERSION 3.1)

project(helloworld_test CXX)

include_directories(..)
add_executable(helloworld_test main_test.cpp)
target_link_libraries(helloworld_test hw)

enable_testing()
add_test(version helloworld_test)
