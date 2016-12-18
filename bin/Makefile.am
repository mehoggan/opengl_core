bin_PROGRAMS = runner

if LINUX
AM_CXXFLAGS = -Werror -Wall -pedantic \
	-I/usr/local/include/ -I$(top_builddir)/include/ -std=c++11
else
AM_CXXFLAGS = -Werror -Wall -pedantic \
	-I/usr/local/include/ -std=c++11
endif

# Copy block and rename.
runner_SOURCES = runner.cpp
runner_CXXFLAGS = -I$(top_builddir)/include/ \
	-I$(top_builddir)/tools/include -std=c++11
runner_LDADD = $(top_builddir)/lib/libopengl_core.la
runner_LDFLAGS = -lGL -lX11
if OSX
runner_LDFLAGS = -lc++
endif

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/
