cmake_minimum_required(VERSION 3.22)

find_package(httplib CONFIG REQUIRED)
find_package(llama CONFIG REQUIRED)

add_executable(tensor-llm
    src/main.cpp
    src/server.cpp
)

target_include_directories(tensor-llm PRIVATE include)

target_link_libraries(tensor-llm PRIVATE
    httplib::httplib
    llama
    ${CMAKE_THREAD_LIBS_INIT}
)

target_compile_features(tensor-llm PRIVATE cxx_std_17)

if (MSVC)
    target_compile_options(tensor-llm PRIVATE /wd4996)
endif()

install(TARGETS tensor-llm RUNTIME DESTINATION bin)