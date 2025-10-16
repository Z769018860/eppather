# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.15)

project (C_PARSER LANGUAGES CXX)

add_subdirectory (antlr4-runtime)

file (GLOB ANTLR4_GENERATED_CPP_FILES ".antlr/*.cpp")
add_library (c-parser ${ANTLR4_GENERATED_CPP_FILES})
target_include_directories (c-parser PUBLIC ".antlr")
target_link_libraries (c-parser antlr4-runtime)
target_compile_features(c-parser PRIVATE cxx_std_17)
if (MSVC)
  target_compile_options (c-parser PRIVATE "/utf-8")
endif()