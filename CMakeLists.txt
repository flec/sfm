# Copyright 2009 Marco Fuellemann & Janosch Rohdewald.  All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

cmake_minimum_required(VERSION 3.0)
project(sfm)

########### options ###############
SET(USE_QT TRUE CACHE BOOL "Build with CLI or QT GUI?")
SET(USE_CUDA FALSE CACHE BOOL "Build with CUDA?")
########### END options ###########

# Set a default build type for single-configuration
# CMake generators if no build type is set.
IF (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

# Select flags.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -std=c++11")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")

# include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

########### OpenMP ################
find_package(OpenMP)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
########### END OpenMP ############

########### OpenCV ################
set(OpenCV_STATIC OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
list(APPEND LINK_LIBRARIES ${OpenCV_LIBS})

# CUDA for feature detection?
IF (USE_CUDA)
  add_definitions(-DUSE_CUDA)
ENDIF (USE_CUDA)
########### END OpenCV ############


########### Qt 5 ##################
IF (USE_QT)
  ADD_DEFINITIONS("-DUSE_QT")

  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5Xml REQUIRED)
  find_package(Qt5OpenGL REQUIRED)

  include_directories(${Qt5Widgets_INCLUDE_DIRS}
      ${Qt5Xml_INCLUDE_DIRS}
      ${Qt5OpenGL_INCLUDE_DIRS}
  )

  list(APPEND LINK_LIBRARIES Qt5::Widgets Qt5::Xml Qt5::OpenGL)

  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  include_directories(src/ui/mainwindow
      src/ui/widgets)

  # Find QGLViewer and OpenGL libraries
  find_package(OpenGL REQUIRED)
  find_library(QGLVIEWER_LIBRARY
      NAMES qglviewer-qt5 qglviewer QGLViewer QGLViewer2)
  list(APPEND LINK_LIBRARIES ${QGLVIEWER_LIBRARY} ${OPENGL_LIBRARIES})
ENDIF (USE_QT)
########### END Qt 5 ##############

########### vendors ###############
link_libraries(colamd)
add_subdirectory(vendor/SSBA-4.0)
link_directories(vendor/SSBA-4.0)
link_libraries(V3D)
include_directories(vendor vendor/SSBA-4.0)
add_definitions(-DV3DLIB_ENABLE_SUITESPARSE)
########### END vendors ###########

########### sources ###############
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(sfm ${SOURCE_FILES})
########### END sources ###########


########### headers ###############
include_directories(src)
########### END headers ###########


########### link libraries ########
target_link_libraries(sfm ${LINK_LIBRARIES})
########### END link libraries ####
