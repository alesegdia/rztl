cmake_minimum_required(VERSION 3.7)
project(xstf-test)

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(TESTS_FOLDER ./test)
file(GLOB_RECURSE XSTF_HEADERS include/rztl/*.h)

function(ADD_TEST TEST_NAME)
    add_executable(${TEST_NAME} ${TESTS_FOLDER}/${TEST_NAME}.cpp ${XSTF_HEADERS})
    include_directories(include)
endfunction(ADD_TEST)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

ADD_TEST(dynamicarray_test)
ADD_TEST(unordereddynamicarray_test)
