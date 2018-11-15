cmake_minimum_required(VERSION 3.1)

project(otus_hws)

add_custom_target(deploy
  COMMENT "deploying is executed")

configure_file(docs.cfg.in docs.cfg)

add_custom_target(docs
  DEPENDS
  ${CMAKE_CURRENT_BINARY_DIR}/../docs/html/index.html)

add_custom_command(OUTPUT
  ${CMAKE_CURRENT_BINARY_DIR}/../docs/html/index.html
  COMMAND
  doxygen docs.cfg
  COMMAND
  cp ${CMAKE_SOURCE_DIR}/index.html ${CMAKE_SOURCE_DIR}/docs)

add_subdirectory(helloworld)
add_subdirectory(ip_filter)
add_subdirectory(bin_id)
add_subdirectory(timus)
add_subdirectory(allocator)
add_subdirectory(print_ip)
add_subdirectory(editor)
add_subdirectory(matrix)
add_subdirectory(bulk)
add_subdirectory(bulkmt)

enable_testing()
