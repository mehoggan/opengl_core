bin_PROGRAMS = test_opengl_core

AM_CPPFLAGS = -I../../includes -I../../
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

test_opengl_core_LDFLAGS = -no-install \
	-L$(abs_top_builddir)/../../build/.libs/ -lopengl_core

test_opengl_core_SOURCES = \
	../main.cpp
