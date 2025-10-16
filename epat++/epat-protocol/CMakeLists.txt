# CMakeList.txt: epat-protocol项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("epat-protocol" VERSION 1.5.0)

# antlr4-runtime
add_subdirectory("grammar/antlr4-runtime")

file(GLOB EPAT_PROTOCOL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB ANTLR4_GENERATED_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/grammar/.antlr/*.cpp")
file(GLOB CPARSER_IMP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/grammar/src/*.cpp")

set(DEBUG_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.debug")

if(EXISTS ${DEBUG_FILE_PATH})
  message(STATUS "Epat protocol debug mode enabled.")
  add_compile_definitions(EPAT_DEBUG)
  add_compile_definitions(EPAT_LOG)
else()
  message(STATUS "Epat protocol mode disabled.")
endif()

add_library(epat-protocol STATIC
  ${EPAT_PROTOCOL_SRC}
  ${ANTLR4_GENERATED_CPP_FILES}
  ${CPARSER_IMP_FILES}
)
target_include_directories(epat-protocol PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(epat-protocol PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/utils
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/.antlr
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/include
)
target_link_libraries(epat-protocol PRIVATE antlr4-runtime)
target_compile_features(epat-protocol PUBLIC cxx_std_17)

if(MSVC)
  target_compile_options(epat-protocol PUBLIC "/utf-8")
endif()

# 测试
enable_testing()
add_subdirectory("test")
