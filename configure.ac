

dnl Initialize autoconf with name and version of package to be built. 
dnl PACKAGE and VERSION will be so defined in <config.h>.
AC_INIT([reviz],[0.0.0],[pevieira@jpl.nasa.gov])

dnl Use a specfic version of autoconf
AC_PREREQ(2.53)

dnl Get the system description (host and build environment)
AC_CANONICAL_SYSTEM

dnl Initialize automake
AM_INIT_AUTOMAKE()

AC_CONFIG_MACRO_DIR([m4])

dnl Generate a configuration header called <config.h> and put all the C
dnl preprocessor defines in there
AM_CONFIG_HEADER(config.h)

dnl Tests for basic tools
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_RANLIB
AC_PROG_INSTALL  

dnl check sizeof long for 64 vs 32 bit machines
AC_CHECK_SIZEOF([long])


dnl Check for required programs/tools
AC_CHECK_PROG([GENGETOPT], [gengetopt], [gengetopt], [AC_MSG_ERROR([gengetopt is required])])
AC_CHECK_PROG([DOT], [dot], [dot], [AC_MSG_ERROR([dot/graphviz is required])])

dnl Check for some standard headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdint.h stdlib.h string.h pthread.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_C_CONST
AC_C_INLINE

dnl always use -Wall for now
CPPFLAGS="$CPPFLAGS -Wall -Werror"

dnl Checks for library functions.
AC_CHECK_FUNCS([strerror])

dnl set absolute source dir path
ABSSRC=`cd $srcdir && pwd`

m4_include([m4/libosg.m4])
m4_include([m4/liburdfdom.m4])
m4_include([m4/libqt.m4])

OSG_LIBS_CHECK_CONFIG()
URDFDOM_LIBS_CHECK_CONFIG()
QT_LIBS_CHECK_CONFIG()

dnl check for gui libraries
GUI_LIBS="$QT_LIBS $OSG_LIBS"
HAVE_GUI_LIBS="yes"

CPPFLAGS="$CPPFLAGS -I./osgReviz -I./qtWidgets -I./qtWidgets/ui"

AC_CHECK_PROGS(MOC, [moc-qt5 moc-qt4 moc])
AC_CHECK_PROGS(UIC, [uic-qt5 uic-qt4 uic])
AC_CHECK_PROGS(RCC, [rcc])
if test -z "$MOC" || test -z "$UIC" || test -z "$RCC"; then
   AC_MSG_ERROR([Qt utility programs moc, uic, and rcc are required.])
fi

AM_CONDITIONAL(HAVE_MODEL_LIBS, [test x$HAVE_MODEL_LIBS == xyes])
AM_CONDITIONAL(HAVE_GUI_LIBS, [test x$HAVE_GUI_LIBS == xyes])
AM_CONDITIONAL(HAVE_OSG_LIBS, [test x$HAVE_OSG_LIBS == xyes])
AM_CONDITIONAL(HAVE_URDFDOM_LIBS, [test x$HAVE_URDFDOM_LIBS == xyes])

AC_SUBST(GUI_LIBS)

dnl Create files
AC_CONFIG_FILES([Makefile
                osgReviz/Makefile
                qtWidgets/Makefile
                src/Makefile
                osgUrdf/Makefile
                test/Makefile])


AC_OUTPUT

AC_MSG_NOTICE([*************************************************************])
AC_MSG_NOTICE(AC_HELP_STRING([CPPFLAGS], [$CPPFLAGS]))
AC_MSG_NOTICE(AC_HELP_STRING([CFLAGS], [$CFLAGS]))
AC_MSG_NOTICE(AC_HELP_STRING([CXXFLAGS], [$CXXFLAGS]))
AC_MSG_NOTICE(AC_HELP_STRING([LDFLAGS], [$LDFLAGS]))
AC_MSG_NOTICE([*************************************************************])
AC_MSG_NOTICE(AC_HELP_STRING([GUI_LIBS], [$HAVE_GUI_LIBS: $GUI_LIBS]))
AC_MSG_NOTICE(AC_HELP_STRING([OSG_LIBS], [$HAVE_OSG_LIBS: $OSG_LIBS]))
AC_MSG_NOTICE(AC_HELP_STRING([URDFDOM_LIBS], [$HAVE_URDFDOM_LIBS: $URDFDOM_LIBS]))
AC_MSG_NOTICE([*************************************************************])

