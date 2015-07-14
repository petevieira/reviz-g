
lib_LTLIBRARIES =		libosgGolems.la

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED

AM_CPPFLAGS = 		-Werror \
									-I/usr/include/osg \
									-I/usr/include/osgViewer \
									-I/usr/include/osgManipulator \
									-I/usr/include/osgGA \
									-I/usr/include/osgQt \
									-I/usr/include/qt4 \
									-I/usr/include/qt4/QtXml \
									-I/usr/include/qt4/QtOpenGL \
									-I/usr/include/qt4/QtCore

libosgGolems_la_LIBFLAGS = -shared -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x -export-dynamic -soname

libosgGolems_la_SOURCES = \
												 	src/ViewerWidget.cpp \
													src/Grid.cpp \
													src/osgUtils.cpp \
													src/GripCameraManipulator.cpp