cmake_minimum_required(VERSION 3.24)
project(modeling_queue)

set(CMAKE_CXX_STANDARD 17)

add_executable(modeling_queue main.cpp src/Server.cpp include/Server.hpp src/LimitedQueue.cpp include/LimitedQueue.hpp include/Request.hpp src/InfinityQueue.cpp include/InfinityQueue.hpp)
