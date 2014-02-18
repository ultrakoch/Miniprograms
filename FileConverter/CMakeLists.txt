cmake_minimum_required (VERSION 2.6)
include(FindPkgConfig)

############################
# General project settings #
############################

PROJECT(hokuyoEW)
SET(APPLICATIONS_VERSION_MAJOR 0)
SET(APPLICATIONS_VERSION_MINOR 1)

#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
PKG_CHECK_MODULES(XML libxml++-2.6)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include 
  /usr/local/include/
  )

LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/lib
  )




ADD_EXECUTABLE(FileConverter src/FileConverter.cpp)

#TARGET_LINK_LIBRARIES(FileConverter ${DEVICELIBS} ${URGLIBS} ${GRAPHICLIBS} ${CORELIBS} ${VISIONLIBS} )



