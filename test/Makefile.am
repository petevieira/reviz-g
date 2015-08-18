
bin_PROGRAMS =	osgviewerQt

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE

AM_CXXFLAGS = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED \
									-I../ \
									-I../osgReviz \
									-I../qtWidgets/ui \
									-I../qtWidgets \
									-I../osgUrdf \
									-I../include \
									-I../src \
									-I/usr/include/qt4 \
									-I/usr/include/qt4/QtXml \
									-I/usr/include/qt4/QtOpenGL \
									-I/usr/include/qt4/QtCore \
									-I/usr/include/qt4/QtGui
									-I/usr/include/osg \
									-I/usr/include/osgViewer \
									-I/usr/include/osgManipulator \
									-I/usr/include/osgGA \
									-I/usr/include/osgQt

osgviewerQt_LDADD = \
							../qtWidgets/libqtWidgets.la \
							../osgReviz/libosgReviz.la \
							../osgUrdf/libosgUrdf.la \
							../src/libmainwindow.la \
							$(GUI_LIBS) \
							$(OSG_LIBS) \
							$(URDFDOM_LIBS)

osgviewerQt_SOURCES = \
								osgviewerQt.cpp