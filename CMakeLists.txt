cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

# Project name
project(EGL)

# Locate additionnal modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find Glew
find_package(GLEW REQUIRED)

# Find SFML
find_package(SFML 2 REQUIRED system window graphics)


# Set the compiler flags to support c++0x
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra" CACHE STRING "Compiler flags" FORCE)
add_definitions(-DGLM_FORCE_RADIANS)

# Includes paths
include_directories(
    include
    ${SFML_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

link_directories(
)

# Sources files
file(
    GLOB_RECURSE
    SOURCES
    src/*
)

# Add build of glEngine library
add_library(EGL SHARED ${SOURCES})
target_link_libraries(
	EGL
	${SFML_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
)

file(GLOB EXAMPLES ${PROJECT_SOURCE_DIR}/examples/*)
foreach(EXAMPLE ${EXAMPLES})
	if(IS_DIRECTORY ${EXAMPLE})
		file(
    		GLOB_RECURSE
    		EXAMPLE_SOURCES
    		${EXAMPLE}/src/*
    	)
    	GET_FILENAME_COMPONENT(EXAMPLE_NAME ${EXAMPLE} NAME)
    	add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
		target_link_libraries(${EXAMPLE_NAME} EGL)
	endif()
endforeach()