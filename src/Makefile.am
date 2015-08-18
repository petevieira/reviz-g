
bin_PROGRAMS =	reviz

lib_LTLIBRARIES = libmainwindow.la

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

reviz_LDADD = \
							libmainwindow.la \
							../qtWidgets/libqtWidgets.la \
							../osgReviz/libosgReviz.la \
							../osgUrdf/libosgUrdf.la \
							$(GUI_LIBS) \
							$(OSG_LIBS) \
							$(URDFDOM_LIBS)

reviz_SOURCES = \
								reviz.cpp

libmainwindow_la_LIBADD = \
													../qtWidgets/libqtWidgets.la \
													../osgReviz/libosgReviz.la \
													../osgUrdf/libosgUrdf.la \
													$(GUI_LIBS) \
													$(OSG_LIBS) \
													$(URDFDOM_LIBS)

libmainwindow_la_LIBFLAGS = -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x

libmainwindow_la_SOURCES =	\
														ViewerWidget.cpp \
														RevizMainWindow.cpp \
														moc_MainWindow.cc MainWindow.cpp \
														GripTimeslice.cpp \
           qrc-resources.cc

moc_MainWindow.cc:	../include/MainWindow.h
					@MOC@ -o $@ $<

qrc-resources.cc: ../resources/qtResources.qrc
	@RCC@ -o $@ $<
