cmake_minimum_required(VERSION 3.19)
project(krypto)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_TESTS OFF)
option(BUILD_SRC OFF)

if (BUILD_SRC)
    add_subdirectory(src)
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

file(GLOB SRC_FILES "src/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(krypto_lib ${SRC_FILES})
target_include_directories(krypto_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)