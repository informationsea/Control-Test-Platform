AM_CPPFLAGS = -I$(abs_top_srcdir)/src

LDADD = $(top_builddir)/src/libodeutil.la

noinst_PROGRAMS = slopekey slopeonoff slopetemplate
slopekey_SOURCES = key_controller.c slope_roller.cpp
slopeonoff_SOURCES = onoff_controller.c slope_roller.cpp
slopetemplate_SOURCES = template_controller.c slope_roller.cpp
