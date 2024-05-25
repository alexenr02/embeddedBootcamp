cmake_minimum_required(VERSION 3.29.3)

project(
  Clock
  VERSION 1.0
  LANGUAGES C)

add_executable(main
  ${CMAKE_CURRENT_SOURCE_DIR}/App/source/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/App/source/scheduler.c
  ${CMAKE_CURRENT_SOURCE_DIR}/App/source/rtc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/App/source/queue.c
)

target_include_directories(main
  PUBLIC
  "./App/include"
)

add_subdirectory(docs)