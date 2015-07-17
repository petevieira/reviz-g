cmake_minimum_required(VERSION 2.8.3)

#-----------------------------------------------
#                FIND PACKAGES
#-----------------------------------------------

include_directories(./)

# OpenSceneGraph Nodes Library
file(GLOB srcs ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/*.h)
add_library(osgReviz SHARED ${srcs})
target_link_libraries(osgReviz ${OPENSCENEGRAPH_LIBRARIES} ${QT_LIBRARIES})
