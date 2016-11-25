# Append name of your tests here.

if LINUX
TESTS = check_x11_render_system
check_PROGRAMS = check_x11_render_system
else
endif

if LINUX
AM_CXXFLAGS = -Werror -Wall -pedantic \
	-I/usr/local/include/
else
AM_CXXFLAGS = -Werror -Wall -pedantic \
	-I/usr/local/include/
endif

if LINUX
# Copy block and rename.
check_x11_render_system_SOURCES = suite.cpp check_x11_render_system.cpp
check_x11_render_system_CXXFLAGS = -I$(top_builddir)/include/ \
	-I$(top_builddir)/tests/include -std=c++11 -Wall -Werror -pedantic
check_x11_render_system_LDADD = $(top_builddir)/lib/libopengl_core.la \
	-lcheck -lsubunit -lm -lrt


else
endif

CLEANFILES = *.o
CLEANDIRS = deps/ \
	.lib/

@VALGRIND_CHECK_RULES@
