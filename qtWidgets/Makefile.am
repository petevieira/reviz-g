
lib_LTLIBRARIES =		libqtWidgets.la

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE

AM_CPPFLAGS = 		-Werror \
									-I../osgReviz \
									-Iui \
									-I. \
									-I/usr/include/qt4 \
									-I/usr/include/qt4/QtXml \
									-I/usr/include/qt4/QtOpenGL \
									-I/usr/include/qt4/QtCore


libqtWidgets_la_SOURCES = 	\
													moc_TreeView.cc ui_TreeView.h src/TreeView.cpp \
													moc_InspectorTab.cc ui_InspectorTab.h src/InspectorTab.cpp \
													moc_VisualizationTab.cc ui_VisualizationTab.h src/VisualizationTab.cpp \
													moc_PlaybackWidget.cc ui_PlaybackWidget.h src/PlaybackWidget.cpp \
													moc_DoubleSlider.cc src/DoubleSlider.cpp \
   qrc-resources.cc

libqtWidgets_la_LIBFLAGS = -shared -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x -export-dynamic -soname

moc_%.cc:	%.h ui_%.h
					@MOC@ -o $@ $<

moc_DoubleSlider.cc: DoubleSlider.h
					@MOC@ -o $@ $<

ui_%.h:	ui/%.ui
				@UIC@ $< -o $@

qrc-resources.cc: ../resources/qtResources.qrc
	@RCC@ -o $@ $<

CLEAN_FILES: \
						moc_*.cc \
						ui_*.h
