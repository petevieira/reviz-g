
AC_DEFUN([URDFDOM_LIBS_CHECK_CONFIG],
[
  AC_DEFINE(URDFDOM_LIBS, "", [Defined to urdfdom library names list])
  AC_DEFINE(HAVE_URDFDOM_LIBS, "yes", [Defined to yes if have urdfdom libs])
  HAVE_URDFDOM_LIBS="yes"

  AC_CHECK_LIB(urdfdom_model, main,
               URDFDOM_LIBS="$URDFDOM_LIBS -lurdfdom_model",
               HAVE_URDFDOM_LIBS="no"
               AC_MSG_WARN([did not find lurdfdom_model]))

  AM_CONDITIONAL(HAVE_URDFDOM_LIBS, [test x$HAVE_URDFDOM_LIBS == xyes])
  AC_SUBST(URDFDOM_LIBS)
  AC_MSG_NOTICE(AC_HELP_STRING([URDFDOM_LIBS], [$HAVE_URDFDOM_LIBS: $URDFDOM_LIBS]))
])