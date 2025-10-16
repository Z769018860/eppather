# CMakeList.txt: test项目文件，在此处包括源代码并定义
# 并包含子项目。
#
if (enable_epat_protocol_testing EQUAL 0)
  return ()
endif()

cmake_minimum_required (VERSION 3.8)

project ("test" VERSION 0.0.1)

# 遍历文件夹
file (GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "basic_test/*.cpp")
foreach (testSrc ${TEST_SRCS})
	get_filename_component (testName ${testSrc} NAME_WE)
  set (testName "eapt-protocol-${testName}")
	add_executable (${testName} ${testSrc})
  target_include_directories (${testName} PRIVATE "include")
  target_link_libraries (${testName} epat-protocol)
  target_compile_features(${testName} PRIVATE cxx_std_17)
  if (MSVC)
    target_compile_options (${testName} PRIVATE "/utf-8")
  endif()
	#link to Boost libraries AND your targets and dependencies
    #target_link_libraries (${testName} Boost::unit_test_framework )
    add_test(NAME ${testName}
        #WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/testBin
        #COMMAND ${CMAKE_BINARY_DIR}/test/testBin/${testName}
        COMMAND ${testName}
    )
endforeach(testSrc)
