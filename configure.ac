

dnl Initialize autoconf with name and version of package to be built. 
dnl PACKAGE and VERSION will be so defined in <config.h>.
AC_INIT([reviz],[0.0.0],[pevieira@jpl.nasa.gov])

dnl Use a specfic version of autoconf
AC_PREREQ(2.53)

dnl check for externals arg early on so we quit early if it's not specified
AC_ARG_WITH(externals, AC_HELP_STRING([--with-externals=PATH], 
            [The path to the externals source trees]),
            externals_dir="$withval", 
	    AC_MSG_ERROR([externals source tree is required (specify --with-externals=DIR)]))

AC_SUBST(externals_dir)

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
AC_PROG_LIBTOOL
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

dnl check for standard libs
AC_CHECK_LIB(pthread, main, , [AC_MSG_ERROR([could not find pthread])])
AC_CHECK_LIB(rt, main, , [AC_MSG_ERROR([could not find rt])])
AC_CHECK_LIB(m, main, , [AC_MSG_ERROR([could not find m])])


# by convention, we will install 3rd party libraries in ext/
# with header files in their own subdirectory in libs/include/<pkg>
# and libries in libs/lib-<arch>/lib<pkg>.a (where arch is `uname -a`) 

# CPPFLAGS="$CPPFLAGS -I$ABSSRC/ext/include -I$ABSSRC/ext/include/bullet"
# LDFLAGS="$LDFLAGS -L$ABSSRC/ext/lib-$target_cpu"


dnl check for required 3rd party headers
# AC_CHECK_HEADERS([lump/lump_log.h],,[AC_MSG_ERROR([lump is required])])

dnl check for common libraries used by all modules

dnl technically we should only set ETHERCAT_{CPPFLAGS,LDFLAGS}, but it won't
dnl hurt to have these included globally, except it's ugly
# CPPFLAGS="${CPPFLAGS} -I${ethercat_dir}/include"
# LDFLAGS="${LDFLAGS} -L${ethercat_dir}/lib"

AC_LANG_PUSH([C++])

AC_LANG_POP([C++])

dnl check for gui libraries
GUI_LIBS=""
HAVE_GUI_LIBS="yes"

OSG_LIBS=""
HAVE_OSG_LIBS="yes"

# for now assuming a fixed location for QT
CPPFLAGS="$CPPFLAGS -I/usr/include/qt4"
CPPFLAGS="$CPPFLAGS -I./osgReviz -I./qtWidgets -I./qtWidgets/ui"

AC_CHECK_LIB(QtOpenGL, main,
             GUI_LIBS="$GUI_LIBS -lQtOpenGL",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libQtOpenGL]))

AC_CHECK_LIB(QtGui, main,
             GUI_LIBS="$GUI_LIBS -lQtGui",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libQtGui]))

AC_CHECK_LIB(QtCore, main,
             GUI_LIBS="$GUI_LIBS -lQtCore",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libQtCore]))

AC_CHECK_LIB(QtXml, main,
             GUI_LIBS="$GUI_LIBS -lQtXml",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libQtXml]))

AC_CHECK_LIB(GLU, main,
             GUI_LIBS="$GUI_LIBS -lGLU",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libGLU]))

AC_CHECK_LIB(glut, main,
             GUI_LIBS="$GUI_LIBS -lglut",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libglut]))

AC_CHECK_LIB(GL, main,
             GUI_LIBS="$GUI_LIBS -lGL",
             HAVE_GUI_LIBS="no"
             AC_MSG_WARN([did not find libGL]))

# OpenSceneGraph
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

AC_CHECK_PROGS(MOC, [moc-qt5 moc-qt4 moc])
AC_CHECK_PROGS(UIC, [uic-qt5 uic-qt4 uic])
AC_CHECK_PROGS(RCC, [rcc])
if test -z "$MOC" || test -z "$UIC" || test -z "$RCC"; then
   AC_MSG_ERROR([Qt utility programs moc, uic, and rcc are required.])
fi

AM_CONDITIONAL(HAVE_MODEL_LIBS, [test x$HAVE_MODEL_LIBS == xyes])
AM_CONDITIONAL(HAVE_GUI_LIBS, [test x$HAVE_GUI_LIBS == xyes])
AM_CONDITIONAL(HAVE_OSG_LIBS, [test x$HAVE_OSG_LIBS == xyes])

AC_SUBST(MODEL_LIBS)
AC_SUBST(GUI_LIBS)
AC_SUBST(OSG_LIBS)

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
AC_MSG_NOTICE(AC_HELP_STRING([LIBS], [$LIBS]))
AC_MSG_NOTICE([*************************************************************])
AC_MSG_NOTICE(AC_HELP_STRING([GUI_LIBS], [$HAVE_GUI_LIBS: $GUI_LIBS]))
AC_MSG_NOTICE(AC_HELP_STRING([OSG_LIBS], [$HAVE_OSG_LIBS: $OSG_LIBS]))
AC_MSG_NOTICE([*************************************************************])

