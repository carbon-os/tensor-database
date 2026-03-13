cmake_minimum_required(VERSION 3.22)
project(tensor-db VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(antlr4-runtime CONFIG REQUIRED)

add_subdirectory(tql)
add_subdirectory(storage)
add_subdirectory(inference)
# add_subdirectory(net)
# add_subdirectory(db)