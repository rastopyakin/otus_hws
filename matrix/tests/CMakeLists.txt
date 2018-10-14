cmake_minimum_required(VERSION 3.8)

project(matrix_tests CXX)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(vector vector.cpp)
add_executable(cube cube.cpp)
target_link_libraries(vector ${Boost_LIBRARIES})
target_link_libraries(cube ${Boost_LIBRARIES})

enable_testing()
add_test(NAME vector COMMAND vector)
add_test(NAME cube COMMAND cube)
