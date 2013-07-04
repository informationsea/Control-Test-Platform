#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([control-test-platform], [0.1.2], [okamura@informationsea.info])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([readme-alpha -Wall -Werror foreign color-tests])
AC_CONFIG_SRCDIR([samples/roller-robot/slopekey.cpp])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Checks for libraries.
case "$host_os" in
  cygwin* | mingw*)
    LIBS="-mwindows -lglu32 -lopengl32 -lwinmm $LIBS"
    WIN32=true
    ;;
  *apple* | *darwin*) # For Mac OS X
    LIBS="-framework GLUT -framework OpenGL $LIBS"
    ;;
  *)
    LIBS="-L/usr/X11R6/lib -lglut -lGLU -lGL -lm -lpthread $LIBS"
    ;;
esac

CPPFLAGS="-Wall -Wextra $CPPFLAGS"

AM_CONDITIONAL([WIN32], [test x$WIN32 = xtrue])


# Checks for programs.
AM_PROG_AR
AC_CONFIG_MACRO_DIR([m4])
ACLOCAL_AMFLAGS="-I m4"
AC_DISABLE_SHARED
LT_INIT([disable-shared])
AC_CHECK_TOOLS([WINDRES], [windres])
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
AC_PRESERVE_HELP_ORDER

AC_ARG_WITH(ode,
[AS_HELP_STRING([--with-ode=PATH],
                [specify prefix directory for the installed ODE package.])])

if test "x$with_ode" != x; then
  AC_PATH_PROG(ODE_CONFIG, [ode-config], [no], [$with_ode/bin])
  if test x$ODE_CONFIG = xno; then
    AC_MSG_ERROR(Test for ode-config failed.)
  fi
  LIBS="`$with_ode/bin/ode-config --libs` -lstdc++ $LIBS"
  CPPFLAGS="$CPPFLAGS `$with_ode/bin/ode-config --cflags`"
else
  AC_PATH_PROG(ODE_CONFIG, ode-config, [no])
  if test x$ODE_CONFIG = xno; then
    AC_MSG_ERROR(Test for ode-config failed.)
  fi
  LIBS="`ode-config --libs` -lstdc++ $LIBS"
  CPPFLAGS="$CPPFLAGS `ode-config --cflags`"
fi


AC_ARG_WITH([drawstuff], [AS_HELP_STRING([--with-drawstuff=PREFIX],
                                   [Open Dynamics Engine Drawstuff])])
AC_ARG_WITH([drawstuff-include], [AS_HELP_STRING([--with-drawstuff-include=PATH],
                                   [Open Dynamics Engine Drawstuff include files])])
AC_ARG_WITH([drawstuff-lib], [AS_HELP_STRING([--with-drawstuff-lib=PATH],
                                   [Open Dynamics Engine Drawstuff library path])])
AC_ARG_WITH([textures], [AS_HELP_STRING([--with-textures=PATH],
                                   [Open Dynamics Engine Drawstuff Textures])])

if test "x$with_drawstuff" != x; then
  drawstuff_include=$with_drawstuff/include
  drawstuff_lib=$with_drawstuff/lib
fi
if test "x$with_drawstuff_include" != x; then
  drawstuff_include=$with_drawstuff_include
fi
if test "x$with_drawstuff_lib" != x; then
  drawstuff_lib=$with_drawstuff_lib
fi
if test "x$with_textures" != x; then
  textures=$with_textures
fi
if test "x$drawstuff_lib" != x;then
   LIBS="-L$drawstuff_lib $LIBS"
fi
if test "x$drawstuff_include" != x;then
   CPPFLAGS="$CPPFLAGS -I$drawstuff_include"
fi
if test "x$textures" == x;then
   if test x$prefix == xNONE;then
     if test "drawstuff_lib" != x;then
       tmpprefix=$drawstuff_lib/..
     elif test "x$with_ode" != x;then
       tmpprefix=$with_ode
     else
       tmpprefix=$ac_default_prefix
     fi
   else
     tmpprefix=$prefix
   fi
   textures="$tmpprefix/$drawstuff/share/drawstuff"
fi
if test ! -f $textures/checkered.ppm ;then
   AC_MSG_ERROR(Drawstuff textures are not found.)
fi
if test ! -f $textures/ground.ppm ;then
   AC_MSG_ERROR(Drawstuff textures are not found.)
fi
if test ! -f $textures/sky.ppm ;then
   AC_MSG_ERROR(Drawstuff textures are not found.)
fi
if test ! -f $textures/wood.ppm ;then
   AC_MSG_ERROR(Drawstuff textures are not found.)
fi

AC_DEFINE_UNQUOTED(DRAWSTUFF_TEXTURE_PATH_DEF, ["$textures"], [define texture path])

AC_CHECK_LIB(ode, [dInitODE], [], AC_MSG_ERROR(Test for library ODE failed.))
AC_CHECK_LIB(drawstuff, [dsSimulationLoop], [], AC_MSG_ERROR(Test for library drawstuff failed.
You have to apply the patch "ode-1.2.patch" in misc to install drawstuff.))

# Checks for header files.
AC_CHECK_HEADER([ode/ode.h], [], AC_MSG_ERROR(Test for library ODE/Drawstuff failed.))
AC_CHECK_HEADER([drawstuff/drawstuff.h], [], AC_MSG_ERROR(Test for library ODE/Drawstuff failed.))
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
                 samples/Makefile
                 samples/template/Makefile
                 samples/normal-robot/Makefile
                 samples/roller-robot/Makefile
                 odeutil/Makefile])
AC_OUTPUT
