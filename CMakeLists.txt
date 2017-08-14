
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SCANNER "wayland-scanner")

add_executable(wayland-scanner-plus
  wayland-scanner-plus.cc
  )

target_link_libraries(wayland-scanner-plus
  uuid
  )

add_custom_target(run
  COMMAND ./wayland-scanner-plus < weston-desktop-shell.xml
  DEPENDS wayland-scanner-plus
  )

