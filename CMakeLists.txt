cmake_minimum_required(VERSION 3.0)
project(sfm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# libraries to link in the end
set(LINK_LIBRARIES "")

########### options ###############
SET(USE_GUI TRUE CACHE BOOL "Build with CLI and GUI?")
########### END options ###########


########### OpenCV ################
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
list(APPEND LINK_LIBRARIES ${OpenCV_LIBS})
########### END OpenCV ############


########### Qt 5 ##################
IF(USE_GUI)
  ADD_DEFINITIONS("-DUSE_GUI")

  find_package(Qt5Widgets REQUIRED)
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
  list(APPEND LINK_LIBRARIES Qt5::Widgets)

  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
ENDIF(USE_GUI)
########### END Qt 5 ##############

########### sources ###############
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(sfm ${SOURCE_FILES})
########### END sources ###########


########### headers ###############
file(GLOB_RECURSE HEADERS "src/*.h")

set (INCLUDE_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})
########### END headers ###########


########### link libraries ########
target_link_libraries (sfm ${LINK_LIBRARIES})
########### END link libraries ####
