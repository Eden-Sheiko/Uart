cmake_minimum_required(VERSION 3.22.1)
project(UartWrapperLinux C)

set(CMAKE_C_STANDARD 11)

add_executable(UartWrapperLinux main.c
        Inc/Uart.h
        Src/Uart.c)
