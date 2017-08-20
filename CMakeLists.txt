
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SCANNER "wayland-scanner")

add_executable(wayland-scanner-plus
  wayland-scanner-plus.cc
  template.cc
  )

add_custom_target(wayland-client.hpp ALL
  COMMAND ./wayland-scanner-plus < wayland.xml > ../wayland-client.hpp
  DEPENDS wayland-scanner-plus
  )

add_executable(test-client
  test-client.cc
  )

target_link_libraries(wayland-scanner-plus
  uuid
  )

target_link_libraries(test-client
  wayland-client
  )

add_custom_target(run
  COMMAND ./test-client
  DEPENDS wayland-scanner-plus wayland-client.hpp test-client
  )
