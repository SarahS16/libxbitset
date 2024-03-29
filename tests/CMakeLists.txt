cmake_minimum_required(VERSION 3.15)

project(unit_test VERSION 0.0.1 LANGUAGES CXX)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # require at least gcc 11
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
    message(FATAL_ERROR "GCC version must be at least 11!")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # require at least clang 13
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "Clang version must be at least 13!")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  # require at least clang 13
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "Clang version must be at least 13!")
  endif()
else()
  message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC, detected ${CMAKE_CXX_COMPILER_ID}.")
endif()

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_BUILD_TYPE "Debug")

find_package(ut REQUIRED CONFIG)

add_executable(${PROJECT_NAME}
  main.test.cpp
  bitset.test.cpp
  bitreset.test.cpp
  bitflip.test.cpp
  bitinsert.test.cpp
  bitextract.test.cpp
  bittest.test.cpp
  classbitset.test.cpp
  bitupdate.test.cpp
  bitsave.test.cpp
  bitmanip.test.cpp
  originmask.test.cpp
  bitmask.test.cpp
  bitrange.test.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC . ../include)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra
  -Wno-unused-function -Wconversion -Wno-psabi)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::ut
)
