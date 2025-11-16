cmake_minimum_required(VERSION 3.19)
project(krypto)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        sodium
        GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
        GIT_TAG 260622e5b69bce9b955603a98e46354125a932a4
        GIT_SHALLOW ON
)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(sodium)

AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src/utils_src" UTILS_SRC)
add_library(krypto_lib ${UTILS_SRC})
target_include_directories(krypto_lib PUBLIC
        "${PROJECT_SOURCE_DIR}/src/utils_inc"
)
target_link_libraries(krypto_lib PUBLIC sodium)

option(BUILD_TESTS OFF)
option(BUILD_SRC OFF)
option(BUILD_ABE OFF)

if (BUILD_SRC)
    add_subdirectory(src)
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_ABE)
    add_subdirectory(AliceBobEve)
endif()
