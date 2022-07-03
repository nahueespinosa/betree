cmake_minimum_required(VERSION 3.16)

project(betree VERSION 1.0)

include(FetchContent)

add_library(betree INTERFACE)
target_include_directories(betree INTERFACE include)
target_compile_features(betree INTERFACE cxx_std_20)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)
