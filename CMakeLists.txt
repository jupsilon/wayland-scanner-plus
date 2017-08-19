
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SCANNER "wayland-scanner")

add_executable(wayland-scanner-plus
  wayland-scanner-plus.cc
  )

add_custom_target(wayland-client.hpp
  COMMAND ./wayland-scanner-plus < wayland.xml > ../wayland-client.hpp
  DEPENDS wayland-scanner-plus
  )

add_executable(test-client
  test-client.cc
  wayland-client.hpp
  )

target_link_libraries(wayland-scanner-plus
  uuid
  )

add_custom_target(run
  COMMAND ./test-client
  DEPENDS wayland-scanner-plus wayland-client.hpp test-client
  )
