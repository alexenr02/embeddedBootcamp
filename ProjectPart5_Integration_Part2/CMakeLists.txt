cmake_minimum_required(VERSION 3.1...3.29)

project(
  Clock
  VERSION 1.0
  LANGUAGES C)

add_executable(main
  ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/scheduler.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/rtc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/queue.c
)

target_include_directories(main
  PUBLIC
  "./include"
)