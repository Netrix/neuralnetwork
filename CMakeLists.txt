cmake_minimum_required(VERSION 3.3)

#set(CMAKE_CXX_FLAGS "-std=c++14 -g -march=native -O3 -pedantic -Wall -Werror -lpthread")
add_definitions(-std=c++14)
add_definitions(-march=native)
#add_definitions(-O3)
add_definitions(-Wall)
#add_definitions(-g)

link_libraries(pthread)

add_subdirectory(src)

if(MSVC)
    set(gtest_force_shared_crt ON)
endif()

add_subdirectory(modules/gtest)
include_directories(modules/gtest/include)
include_directories(modules/gtest/gtest/include)
include_directories(src)

add_subdirectory(tst)
