cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(bench main.cpp)

target_link_libraries(bench Threads::Threads benchmark)

set_target_properties(bench PROPERTIES CXX_STANDARD 14)
