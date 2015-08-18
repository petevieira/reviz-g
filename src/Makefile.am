
bin_PROGRAMS =	reviz

lib_LIBRARIES = libmainwindow.a



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
							libmainwindow.a \
							../qtWidgets/libqtWidgets.a \
							../osgReviz/libosgReviz.a \
							../osgUrdf/libosgUrdf.a \
							$(GUI_LIBS) \
							$(OSG_LIBS) \
							$(URDFDOM_LIBS)

reviz_SOURCES = \
								reviz.cpp

libmainwindow_a_DEPENDENCIES = \
													../qtWidgets/libqtWidgets.a \
													../osgReviz/libosgReviz.a \
													../osgUrdf/libosgUrdf.a

libmainwindow_a_LIBFLAGS = -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x

libmainwindow_a_SOURCES =	\
														ViewerWidget.cpp \
														RevizMainWindow.cpp \
														moc_MainWindow.cc MainWindow.cpp \
														GripTimeslice.cpp \
           qrc-resources.cc

moc_MainWindow.cc:	../include/MainWindow.h
					@MOC@ -o $@ $<

qrc-resources.cc: ../resources/qtResources.qrc
	@RCC@ -o $@ $<
