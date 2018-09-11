cmake_minimum_required(VERSION 3.1)

project(print_ip VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(print_ip main.cpp)


install(TARGETS print_ip
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib)

configure_file(CPackConfig.cmake.in CPackConfig.cmake)
configure_file(docs.cfg.in docs.cfg)

add_custom_command(OUTPUT ${PROJECT_NAME}-${PROJECT_VERSION}.deb
  COMMAND cpack --config CPackConfig.cmake
  COMMENT "package ${PROJECT_NAME} is building...")

add_custom_command(OUTPUT
  ${CMAKE_CURRENT_BINARY_DIR}/../../docs/${PROJECT_NAME}/html/index.html
  COMMAND
  mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/../../docs/${PROJECT_NAME}
  COMMAND
  doxygen docs.cfg)

add_custom_target(deploy-${PROJECT_NAME}
  DEPENDS ${PROJECT_NAME}-${PROJECT_VERSION}.deb
  COMMAND curl -T ${PROJECT_NAME}-${PROJECT_VERSION}.deb -urastopyakin:$ENV{BINTRAY_KEY} "https://api.bintray.com/content/rastopyakin/otus_hws/${PROJECT_NAME}/${PROJECT_VERSION}/${PROJECT_NAME}-${PROJECT_VERSION}.deb\;deb_distribution=trusty\;deb_component=main\;deb_architecture=amd64\;publish=1"
  COMMENT "${PROJECT_NAME} package is deploying")

add_custom_target(docs-${PROJECT_NAME}
  DEPENDS
  ${CMAKE_CURRENT_BINARY_DIR}/../../docs/${PROJECT_NAME}/html/index.html)

add_dependencies(deploy deploy-${PROJECT_NAME})
add_dependencies(docs docs-${PROJECT_NAME})
