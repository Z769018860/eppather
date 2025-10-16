# CMakeList.txt: test项目文件，在此处包括源代码并定义
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.12)

project("test" VERSION 0.0.1)

function(add_test_directory DIR_NAME LIB_LIST INCLUDE_DIR)
  file(GLOB TEST_SRCS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${DIR_NAME}/*.cpp"
  )

  foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    set(testName "epat-${testName}")
    add_executable(${testName} ${testSrc})
    target_include_directories(${testName} PRIVATE INCLUDE_DIR)
    target_link_libraries(${testName} PRIVATE ${LIB_LIST})
    target_compile_features(${testName} PRIVATE cxx_std_17)
    add_compile_definitions(TEST_SRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/${DIR_NAME}")
    add_test(NAME ${testName} COMMAND ${testName})
    remove_definitions(-DTEST_SRC_DIR)

    # XXX: 仅在用到Z3库时才复制到目标目录
    if(CMAKE_SYSTEM_NAME MATCHES "[Ww]indows")
      add_custom_command(TARGET ${testName} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${Z3_LIB_DIR}/libz3.dll"
        $<TARGET_FILE_DIR:${testName}>
      )
    endif()
  endforeach()
endfunction()

set(EPAT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../libepat++/include)
set(EPAT_PROTOCOL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../epat-protocol/include)

add_test_directory(
  "basic_test" # 基础测试
  "libepat++"
  "${EPAT_INCLUDE_DIR};${EPAT_PROTOCOL_INCLUDE_DIR};${Z3_INCLUDE_DIR}"
)

add_test_directory(
  "reg_test" # 回归测试
  "libepat++"
  "${EPAT_INCLUDE_DIR};${EPAT_PROTOCOL_INCLUDE_DIR};${Z3_INCLUDE_DIR}"
)

# add_test_directory(
# "basic_test"
# "libepat++"
# ""
# )

# add_test_directory(
# "test_case"
# "libepat++"
# "${CMAKE_CURRENT_SOURCE_DIR}/test_case"
# )

# add_test_directory(
# "unit_test"
# "libepat++"
# ""
# )

# add_test_directory(
# "z3_test"
# "libepat++"
# ""
# )
