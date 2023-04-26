cmake_minimum_required(VERSION 3.0.0)
project(FusionRadarBase VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(FusionRadarBase main.cpp Server.cpp)
add_executable(FusionRadarClient Client.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(test)

if(WIN32)
    set(BOOST_INCLUDEDIR     "C:/boost_1_71_0/boost")
    set(BOOST_LIBRARYDIR     "C:/boost_1_71_0/stage/lib")
    set(BOOST_ROOT           "C:/boost_1_71_0")
    
    find_package(Boost 1.71 REQUIRED)
    if(MINGW)
    target_link_libraries(FusionRadarBase ${Boost_LIBRARIES} ws2_32 wsock32)
    target_link_libraries(FusionRadarClient ${Boost_LIBRARIES} ws2_32 wsock32)
    endif()
    if(Boost_FOUND)
        message(STATUS "Boost Libraries are found")
        message(
        "BOOST package:
            found: ${Boost_FOUND}
            BOOST_INCLUDEDIR: ${BOOST_INCLUDEDIR}
            System Boost Dir: ${Boost_LIBRARIES}
            BOOST_LIBRARYDIR: ${BOOST_LIBRARYDIR}
            BOOST_ROOT: ${BOOST_ROOT}
            CMakeDir: ${CMAKE_CURRENT_LIST_DIR}
            "
        )
    else()
        message(STATUS "Failed to find Boost Libraries")
    endif()
    target_include_directories(FusionRadarBase PUBLIC ${BOOST_ROOT})
    target_include_directories(FusionRadarClient PUBLIC ${BOOST_ROOT})
else()
    find_package( Boost 1.71 COMPONENTS program_options REQUIRED )
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    include_directories( ${Boost_INCLUDE_DIR} )
    target_link_libraries(FusionRadarBase LINK_PUBLIC ${Boost_LIBRARIES} )
    target_link_libraries(FusionRadarClient LINK_PUBLIC ${Boost_LIBRARIES} )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)




