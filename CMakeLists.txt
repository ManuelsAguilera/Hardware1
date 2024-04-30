cmake_minimum_required(VERSION 3.20)
project(Hardware)

set(SRC_FOLDER     "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "${SRC_FOLDER}/*.c"
    "${SRC_FOLDER}/*.h"
)

add_executable(Hardware ${SRC})
target_include_directories(Hardware PUBLIC ${INCLUDE_FOLDER})
target_link_libraries(Hardware PUBLIC pthread)
