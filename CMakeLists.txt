cmake_minimum_required(VERSION 3.1)

project(fan_control_firmware C)

add_executable(${PROJECT_NAME} test/test_firmware.c)

add_library(code_under_test src/code_under_test.c src/unity.c)

add_library(fake fake/src/fakefuncs.c)

target_link_libraries(${PROJECT_NAME} code_under_test fake m)