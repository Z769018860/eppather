# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.15)

project (ANTLR4_RUNTIME LANGUAGES CXX)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/atn
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dfa
  ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
  ${CMAKE_CURRENT_SOURCE_DIR}/src/misc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/support
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/pattern
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/xpath
)


file(GLOB libantlrcpp_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/atn/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/dfa/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/internal/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/misc/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/support/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/tree/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/tree/pattern/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/tree/xpath/*.cpp"
)

add_library (antlr4-runtime STATIC ${libantlrcpp_SRC})
target_include_directories (antlr4-runtime PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/atn
  ${CMAKE_CURRENT_SOURCE_DIR}/src/dfa
  ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
  ${CMAKE_CURRENT_SOURCE_DIR}/src/misc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/support
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/pattern
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree/xpath
)

if (CMAKE_HOST_UNIX)
  # Make sure to link against threads (pthreads) library in order to be able to
  # make use of std::call_once in the code without producing runtime errors
  # (see also https://github.com/antlr/antlr4/issues/3708 and/or https://stackoverflow.com/q/51584960).
  find_package(Threads REQUIRED)
  target_link_libraries(antlr4-runtime Threads::Threads)
endif()

IF(TRACE_ATN)
    ADD_DEFINITIONS(-DTRACE_ATN_SIM=1)
ENDIF(TRACE_ATN)

if(APPLE)
  target_link_libraries(antlr4-runtime ${COREFOUNDATION_LIBRARY})
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(disabled_compile_warnings "/wd4251")
else()
  set(disabled_compile_warnings "-Wno-overloaded-virtual")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-dollar-in-identifier-extension -Wno-four-char-constants")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-multichar")
endif()

if (WIN32)
  target_compile_definitions(antlr4-runtime PUBLIC ANTLR4CPP_STATIC)
endif()

target_compile_features(antlr4-runtime PRIVATE cxx_std_17)