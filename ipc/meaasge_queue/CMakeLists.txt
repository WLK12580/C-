cmake_minimum_required(VERSION 2.14)
project(message_queue)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ./message_queue_send.cpp)
add_executable(recv ./message_queue_recv.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} rt)