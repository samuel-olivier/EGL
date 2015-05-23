cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

# Project name
project (EGL)

# Find OpenGL
find_package (OpenGL)

# Set the compiler flags to support c++0x
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra" CACHE STRING "Compiler flags" FORCE)

# Includes paths
include_directories (
    includes
)

link_directories (
)

# Sources files
file (
    GLOB_RECURSE
    SOURCES
    sources/*
)

# Add build of glEngine library
add_library(EGL SHARED ${SOURCES})