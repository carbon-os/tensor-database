add_library(tql STATIC
    src/TQLLexer.cpp
    src/TQLParser.cpp
    src/TQLParserVisitor.cpp
    src/TQLParserBaseVisitor.cpp
    src/compiler.cpp
    src/import_resolver.cpp
    src/scope_checker.cpp
    src/type_checker.cpp
    src/aggregate_checker.cpp
    src/constant_folder.cpp
)

target_include_directories(tql
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/tensor/tql
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tql
    PUBLIC
        antlr4_static
)

add_executable(tql-test tests/main.cpp)

target_link_libraries(tql-test
    PRIVATE
        tql
)