cmake_minimum_required(VERSION 3.12)
project(bugs LANGUAGES CXX)  

file(GLOB sources "*.cpp")
add_library(bugs STATIC ${sources})

# target_compile_features(simple PRIVATE cxx_std_20)