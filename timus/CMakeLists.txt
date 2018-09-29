cmake_minimum_required(VERSION 3.1)

project(timus VERSION 0.1.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(t1000 t1000.cpp)
add_executable(t1001 t1001.cpp)
add_executable(t1785 t1785.cpp)
add_executable(t1293 t1293.cpp)
add_executable(t2012 t2012.cpp)
add_executable(t1409 t1409.cpp)
add_executable(t1877 t1877.cpp)
add_executable(t2001 t2001.cpp)
add_executable(t1264 t1264.cpp)
add_executable(t1787 t1787.cpp)
add_executable(t1545 t1545.cpp)
add_executable(t1496 t1496.cpp)
add_executable(t1196 t1196.cpp)
add_executable(t1837 t1837.cpp)
add_executable(t1820 t1820.cpp)
add_executable(t1197 t1197.cpp)
add_executable(t2066 t2066.cpp)
add_executable(t1880 t1880.cpp)
add_executable(t1639 t1639.cpp)
add_executable(t1910 t1910.cpp)
add_executable(t1924 t1924.cpp)
add_executable(t2023 t2023.cpp)
add_executable(t2100 t2100.cpp)
add_executable(t1209 t1209.cpp)
add_executable(t1567 t1567.cpp)
add_executable(t1319 t1319.cpp)
add_executable(t1225 t1225.cpp)
add_executable(t1068 t1068.cpp)
add_executable(t1313 t1313.cpp)
add_executable(t1100 t1100.cpp)
add_executable(t1991 t1991.cpp)
add_executable(t1263 t1263.cpp)
add_executable(t1585 t1585.cpp)
add_executable(t1581 t1581.cpp)

install(TARGETS
  t1000 t1001 t1785 t1293 t2012 t1409 t1877 t2001 t1264 t1787 t1545 t1496 t1196 t1837 t2066 t1639
  t1820 t1197 t1880 t1910 t1924 t2023 t2100 t1209 t1567 t1319 t1225 t1068 t1313 t1100 t1991 t1263
  t1585 t1581
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
