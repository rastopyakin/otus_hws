cmake_minimum_required(VERSION 3.1)

project(allocator VERSION 0.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator main.cpp)


install(TARGETS allocator
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib)

configure_file(CPackConfig.cmake.in CPackConfig.cmake)

add_custom_command(OUTPUT ${PROJECT_NAME}-${PROJECT_VERSION}.deb
  COMMAND cpack --config CPackConfig.cmake
  COMMENT "package ${PROJECT_NAME} is building...")

add_custom_target(deploy-${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}-${PROJECT_VERSION}.deb
  COMMAND curl -T ${PROJECT_NAME}-${PROJECT_VERSION}.deb -urastopyakin:$ENV{BINTRAY_KEY} "https://api.bintray.com/content/rastopyakin/otus_hws/${PROJECT_NAME}/${PROJECT_VERSION}/${PROJECT_NAME}-${PROJECT_VERSION}.deb\;deb_distribution=trusty\;deb_component=main\;deb_architecture=amd64\;publish=1"
  COMMENT "${PROJECT_NAME} package is deploying")

add_dependencies(deploy deploy-${PROJECT_NAME})
