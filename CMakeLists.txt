cmake_minimum_required(VERSION 3.31)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 26)

set(SOURCE_FILE main.cpp dependencies/glad/src/glad.c
        Shader.cpp
        Shader.h
        stb_image.h
        Texture.cpp
        Texture.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

include_directories(dependencies/glad/include)
include_directories(dependencies/glm)

file(COPY shader DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
file(COPY resources DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_subdirectory(dependencies)

add_executable(LearnOpenGL ${SOURCE_FILE})
target_link_libraries(LearnOpenGL glfw)

