cmake_minimum_required(VERSION 3.9.0)
project(trie VERSION 0.1.0 LANGUAGES C)

add_library(trie ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

target_include_directories(trie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

option(BUILD_EXAMPLE "build an example" OFF)

if(BUILD_EXAMPLE)
    message("Build example")
    add_executable(trie_example example/main.c)
    target_link_libraries(trie_example PRIVATE trie)
endif()