project(AMQstruct)

set(CMAKE_BUILD_TYPE Release)


add_subdirectory(contrib/benchmark)

add_subdirectory(Bloom-Filter)

add_subdirectory(contrib/smhasher/src)

add_subdirectory(cuckoBenchmark)

add_subdirectory(cuckoofilter_mod)