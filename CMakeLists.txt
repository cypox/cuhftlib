cmake_minimum_required(VERSION 3.10)
project(cuhftlib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cuhftlib lib/src/cuhftlib.cpp)

target_include_directories(cuhftlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(cuhftlib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/src
)

add_executable(run_stats examples/run_stats.cpp)

target_include_directories(run_stats
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>
)

target_include_directories(run_stats
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/src
)
