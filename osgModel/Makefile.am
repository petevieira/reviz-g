
lib_LTLIBRARIES =		libosgModel.la

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED

AM_CPPFLAGS = 		-Werror \
									-I$(top_srcdir)/osgReviz \
									-I/usr/include/osg \
									-I/usr/include/osgViewer \
									-I/usr/include/osgManipulator \
									-I/usr/include/osgGA

libosgModel_la_LIBFLAGS = -shared -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x -export-dynamic -soname

libosgModel_la_LIBADD = \
							$(top_srcdir)/osgReviz/libosgReviz.la \
							$(OSG_LIBS)

libosgModel_la_SOURCES = \
													src/osgModel.cpp