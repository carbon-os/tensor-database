cmake_minimum_required(VERSION 3.22)
project(tensor-db VERSION 0.1.0 LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GGML_CUDA "Enable CUDA backend for llama.cpp" ON)

find_package(CUDAToolkit REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)

add_subdirectory(tql)
add_subdirectory(storage)
add_subdirectory(inference)
add_subdirectory(tensor-llm)   # ← new
# add_subdirectory(net)
# add_subdirectory(db)