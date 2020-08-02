
cmake_minimum_required(VERSION 3.18)

set(
    ALTERNATE_GCC_DIR
    "/home/ran/gcc/bin/"
)

set(
    CMAKE_C_COMPILER    
    ${ALTERNATE_GCC_DIR}/gcc
)

set(
    CMAKE_CXX_COMPILER 
    ${ALTERNATE_GCC_DIR}/g++
)


project(executors CXX)

add_executable( ${PROJECT_NAME} )

set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES 
        CXX_STANDARD    20
)

target_compile_options(
    executors
    PRIVATE
        -fconcepts-diagnostics-depth=10
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        main_free_func.cpp
)

