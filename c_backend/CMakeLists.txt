cmake_minimum_required(VERSION 3.22)
project(c_backend)

enable_testing()

# Set up language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Find Halide
find_package(Halide REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)

add_halide_generator(pipeline.generator SOURCES pipeline_generator.cpp)

add_halide_library(pipeline_c FROM pipeline.generator
                   C_BACKEND
                   GENERATOR pipeline
                   PYTHON_EXTENSION output_path_var)

add_halide_library(pipeline_native FROM pipeline.generator
                   GENERATOR pipeline)

# add_executable(run_c_backend_and_native run.cpp)
add_library(run_c_backend_and_native SHARED run.cpp run.h)
# target_link_libraries(run_c_backend_and_native
#                       PRIVATE
#                       pipeline_native
#                       pipeline_c)
target_link_libraries(run_c_backend_and_native
                      PRIVATE
                      pipeline_native
                      pipeline_c
                      Halide::Halide
                      Halide::Runtime)
