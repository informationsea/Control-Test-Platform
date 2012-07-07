#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([control-test-platform], [0.1.1], [okamura@informationsea.info])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([readme-alpha -Wall -Werror foreign color-tests])
AC_CONFIG_SRCDIR([samples/roller-robot/key_controller.c])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Checks for libraries.
case "$host_os" in
  cygwin* | mingw*)
    LIBS="$LIBS -mwindows -lglu32 -lopengl32 -lwinmm"
    WIN32=true
    ;;
  *apple* | *darwin*) # For Mac OS X
    LIBS="$LIBS -framework GLUT -framework OpenGL"
    ;;
  *)
    LIBS="$LIBS -L/usr/X11R6/lib -lglut -lGLU -lGL -lm -lpthread"
    ;;
esac

AM_CONDITIONAL([WIN32], [test x$WIN32 = xtrue])

#AC_PRESERVE_HELP_ORDER
#AC_ARG_WITH([ode], [AS_HELP_STRING([--with-ode=PREFIX],
#                                   [Open Dynamics Engine])],
#            [], [with_ode=yes1])
#AC_ARG_WITH([drawstuff], [AS_HELP_STRING([--with-drawstuff=PREFIX],
#                                   [Open Dynamics Engine Drawstuff])],
#            [], [with_drawstuff=yes2])
#AC_ARG_WITH([drawstuff-include], [AS_HELP_STRING([--with-drawstuff-include=PATH],
#                                   [Open Dynamics Engine Drawstuff include files])],
#            [], [with_drawstuff_include=yes3])
#AC_ARG_WITH([drawstuff-lib], [AS_HELP_STRING([--with-drawstuff-lib=PATH],
#                                   [Open Dynamics Engine Drawstuff library path])],
#            [], [with_drawstuff_include=yes5])
#AC_ARG_WITH([textures], [AS_HELP_STRING([--with-textures=PATH],
#                                   [Open Dynamics Engine Drawstuff Textures])],
#            [], [with_textures=yes4])
#
#echo ODE $with_ode
#echo Drawstuff $with_drawstuff
#echo Drawstuff $with_drawstuff_include
#echo Drawstuff $with_textures


# Checks for programs.
AM_PROG_AR
AC_CONFIG_MACRO_DIR([m4])
ACLOCAL_AMFLAGS="-I m4"
AC_DISABLE_SHARED
LT_INIT([disable-shared win32-dll])
AC_CHECK_TOOLS([WINDRES], [windres])
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PATH_PROG(ODE_CONFIG, ode-config, AC_MSG_ERROR(Test for ode-config failed.))

LIBS="`ode-config --libs` -lstdc++ $LIBS"
CPPFLAGS="$CPPFLAGS `ode-config --cflags`"

# Checks for libraries.
AC_CHECK_LIB(ode, [dInitODE], [], AC_MSG_ERROR(Test for library ODE failed.))
AC_CHECK_LIB(drawstuff, [dsSimulationLoop], [], AC_MSG_ERROR(Test for library drawstuff failed.
You have to install this library manually.))

# Checks for header files.
AC_CHECK_HEADERS([ode/ode.h drawstuff/drawstuff.h])
AC_CHECK_HEADERS([sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset sqrt])

# Doxygen
DX_DOCDIR="doc/ctp"
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(ctp, doxygen.cfg, doc/ctp)


AC_CONFIG_FILES([Makefile
                 samples/roller-robot/Makefile
                 odeutil/Makefile])
AC_OUTPUT
