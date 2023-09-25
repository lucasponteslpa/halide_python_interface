cmake_minimum_required(VERSION 3.22)
project(mymath)

find_package(Halide REQUIRED)
find_package(Python3 REQUIRED Development Interpreter)

set(SRCS "mymath.cpp")

add_library(run_lib SHARED IMPORTED)
set_target_properties(run_lib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/librun_c_backend_and_native.so)

Python3_add_library(mymath MODULE WITH_SOABI ${SRCS})
target_link_libraries(mymath PRIVATE run_lib)
set_target_properties(
        mymath
        PROPERTIES
            PREFIX ""
            OUTPUT_NAME "mymath"
            LINKER_LANGUAGE C
        )

# add_executable(mymath_c mymath.cpp )
target_include_directories(mymath PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            )