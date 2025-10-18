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
