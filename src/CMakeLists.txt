set(LIB_SOURCES
  #algo.cpp
  par_algo.cpp
  seq_algo.cpp
)

set(BIN_SOURCES
  ${LIB_SOURCES}
  main.cpp
)

add_executable(algo.exe ${BIN_SOURCES})
install(TARGETS algo.exe DESTINATION bin)

# The static library is needed for building tests and benchmarks.
add_library(algo_lib STATIC EXCLUDE_FROM_ALL ${LIB_SOURCES})