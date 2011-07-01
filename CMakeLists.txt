cmake_minimum_required(VERSION 2.8)

project(TrainingGrounds)

set(CMAKE_CXX_FLAGS "-std=c++0x")

#For Gtest
include_directories(${TrainingGrounds_SOURCE_DIR}/thirdparty/gtest-1.6.0/include)

add_subdirectory(thirdparty)
add_subdirectory(src)
