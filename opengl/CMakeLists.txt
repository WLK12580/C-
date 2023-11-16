cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
 
project(test)
 
find_package(glfw3 REQUIRED)
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )
file(GLOB project_file glad.c window.cpp)
add_executable(${PROJECT_NAME} ${project_file})
 
target_link_libraries(${PROJECT_NAME}  ${OPENGL_LIBRARIES} glfw)
