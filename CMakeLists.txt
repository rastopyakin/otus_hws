cmake_minimum_required(VERSION 3.1)

project(otus_hws)

add_custom_target(deploy
  COMMENT "deploying is executed")

add_subdirectory(helloworld)

enable_testing()
