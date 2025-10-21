include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(all_tests test.cpp point_tests.cpp mathhelper_tests.cpp int_tests.cpp EC_tests.cpp subgroup_tests.cpp)
target_link_libraries(all_tests gtest_main krypto_lib)

include(GoogleTest)
gtest_discover_tests(all_tests)