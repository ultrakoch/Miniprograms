CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
include(FindPkgConfig)

PROJECT(rgb_cam)

SET(IMAGER_VERSION_MAJOR 0)
SET(IMAGER_VERSION_MINOR 1)

FIND_PACKAGE(OpenCV REQUIRED)

SET(CMAKE_CXX_FLAGS "-Wno-write-strings -fpermissive")

##### 
INCLUDE_DIRECTORIES(../.. 
                    .. 
                    ${PROJECT_SOURCE_DIR}/../include 
                    ${PROJECT_SOURCE_DIR}/../wrapper
                    /usr/include/opencv2)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../lib
                  $ENV{OPENCV_ROOT}
                  )

## Executables
ADD_EXECUTABLE( rgb_cam
                starter_video.cpp
)
TARGET_LINK_LIBRARIES(rgb_cam ${OpenCV_LIBS})

