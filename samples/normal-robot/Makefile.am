LDADD = $(top_builddir)/odeutil/libodeutil.la

noinst_PROGRAMS = normalkey inrofkey
normalkey_SOURCES = normalkey.cpp
inrofkey_SOURCES = inrofkey.cpp

if WIN32
resources.o: $(top_srcdir)/odeutil/resources.rc $(top_srcdir)/odeutil/resource.h
	@WINDRES@ $(top_srcdir)/odeutil/resources.rc -o resources.o
LDADD += resources.o
endif
