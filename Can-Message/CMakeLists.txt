cmake_minimum_required(VERSION 3.17)
project(Can_Message C)

set(CMAKE_C_STANDARD 99)

add_executable(Can_Message main.c lib/binmatrix.c lib/binmatrix.h)