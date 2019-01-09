cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(bench main.cpp binary_tree.cpp)

find_package(Boost COMPONENTS system thread program_options REQUIRED)

target_link_libraries(bench Threads::Threads benchmark ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY})

set_target_properties(bench PROPERTIES CXX_STANDARD 14)
