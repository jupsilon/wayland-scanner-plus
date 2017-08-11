
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS
  "-std=c++1z -Wall"
  )
set(SCANNER
  "wayland-scanner"
  )

add_executable(wayland-scanner-plus
  wayland-scanner-plus.cc
  )

target_link_libraries(wayland-scanner-plus
  )

add_custom_target(run
  COMMAND ./wayland-scanner-plus
  DEPENDS wayland-scanner-plus
  )
  
