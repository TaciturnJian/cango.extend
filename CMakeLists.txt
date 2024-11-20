cmake_minimum_required(VERSION 3.21)

project(cango.extend)

add_library(cango_extend INTERFACE)
add_library(cango::extend ALIAS cango_extend)
target_include_directories(cango_extend INTERFACE include)
set_target_properties(cango_extend PROPERTIES CXX_STANDARD 20)


if (MSVC)
    target_compile_options(cango_extend INTERFACE "/utf-8")
endif()


if (PROJECT_IS_TOP_LEVEL)
    add_executable(cango_extend_grammar_test test/grammar_test.cpp)
    target_link_libraries(cango_extend_grammar_test cango::extend)
    set_target_properties(cango_extend_grammar_test PROPERTIES CXX_STANDARD 20)
endif()
