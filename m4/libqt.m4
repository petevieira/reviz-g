AC_DEFUN([QT_LIBS_CHECK_CONFIG],
[

  # for now assuming a fixed location for QT
  CPPFLAGS="$CPPFLAGS -I/usr/include/qt4"

  AC_DEFINE(QT_LIBS, [""], [Defined to Qt library names list])
  AC_DEFINE(HAVE_QT_LIBS, ["yes"], [Define to 1 if you have Qt-4.8])
  HAVE_QT_LIBS="yes"

  AC_MSG_NOTICE(HAVE_QT_LIBS: $HAVE_QT_LIBS)

  AC_CHECK_LIB(QtOpenGL, main,
               QT_LIBS="$QT_LIBS -lQtOpenGL",
               HAVE_QT_LIBS="no"
               AC_MSG_WARN([did not find libQtOpenGL]))

  AC_CHECK_LIB(QtGui, main,
               QT_LIBS="$QT_LIBS -lQtGui",
               HAVE_QT_LIBS="no"
               AC_MSG_WARN([did not find libQtGui]))

  AC_CHECK_LIB(QtCore, main,
               QT_LIBS="$QT_LIBS -lQtCore",
               HAVE_QT_LIBS="no"
               AC_MSG_WARN([did not find libQtCore]))

  AC_CHECK_LIB(QtXml, main,
               QT_LIBS="$QT_LIBS -lQtXml",
               HAVE_QT_LIBS="no"
               AC_MSG_WARN([did not find libQtXml]))

  AM_CONDITIONAL(HAVE_QT_LIBS, [test x$HAVE_QT_LIBS == xyes])
  AC_SUBST(QT_LIBS)
  AC_MSG_NOTICE(AC_HELP_STRING([QT_LIBS], [$HAVE_QT_LIBS: $QT_LIBS]))

])
