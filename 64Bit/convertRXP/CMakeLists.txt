cmake_minimum_required (VERSION 2.6.1)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/3rdparty/CMakeModules" ${CMAKE_MODULE_PATH})

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

## Multiple Cores 
INCLUDE(CountProcessors)
SET(NUMBER_OF_CPUS "${PROCESSOR_COUNT}" CACHE STRING "The number of processors to use (default: ${PROCESSOR_COUNT})" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAX_OPENMP_NUM_THREADS=1 -DOPENMP_NUM_THREADS=1")
SET(ADDITIONAL_CFLAGS "-O3 -msse3 -Wall -finline-functions -Wno-write-strings -Wno-char-subscripts -Wno-unused-result" CACHE STRING"Additional flags given to the compiler (-O3 -Wall -finline-functions -Wno-write-strings -Wno-unused-result)" )


# OPEN
FIND_PACKAGE(OpenMP)
IF(OPENMP_FOUND)
  MESSAGE(STATUS "With OpenMP ")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAX_OPENMP_NUM_THREADS=${PROCESSOR_COUNT} -DOPENMP_NUM_THREADS=${NUMBER_OF_CPUS} ${OpenMP_CXX_FLAGS} -DOPENMP")
ELSE(OPENMP_FOUND)
  MESSAGE(STATUS "Without OpenMP")
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMAX_OPENMP_NUM_THREADS=1 -DOPENMP_NUM_THREADS=1")
ENDIF(OPENMP_FOUND)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS}")

## RivLib
MESSAGE(STATUS "Compiling a scan IO for RXP files")
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)
link_directories(${CMAKE_SOURCE_DIR}/3rdparty)
SET(RIEGL_DIR ${CMAKE_SOURCE_DIR}/3rdparty/riegl/)
SET(RIVLIB ${RIEGL_DIR}libscanlib-mt-s.a ${RIEGL_DIR}libctrllib-mt-s.a ${RIEGL_DIR}libboost_system-mt-s-1_43_0-vns.a pthread)
FIND_PACKAGE(LibXml2 )

# Add include path for OpenGL without GL/-prefix 
# to avoid the include incompatibility between MACOS 
# and linux
FIND_PATH(OPENGL_INC gl.h /usr/include/GL)
include_directories(${OPENGL_INC})

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Set output directories for libraries and executables
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/obj )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

# Set include and link dirs ... 
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/)
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glui)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/ann_1.1.1_modified/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/ann_1.1.1_modified/src)

link_directories(${CMAKE_SOURCE_DIR}/obj)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(3rdparty)

set(CMAKE_CXX_FLAGS "-fopenmp")

link_directories(
	${PROJECT_SOURCE_DIR}/lib
	)

include_directories(
	$ENV{OBVIOUSLY_ROOT}
	${PROJECT_SOURCE_DIR}/include
	)


add_executable(convertRXP src/convertRXP.cpp src/read_rxp.cpp)
target_link_libraries(convertRXP scanlib obcore ANN dl) #sparse_s newmat_s glui ANN) 
