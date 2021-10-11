cmake_minimum_required(VERSION 3.17)
project(PortoFlats C)


set(CMAKE_C_STANDARD 99)

add_executable(PortoFlats main.c main.h)

target_link_libraries(PortoFlats PRIVATE m)