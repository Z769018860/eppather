# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("epat++" VERSION 1.5.0)

# ctest
include(CTest)
enable_testing()

# using utf-8
if(MSVC)
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# 包含数据协议
set(enable_epat_protocol_testing 1)
add_subdirectory("epat-protocol")

# 根据平台引入z3预编译库
set(Z3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libz3)

if(${CMAKE_SYSTEM_NAME} MATCHES "[Ll]inux")
  set(Z3_DIR "${Z3_DIR}/z3-4.12.2-x64-glibc-2.31")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "[Dd]arwin")
  set(Z3_DIR "${Z3_DIR}/z3-4.12.2-x64-osx-10.16")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "[Ww]indows")
  set(Z3_DIR "${Z3_DIR}/z3-4.12.2-x64-win")
else()
  message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(Z3_INCLUDE_DIR "${Z3_DIR}/include")
set(Z3_LIB_DIR "${Z3_DIR}/bin")

find_library(Z3_LIB
  NAMES z3 libz3
  HINTS ${Z3_LIB_DIR}
  NO_DEFAULT_PATH
)
message(Z3_LIB: ${Z3_LIB})
message(Z3_INCLUDE_DIR: ${Z3_INCLUDE_DIR})

# 包含子项目。
add_subdirectory("libepat++")

# 测试
enable_testing()
add_subdirectory("test")
