cmake_minimum_required(VERSION 3.16)

project(lordfetch C)

add_executable(lordfetch
    src/lordfetch.c
    src/asciis.c
    src/info.c
    src/show.c
    src/environment.c
)
