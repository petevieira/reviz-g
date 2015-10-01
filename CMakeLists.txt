cmake_minimum_required(VERSION 2.8.3)
project(reviz)

set(CMAKE_VERBOSE_MAKEFILE on)

# Define some colors for fun output
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(Red         "${Esc}[1;31m")
  set(Yellow      "${Esc}[1;33m")
endif()

if(APPLE)
    set(X11_THREADS_LIB "X11")
    # set X11 include path for Mac OS X 
    include_directories(/opt/X11/include)
    link_directories(/opt/X11/lib)
else(APPLE)
    # linux uses rt for XInitThreads()
    set(X11_THREADS_LIB "rt")
endif()

#-----------------------------------------------
#                COMPILE SETTINGS
#-----------------------------------------------
set(CMAKE_BUILD_TYPE "Release")
list(APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib64)

# Define preprocessor macro for Debug printing in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "\nBuilding in \"Debug\" mode.\n-- CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "\nBuilding in \"Release\" mode.\n-- CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
else()
endif()

#-----------------------------------------------
#               UNINSTALL TARGET
#-----------------------------------------------
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

#-----------------------------------------------
#                FIND PACKAGES
#-----------------------------------------------
# Find QT
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL QtXml REQUIRED) # Qt3Support
add_definitions(${QT_DEFINITIONS})
include(${QT_USE_FILE})

set(OSG_LIBRARY_INSTALL "FALSE")
if(${OSG_LIBRARY_INSTALL})
    # Find OpenSceneGraph (as installed library 3.0.1, for ubuntu 14.04)
    # NOTE: The osg deb for 14.04 is v3.2.0, which is broken (renders weird) 
    #       * to get OSG 3.0.1 to build you may need to disable ffmpeg:
    #       * run "ccmake ..", and delete entry "FFMPEG_LIBAVUTIL_INCLUDE_DIRS" 
    find_library(OpenSceneGraph REQUIRED
        COMPONENTS osg osgViewer osgManipulator osgGA osgDB osgQt osgUtil)
    set(OSG_LIBRARY_PATH "/usr/local/lib64") # may have to be customized
    if(APPLE)
        set(LIB_SUFFIX "dylib")
    else(APPLE)
        set(LIB_SUFFIX "so")
    endif()
    set(OPENSCENEGRAPH_LIBRARIES ${OSG_LIBRARY_PATH}/libosg.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosgViewer.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosgManipulator.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosgGA.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosgDB.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libOpenThreads.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosgQt.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosg.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libosg.${LIB_SUFFIX}
                                 ${OSG_LIBRARY_PATH}/libOpenThreads.${LIB_SUFFIX})
else(${OSG_LIBRARY_INSTALL})
    # Find OpenSceneGraph (cmake package)
    message(STATUS "Searching for OpenSceneGraph")
    set(OSG_LIBRARY_PATH "/usr/local/lib64") # may have to be customized
    find_package(OpenSceneGraph 3.0 REQUIRED
        COMPONENTS osg osgViewer osgManipulator osgGA osgDB)
    find_package(OpenSceneGraph 3.0 REQUIRED COMPONENTS osgQt)
    if(${OSG_FOUND})
        message(STATUS "Looking for OpenSceneGraph - Found")
    else()
        message(SEND_ERROR "Looking for OpenSceneGraph - NOT Found. Please install libopenscenegraph-dev")
    endif()
    include_directories(${OpenSceneGraph_INCLUDE_DIRS})
    add_definitions(${OpenSourceGraph_DEFINITIONS})
    set(OPENSCENEGRAPH_LIBRARIES ${OPENSCENEGRAPH_LIBRARIES} osgQt)
endif()

message(STATUS "\nIncludes: ${OpenSceneGraph_INCLUDE_DIRS}")

# Find urdfdom
find_package(urdfdom QUIET)
if(urdfdom_FOUND)
    message(STATUS "Looking for urdfdom - Found")
    set(URDFDOM_LIBRARIES urdfdom_model
                          urdfdom_model_state
                          urdfdom_world)
else()
    message(SEND_ERROR "Looking for urdfdom - NOT Found, please install liburdfdom-dev")
endif()

# Find Eigen3
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIR})

#-----------------------------------------------
#      INCLUDES & SUBDIRECTORY LIBRARIRES
#-----------------------------------------------
include_directories(include)

# Add QT Widgets library
add_subdirectory(qtWidgets)
include_directories(qtWidgets)

# Add OpenSceneGraph Nodes library
add_subdirectory(osgReviz)
include_directories(osgReviz)
include_directories(./)

