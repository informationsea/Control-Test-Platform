lib_LTLIBRARIES = libodeutil.la
libodeutil_la_SOURCES = indicator.cpp inroffield.cpp marker.cpp normal.cpp odeutil.cpp platform.cpp roller.cpp slopefield.cpp obstaclefield.cpp

libodeutil_la_includedir = $(includedir)/odeutil
libodeutil_la_include_HEADERS = indicator.h inroffield.h marker.h normal.h odeutil.h platform.h readme.h roller.h slopefield.h obstaclefield.h

if WIN32
libodeutil_la_include_HEADERS += resource.h
libodeutil_la_SOURCES += resources.rc
endif
