cmake_minimum_required(VERSION 3.1)

project(otus_hws)

add_custom_target(deploy
  COMMENT "deploying is executed")

add_subdirectory(helloworld)
add_subdirectory(ip_filter)
add_subdirectory(bin_id)
add_subdirectory(timus)
add_subdirectory(allocator)
add_subdirectory(print_ip)

enable_testing()
