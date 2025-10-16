# CMakeList.txt: epat-protocol项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("libepat++" VERSION 1.5.0)

set(DEBUG_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.debug")

if(EXISTS ${DEBUG_FILE_PATH})
  message(STATUS "Epat++ debug mode enabled.")
  add_compile_definitions(EPAT_DEBUG)
  add_compile_definitions(EPAT_LOG)
else()
  message(STATUS "Epat++ mode disabled.")
endif()

file(GLOB LIB_EPAT++_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
add_library(libepat++ STATIC ${LIB_EPAT++_SRCS})
target_link_libraries(libepat++ PUBLIC epat-protocol ${Z3_LIB})
target_include_directories(libepat++ PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/utils"
  "${CMAKE_CURRENT_SOURCE_DIR}/../epat-protocol/utils"
  "${CMAKE_CURRENT_SOURCE_DIR}/../epat-protocol/include"
  ${Z3_INCLUDE_DIR}
)
target_compile_features(libepat++ PRIVATE cxx_std_17)
