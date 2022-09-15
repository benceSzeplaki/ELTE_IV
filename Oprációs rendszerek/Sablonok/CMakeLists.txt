cmake_minimum_required(VERSION 3.22)
project(Sablonok C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories("Messege que")
include_directories(Pipe)
include_directories(Signal)

add_executable(Sablonok
        "Messege que/main.c"
        Pipe/main.c
        Signal/main.c)
