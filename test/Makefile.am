
bin_PROGRAMS =	osgviewerQt

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE

AM_CXXFLAGS = 		-Werror \
									-D_GNU_SOURCE \
									-DQT_SHARED \
									-I$(top_srcdir)/osgReviz \
									-I$(top_srcdir)/qtWidgets/ui \
									-I$(top_srcdir)/qtWidgets \
									-I$(top_srcdir)/osgUrdf \
									-I$(top_srcdir)/include \
									-I$(top_srcdir)/src \
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
							$(top_srcdir)/qtWidgets/libqtWidgets.la \
							$(top_srcdir)/osgReviz/libosgReviz.la \
							$(top_srcdir)/osgUrdf/libosgUrdf.la \
							$(top_srcdir)/src/libmainwindow.la \
							$(GUI_LIBS) \
							$(OSG_LIBS)

osgviewerQt_SOURCES = \
								osgviewerQt.cpp