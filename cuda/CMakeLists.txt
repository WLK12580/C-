cmake_minimum_required(VERSION 3.8)
project(CUDA_TEST)

find_package(CUDA REQUIRED)

message(STATUS "cuda version: " ${CUDA_VERSION_STRING})
include_directories(${CUDA_INCLUDE_DIRS})

cuda_add_executable(cuda_test cuda_array.cu)
target_link_libraries(cuda_test ${CUDA_LIBRARIES})