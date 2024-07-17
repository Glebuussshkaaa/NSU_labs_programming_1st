cmake_minimum_required(VERSION 3.5.1)
project(lab10 C)

set(SRC src/main.c src/convexHull.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)

target_compile_definitions(${PROJECT_NAME} PRIVATE _GNU_SOURCE=1)
