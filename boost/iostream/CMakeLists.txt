cmake_minimum_required(VERSION 3.0.2)
set(CMAKE_CXX_STANDARD 14)
project(Test)

add_definitions(-g -O3)

find_package(Boost REQUIRED COMPONENTS filesystem iostreams serialization)
set(SRC
    compress.cpp
)


add_executable(project ${SRC})

target_link_libraries(project  -lm -lstdc++ ${GZIP_LIBRARIES} ${Boost_LIBRARIES})
