cmake_minimum_required(VERSION 3.30)

project(foo VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXCompilerFlag)

macro(add_cxx_compiler_flag flag)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
endmacro()

macro(try_cxx_compiler_flag flag var)
  check_cxx_compiler_flag(${flag} ${var})
  if(${var})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
  endif()
endmacro()

# Debugging flags.
if(CMAKE_BUILD_TYPE MATCHES Debug)
  try_cxx_compiler_flag("-Og" CXX_HAS_OPTDEBUG_FLAG)
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(benchmarks EXCLUDE_FROM_ALL)