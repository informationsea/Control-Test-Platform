LDADD = $(top_builddir)/odeutil/libodeutil.la

noinst_PROGRAMS = obstacletemplate obstacle_static obstacle_follow obstacle_follow_real obstacletemplate_real
obstacletemplate_SOURCES = obstacletemplate.cpp
obstacle_static_SOURCES = obstacle_static.cpp
obstacle_follow_SOURCES = obstacle_follow.cpp
obstacle_follow_real_SOURCES = obstacle_follow_real.cpp
obstacletemplate_real_SOURCES = obstacletemplate_real.cpp

if WIN32
resources.o: $(top_srcdir)/odeutil/resources.rc $(top_srcdir)/odeutil/resource.h
	@WINDRES@ $(top_srcdir)/odeutil/resources.rc -o resources.o
LDADD += resources.o
endif
