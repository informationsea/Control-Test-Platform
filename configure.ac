#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([control-test-platform], [0.1], [okamura@informationsea.info])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([readme-alpha -Wall -Werror foreign color-tests])
AC_CONFIG_SRCDIR([samples/roller-robot/key_controller.c])
AC_CONFIG_HEADERS([config.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

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

# Checks for libraries.
case "$host_os" in
  cygwin* | mingw*)
    LIBS="$LDFLAGS -mwindows -lglu32 -lopengl32 -lwinmm"
    ;;
  *apple* | *darwin*) # For Mac OS X
    LIBS="$LDFLAGS -framework GLUT -framework OpenGL"
    ;;
  *)
    LIBS="$LDFLAGS -L/usr/X11R6/lib -lglut -lGLU -lGL -lm -lpthread"
    ;;
esac

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

AC_CONFIG_FILES([Makefile
                 samples/roller-robot/Makefile
                 src/Makefile])
AC_OUTPUT
