cmake_minimum_required(VERSION 3.10)
project(ComputerGraphicsPhase1)

set(CMAKE_CXX_STANDARD 17)

# 1. Find OpenGL and GLUT (Works automatically on macOS)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})

# 2. Build the Generator (Standard C++, no OpenGL needed)
add_executable(generator generator/generator.cpp)

# 3. Build the Engine (Needs OpenGL and GLUT)
add_executable(engine engine/main.cpp)

# macOS specific: Link frameworks and ignore deprecation warnings
if(APPLE)
    target_link_libraries(engine "-framework OpenGL" "-framework GLUT")
    target_compile_options(engine PRIVATE "-Wno-deprecated-declarations")
else() 
    target_link_libraries(engine ${GLUT_LIBRARY} ${OpenGL_LIBRARIES})
endif()