cmake_minimum_required(VERSION 3.1) # 3.1 << C_STANDARD 11

project(globs LANGUAGES CXX)

find_package(OpenCL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_compile_definitions(${PROJECT_NAME} PRIVATE CL_TARGET_OPENCL_VERSION=100)