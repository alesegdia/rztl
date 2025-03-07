cmake_minimum_required(VERSION 3.10)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set the project name
project(RZTLTests)

enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp")
file(GLOB RZTL_SOURCES "include/**/*.h")

add_executable(rztl_tests ${TEST_SOURCES} ${RZTL_SOURCES})

target_link_libraries(
    rztl_tests
    GTest::gtest_main
)

target_include_directories(
    rztl_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(rztl_tests)


