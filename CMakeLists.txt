cmake_minimum_required(VERSION 3.24)
project(cpp_seminars)

set(CMAKE_CXX_STANDARD 23)

# seminar 13
add_executable(sem13-intro seminar13/part1/exceptions.cpp)
add_executable(sem13-noexcept seminar13/part1/noexcept.cpp)
add_executable(sem13-vector-noexcept seminar13/part1/myvector.cpp)