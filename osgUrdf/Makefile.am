
lib_LTLIBRARIES =		libosgUrdf.la

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED

AM_CPPFLAGS = 		-Werror \
									-I../
									-I../osgReviz \
									-I/usr/include/osg \
									-I/usr/include/osgViewer \
									-I/usr/include/osgManipulator \
									-I/usr/include/osgGA

libosgUrdf_la_LIBFLAGS = -shared -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x -export-dynamic -soname

libosgUrdf_la_LIBADD = \
							../osgReviz/libosgReviz.la \
							$(OSG_LIBS) \
							$(URDFDOM_LIBS)

libosgUrdf_la_SOURCES = \
													src/osgUrdf.cpp