AC_DEFUN([OSG_LIBS_CHECK_CONFIG],
[
  AC_DEFINE(OSG_LIBS, [""], [Defined to OpenSceneGraph library names list])
  AC_DEFINE(HAVE_OSG_LIBS, ["yes"], [Define to 1 if you have OpenSceneGraph-3.2.1])
  HAVE_OSG_LIBS="yes"

  AC_MSG_NOTICE(HAVE_OSG_LIBS: $HAVE_OSG_LIBS)

  AC_CHECK_LIB(osg, main,
               OSG_LIBS="$OSG_LIBS -losg",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losg]))

  AC_CHECK_LIB(osgQt, main,
               OSG_LIBS="$OSG_LIBS -losgQt",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losgQt]))

  AC_CHECK_LIB(osgViewer, main,
               OSG_LIBS="$OSG_LIBS -losgViewer",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losgViewer]))

  AC_CHECK_LIB(osgManipulator, main,
               OSG_LIBS="$OSG_LIBS -losgManipulator",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losgManipulator]))

  AC_CHECK_LIB(osgGA, main,
               OSG_LIBS="$OSG_LIBS -losgGA",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losgGA]))

  AC_CHECK_LIB(osgDB, main,
               OSG_LIBS="$OSG_LIBS -losgDB",
               HAVE_OSG_LIBS="no"
               AC_MSG_WARN([did not find losgDB]))

  AM_CONDITIONAL(HAVE_OSG_LIBS, [test x$HAVE_OSG_LIBS == xyes])
  AC_SUBST(OSG_LIBS)
  AC_MSG_NOTICE(AC_HELP_STRING([OSG_LIBS], [$HAVE_OSG_LIBS: $OSG_LIBS]))

])
