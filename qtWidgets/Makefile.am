
lib_LTLIBRARIES =		libqtWidgets.la

AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS   = 		-Werror \
									-D_GNU_SOURCE

AM_CPPFLAGS = 		-Werror \
									-I$(top_srcdir)/osgGolems \
									-Iui \
									-I/usr/include/qt4 \
									-I/usr/include/qt4/QtXml \
									-I/usr/include/qt4/QtOpenGL \
									-I/usr/include/qt4/QtCore


libqtWidgets_la_SOURCES = 	\
													moc_TreeView.cc ui_TreeView.h \
													moc_InspectorTab.cc ui_InspectorTab.h \
													moc_VisualizationTab.cc ui_VisualizationTab.h \
													moc_PlaybackWidget.cc ui_PlaybackWidget.h

libqtWidgets_la_LIBFLAGS = -shared -L/usr/lib/x86_64-linux-gnu/ -fPIC -std=c++0x -export-dynamic

moc_%.cc:	%.h ui_%.h
					@MOC@ -o $@ $<

ui_%.h:	ui/%.ui
				@UIC@ $< -o $@

CLEAN_FILES: \
						moc_*.cc \
						ui_*.h