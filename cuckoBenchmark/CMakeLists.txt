project(BloomFilterBench)

set(CMAKE_BUILD_TYPE Release)

add_executable(bench bench.cpp)

include_directories(../contrib/benchmark/include)

include_directories(../cuckoofilter_mod/src)


target_link_libraries(bench benchmark::benchmark)
target_link_libraries(bench CuckooFiltSupport)
