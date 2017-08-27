
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SCANNER "wayland-scanner")

add_executable(wayland-scanner-plus
  wayland-scanner-plus.cc
  wayland-scanner-plus-template.cc
  utilities/misc.cc
  utilities/uuid.cc
  )

add_custom_target(wayland-client.hpp ALL
  COMMAND ./wayland-scanner-plus < wayland.xml > ../wayland-client.hpp
  DEPENDS wayland-scanner-plus
  )

add_custom_target(weston-desktop-hpp ALL
  COMMAND ./wayland-scanner-plus < weston-desktop-shell.xml > ../weston-desktop-client.hpp
  DEPENDS wayland-scanner-plus
  )

add_custom_command(OUTPUT ../weston-desktop.c
  COMMAND wayland-scanner code          < weston-desktop-shell.xml > ../weston-desktop.c
  COMMAND wayland-scanner client-header < weston-desktop-shell.xml > ../weston-desktop-client.h
)

add_executable(test-client
  test-client.cc
  weston-desktop.c
  utilities/misc.cc
  )

target_link_libraries(wayland-scanner-plus
  uuid
  )

target_link_libraries(test-client
  wayland-client
  wayland-egl
  uuid
  EGL
  GL
  )

add_custom_target(run
  COMMAND ./test-client
  DEPENDS wayland-scanner-plus wayland-client.hpp test-client
  )
