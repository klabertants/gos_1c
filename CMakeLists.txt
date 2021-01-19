cmake_minimum_required(VERSION 3.17)
project(GOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(GOS main.cpp FileDecomposer.h FileDecomposer.cpp SuffixArray.h SuffixArray.cpp Finder.h Finder.cpp)