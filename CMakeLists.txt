cmake_minimum_required(VERSION 3.21)
project(ex4 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex4 main.c LinkedList.c LinkedList.h Hist.h Hist.c TestHist.c TestHist.h)
