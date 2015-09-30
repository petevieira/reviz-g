cmake_minimum_required(VERSION 2.8.3)

#-----------------------------------------------
#                FIND PACKAGES
#-----------------------------------------------

include_directories(./)

# OpenSceneGraph Urdf Library
file(GLOB srcs ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.h)
add_library(osgUrdf SHARED ${srcs})
target_link_libraries(osgUrdf ${OPENSCENEGRAPH_LIBRARIES} ${URDFDOM_LIBRARIES})
