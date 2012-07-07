AM_CPPFLAGS = -I$(abs_top_srcdir)/odeutil

LDADD = $(top_builddir)/odeutil/libodeutil.la

noinst_PROGRAMS = slopekey slopeonoff slopetemplate
slopekey_SOURCES = key_controller.c slope_roller.cpp
slopeonoff_SOURCES = onoff_controller.c slope_roller.cpp
slopetemplate_SOURCES = template_controller.c slope_roller.cpp


if WIN32
resources.o: $(top_srcdir)/drawstuff/src/resources.rc $(top_srcdir)/drawstuff/src/resource.h
	@WINDRES@ $(top_srcdir)/drawstuff/src/resources.rc -o resources.o
LDADD += resources.o
endif
