LDADD = $(top_builddir)/odeutil/libodeutil.la
AM_LDFLAGS = -static

noinst_PROGRAMS = slopekey slopeonoff slopetemplate slope_p slope_pd slope_pid
slopekey_SOURCES = slopekey.cpp
slopeonoff_SOURCES = slopeonoff.cpp
slopetemplate_SOURCES = slopetemplate.cpp
slope_p_SOURCES = slope_p.cpp
slope_pd_SOURCES = slope_pd.cpp
slope_pid_SOURCES = slope_pid.cpp

if WIN32
resources.o: $(top_srcdir)/odeutil/resources.rc $(top_srcdir)/odeutil/resource.h
	@WINDRES@ $(top_srcdir)/odeutil/resources.rc -o resources.o
LDADD += resources.o
endif
