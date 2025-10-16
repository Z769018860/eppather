# CMakeList.txt: test项目文件，在此处包括源代码并定义
# 并包含子项目。
#
if(enable_epat_protocol_testing EQUAL 0)
  return()
endif()

cmake_minimum_required(VERSION 3.12)

project("test" VERSION 0.0.1)

# 文件列表
file(GLOB BASIC_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "basic_test/*.cpp")

# file(GLOB ADVANCED_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "advanced_test/*.cpp")
foreach(testSrc ${BASIC_TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  set(testName "epat-protocol-${testName}")
  add_executable(${testName} ${testSrc})
  target_include_directories(${testName} PRIVATE "include")
  target_link_libraries(${testName} epat-protocol)
  target_compile_features(${testName} PRIVATE cxx_std_17)

  if(MSVC)
    target_compile_options(${testName} PRIVATE "/utf-8")
  endif()

  add_test(NAME ${testName}
    COMMAND ${testName} ${CMAKE_CURRENT_SOURCE_DIR}/leetcode ${CMAKE_CURRENT_SOURCE_DIR}/1.out
  )
endforeach(testSrc)

# foreach(testSrc ${ADVANCED_TEST_SRCS})
# get_filename_component(testName ${testSrc} NAME_WE)
# set(testName " epat-protocol-${testName} ")
# add_executable(${testName} ${testSrc})
# target_include_directories(${testName} PRIVATE " include ")
# target_link_libraries(${testName} epat-protocol)
# target_compile_features(${testName} PRIVATE cxx_std_17)

# if(MSVC)
# target_compile_options(${testName} PRIVATE " /utf-8 ")
# endif()

# add_test(NAME ${testName}
# COMMAND " ${testName} ${CMAKE_SOURCE_DIR}/leetcode ${CMAKE_SOURCE_DIR}/1.out "
# )
# endforeach(testSrc)