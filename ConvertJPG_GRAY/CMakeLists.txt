CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
include(FindPkgConfig)

PROJECT(IMAGERSHOW)
SET(IMAGER_VERSION_MAJOR 0)
SET(IMAGER_VERSION_MINOR 1)

FIND_PACKAGE(OpenCV REQUIRED)

SET(CMAKE_CXX_FLAGS "-Wno-write-strings -fpermissive")

##### Files for Thermocamera
INCLUDE_DIRECTORIES(../.. .. ${PROJECT_SOURCE_DIR}/../include ${PROJECT_SOURCE_DIR}/../wrapper)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib)





## Executables
ADD_EXECUTABLE(convertGray
            convertGray.cpp
)

TARGET_LINK_LIBRARIES(convertGray ${OpenCV_LIBS})
