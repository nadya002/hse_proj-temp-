project(BloomFilter)

set(CMAKE_BUILD_TYPE Release)

set(MAIN_PROJECT_SRC_LIST main.cpp)

add_library(BloomFilt Bloom_filt.h)

add_executable(main main.cpp)

add_subdirectory(benchmark)

include_directories(../contrib/smhasher/src)
include_directories(.)

target_link_libraries(BloomFilt SMHasherSupport)

target_link_libraries(main BloomFilt)
