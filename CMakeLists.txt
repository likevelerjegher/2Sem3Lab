cmake_minimum_required(VERSION 3.24)
project(3Lab C)

set(CMAKE_C_STANDARD 11)

add_executable(3Lab main.c menuFunctions.c structures.h fileFunctions.c fileFunctions.h photoFeatures.c photoFeatures.h)
