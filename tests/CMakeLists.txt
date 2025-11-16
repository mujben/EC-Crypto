include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW ON)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_LIST_DIR}" TEST_SRC)

add_executable(all_tests ${TEST_SRC})
target_link_libraries(all_tests gtest_main krypto_lib)

include(GoogleTest)
gtest_discover_tests(all_tests)