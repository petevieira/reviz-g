
lib_LIBRARIES =		libosgUrdf.a



AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED

AM_CPPFLAGS = 		-Werror \
									-I../
									-I../osgReviz \
									-I../osgUrdf \
									-I../include \
									-I/usr/include/osg \
									-I/usr/include/osgViewer \
									-I/usr/include/osgManipulator \
									-I/usr/include/osgGA

libosgUrdf_a_LDADD = \
							libmainwindow.a \
							../qtWidgets/libqtWidgets.a \
							../osgReviz/libosgReviz.a \
							../osgUrdf/libosgUrdf.a \
							$(GUI_LIBS) \
							$(OSG_LIBS) \
							$(URDFDOM_LIBS)

libosgUrdf_a_LIBFLAGS = \
												-L/usr/lib/x86_64-linux-gnu/ \
												-fPIC \
												-std=c++0x

libosgUrdf_a_DEPENDENCIES = \
														../osgReviz/libosgReviz.a

libosgUrdf_a_SOURCES = \
													src/osgUrdf.cpp