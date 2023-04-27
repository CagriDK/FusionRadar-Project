cmake_minimum_required(VERSION 3.0.0)
project(ExampleTests VERSION 0.1.0)

add_executable(ExampleTests ExampleTests.cpp TestFunctions.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(PATH ${CMAKE_CURRENT_LIST_DIR}/lib)

if(WIN32)

else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    link_directories(${PATH})
endif()
target_link_libraries(ExampleTests PUBLIC ${PATH}/libgtest_main.a ${PATH}/libgtest.a ${PATH}/libgmock.a ${PATH}/libgmock_main.a)
   
add_test(
    NAME ExampleTests
    COMMAND ExampleTests
)