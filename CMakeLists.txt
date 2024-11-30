cmake_minimum_required(VERSION 3.15)
project(ParallelPractice)
include (FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(PARLAY_NUM_THREADS 4)

FetchContent_Declare(parlaylib
  GIT_REPOSITORY  https://github.com/cmuparlay/parlaylib.git
  GIT_TAG         master
)
FetchContent_GetProperties(parlaylib)
if(NOT parlaylib_POPULATED)
  FetchContent_Populate(parlaylib)  
  add_subdirectory(${parlaylib_SOURCE_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(
  googletest
)

FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.1.zip
)
FetchContent_MakeAvailable(
  benchmark
)

add_executable(benchmarks
  benchmarks/bench.cpp
  src/algo.h
  src/par_algo.cpp
  src/seq_algo.cpp
)

add_executable(main
  src/main.cpp
  src/algo.h
  src/par_algo.cpp
  src/seq_algo.cpp
)

target_link_libraries(benchmarks PRIVATE parlay benchmark::benchmark)
target_link_libraries(main PRIVATE parlay)