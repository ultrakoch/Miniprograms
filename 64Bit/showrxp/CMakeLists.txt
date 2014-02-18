cmake_minimum_required (VERSION 2.6.1)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/CMakeModules" ${CMAKE_MODULE_PATH})
project (Slam6D)


#include_directories(OPENGL_INCLUDE_DIR)
set(Boost_USE_STATIC_LIBS FALSE)

SET(Boost_ADDITIONAL_VERSIONS "1.42" "1.42.0" "1.44" "1.44.0" "1.45.0" "1.45" "1.47.0" "1.47")
find_package( Boost COMPONENTS serialization graph regex REQUIRED)

if(Boost_FOUND)
  link_directories(${BOOST_LIBRARY_DIRS})
  include_directories(${Boost_INCLUDE_DIRS})
  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
endif()

#################################################
# Declare Options and modify build accordingly ##
#################################################
## SHOW
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
MESSAGE(STATUS "With show")

## Octree
MESSAGE(STATUS "Using octree display")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_GL_POINTS")

## RivLib
MESSAGE(STATUS "Compiling a scan IO for RXP files")
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)
link_directories(${CMAKE_SOURCE_DIR}/3rdparty)
SET(RIEGL_DIR ${CMAKE_SOURCE_DIR}/3rdparty/riegl/)
SET(RIVLIB ${RIEGL_DIR}libscanlib-mt-s.a ${RIEGL_DIR}libctrllib-mt-s.a ${RIEGL_DIR}libboost_system-mt-s-1_43_0-vns.a pthread)
FIND_PACKAGE(LibXml2 )

## Multiple Cores 
INCLUDE(CountProcessors)
SET(NUMBER_OF_CPUS "${PROCESSOR_COUNT}" CACHE STRING "The number of processors to use (default: ${PROCESSOR_COUNT})" )
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAX_OPENMP_NUM_THREADS=1 -DOPENMP_NUM_THREADS=1")
SET(ADDITIONAL_CFLAGS "-O3 -msse3 -Wall -finline-functions -Wno-write-strings -Wno-char-subscripts -Wno-unused-result" CACHE STRING"Additional flags given to the compiler (-O3 -Wall -finline-functions -Wno-write-strings -Wno-unused-result)" )
# Add include path for OpenGL without GL/-prefix 
# to avoid the include incompatibility between MACOS 
# and linux
FIND_PATH(OPENGL_INC gl.h /usr/include/GL)
include_directories(${OPENGL_INC})

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS}")

# Hide CMake variables
SET (CMAKE_INSTALL_PREFIX "/usr/local" CACHE INTERNAL "" FORCE)
SET (CMAKE_BUILD_TYPE "" CACHE INTERNAL "" FORCE)

# Set output directories for libraries and executables
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/obj )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

# Set include and link dirs ... 
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glui)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/ann_1.1.1_modified/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/ann_1.1.1_modified/src)
link_directories(${CMAKE_SOURCE_DIR}/obj)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(3rdparty)
 
SET(SHOW_LIBS ${OPENGL_LIBRARIES} glui scanlib ANN)
SET(SHOW_LIBS ${SHOW_LIBS} newmat dl ${GLUT_LIBRARIES}) 
  
SET(SHOW_SRCS src/NurbsPath.cc  src/PathGraph.cc src/vertexarray.cc  src/viewcull.cc src/colormanager.cc src/compacttree.cc src/scancolormanager.cc src/display.cc)

add_executable(show src/show.cc ${SHOW_SRCS}) 
target_link_libraries(show ${SHOW_LIBS} )

MESSAGE (STATUS "Build environment is set up!")

