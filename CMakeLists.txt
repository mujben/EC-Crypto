cmake_minimum_required(VERSION 3.19)
project(krypto)

set(CMAKE_CXX_STANDARD 20)

AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src/utils_src" UTILS_SRC)
add_library(krypto_lib ${UTILS_SRC})
target_include_directories(krypto_lib PUBLIC
        "${PROJECT_SOURCE_DIR}/src/utils_inc"
)

option(BUILD_TESTS OFF)
option(BUILD_SRC OFF)

if (BUILD_SRC)
    add_subdirectory(src)
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