# Add OpenSceneGraph Urdf library
add_subdirectory(osgUrdf)
include_directories(osgUrdf)

# Set project libraries variable
set(project_libs qtWidgets
                 osgReviz
                 osgUrdf)

# Add Main Window library
QT4_WRAP_CPP(GUI_MOC_HEADERS ${PROJECT_SOURCE_DIR}/include/MainWindow.h)
file(GLOB GUI_SRC include/*.h src/*.cpp)
add_library(mainWindow ${GUI_MOC_HEADERS} ${GUI_SRC})
target_link_libraries(mainWindow ${project_libs} ${X11_THREADS_LIB})

# Set project libraries variable
set(project_libs ${project_libs} mainWindow)

#-----------------------------------------------
#                BUILD REVIZ
#-----------------------------------------------
add_executable(reviz ${PROJECT_SOURCE_DIR}/src/reviz.cpp)
target_link_libraries(reviz ${project_libs} ${URDFDOM_LIBRARIES} ${QT_LIBRARIES} ${OPENSCENEGRAPH_LIBRARIES})

FILE(GLOB reviz-srcs osgReviz/*.h osgReviz/src/*.cpp qtWidgets/*.h qtWidgets/src/*.cpp osgUrdf/*.h osgUrdf/src*.cpp)
add_library(reviz-core SHARED ${reviz-srcs})
target_link_libraries(reviz-core ${project_libs} ${QT_LIBRARIES} ${OPENSCENEGRAPH_LIBRARIES} ${URDFDOM_LIBRARIES})

# add_library(reviz_wrap_test STATIC ${PROJECT_SOURCE_DIR}/src/reviz_wrap_test.cpp)
# target_link_libraries(reviz_wrap_test ${project_libs} ${QT_LIBRARIES} ${DART_LIBRARIES} ${OPENSCENEGRAPH_LIBRARIES})
# MESSAGE("----------> ALL LIBRARIES: reviz_wrap_test ${project_libs} ${QT_LIBRARIES} ${DART_LIBRARIES} ${OPENSCENEGRAPH_LIBRARIES}")
#-----------------------------------------------
#                BUILD TESTS
#-----------------------------------------------
# Get test files
file(GLOB unit_tests_source "test/*.cpp")
LIST(SORT unit_tests_source)

# Build test programs
message(STATUS "\n-- UNIT TEST: ")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
foreach(utest_src_file ${unit_tests_source})
    get_filename_component(test_base ${utest_src_file} NAME_WE)
    message(STATUS "Adding test ${test_base}")
    add_executable(${test_base} ${utest_src_file})
    target_link_libraries(${test_base} ${project_libs} ${OPENSCENEGRAPH_LIBRARIES} ${QT_LIBRARIES} ${URDFDOM_LIBRARIES})
    add_test(${test_base} ${EXECUTABLE_OUTPUT_PATH}/${test_base})
    add_custom_target(${test_base}.run ${test_base} ${ARGN})
    add_dependencies(check ${test_base})
endforeach(utest_src_file)

#-----------------------------------------------
#                 INSTALLATION
#-----------------------------------------------
# Install reviz
# INSTALL(PROGRAMS build/reviz
#         DESTINATION /usr/local/bin/)

# # Install library of reviz's libraries
# INSTALL(TARGETS reviz-core
#         DESTINATION /usr/local/lib/)

# # Install header files by namespace and directory
# FILE(GLOB osgDartHeaders "osgDart/*.h")
# INSTALL(FILES ${osgDartHeaders}
#         DESTINATION /usr/local/include/reviz/osgDart)

# FILE(GLOB osgRevizHeaders "osgReviz/*.h")
# INSTALL(FILES ${osgRevizHeaders}
#         DESTINATION /usr/local/include/reviz/osgReviz)

# FILE(GLOB qtWidgetsHeaders "qtWidgets/*.h")
# INSTALL(FILES ${qtWidgetsHeaders}
#         DESTINATION /usr/local/include/reviz/qtWidgets)

# FILE(GLOB mainHeaders "include/*.h")
# INSTALL(FILES ${mainHeaders}
#         DESTINATION /usr/local/include/reviz/include)

# # Install cmake find file for reviz
# INSTALL(FILES cmake/FindREVIZ.cmake
#         DESTINATION ${CMAKE_ROOT}/Modules)

# # Install desktop file to call reviz from desktop
# INSTALL(FILES "doc/reviz.desktop"
#         DESTINATION /usr/share/applications)

# INSTALL(FILES "src/icons/reviz-icon.png"
#         DESTINATION /usr/share/icons/)
