cmake_minimum_required(VERSION 3.5.1)
project(lab5 C)

set(SRC src/main.c
        src/bitStream.c
        src/bitStream.h
        src/compress.c
        src/decompress.c
        src/tree.c)

include_directories(src)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
