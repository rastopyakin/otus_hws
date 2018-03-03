cmake_minimum_required(VERSION 3.1)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

configure_file(version.hpp.in version.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(hw SHARED hw.cpp)

add_executable(helloworld main.cpp)
target_link_libraries(helloworld hw)

enable_testing()

add_subdirectory(test)
