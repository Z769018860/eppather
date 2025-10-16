# CMakeList.txt: epat-protocol项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("epat-protocol" VERSION 1.5.0)

# 语法分析器
add_subdirectory (grammar)

file (GLOB epat-protocol_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library (epat-protocol STATIC ${epat-protocol_SRC})
target_include_directories (epat-protocol PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries (epat-protocol c-parser)
target_compile_features(epat-protocol PRIVATE cxx_std_17)
if (MSVC)
  target_compile_options (epat-protocol PRIVATE "/utf-8")
endif()

# 测试
enable_testing ()
add_subdirectory ("test")
