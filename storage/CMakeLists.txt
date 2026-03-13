# storage/CMakeLists.txt

# 1. Find all external dependencies managed by vcpkg using exact casing
find_package(Crc32c CONFIG REQUIRED)
find_package(Snappy CONFIG REQUIRED)
find_package(roaring CONFIG REQUIRED)
find_package(hnswlib CONFIG REQUIRED)
find_package(msgpack-c CONFIG REQUIRED)

# 2. Define the storage library target
add_library(tensor_storage
    src/wal.cpp
    src/sst.cpp
    src/page.cpp
    src/rbm.cpp
    src/vec.cpp
    src/hnsw.cpp
    src/tok.cpp
)

# 3. Setup include directories
target_include_directories(tensor_storage
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${VCPKG_INSTALLED_DIR}/x64-linux/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 4. Link the vcpkg targets to the storage library
target_link_libraries(tensor_storage
    PUBLIC
        Crc32c::crc32c
        Snappy::snappy
        roaring::roaring
        hnswlib::hnswlib
        msgpack-c
)

# Require C++17
target_compile_features(tensor_storage PUBLIC cxx_std_17)