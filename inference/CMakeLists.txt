find_package(llama CONFIG REQUIRED)

add_library(inference STATIC
    src/embed.cpp
    src/reasoning.cpp
)

target_include_directories(inference
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(inference
    PRIVATE
        llama
)

target_compile_features(inference PUBLIC cxx_std_17)

add_executable(inference-embed-test     tests/main_embed.cpp)
add_executable(inference-reasoning-test tests/main_reasoning.cpp)

target_link_libraries(inference-embed-test     PRIVATE inference)
target_link_libraries(inference-reasoning-test PRIVATE inference)