bin_PROGRAMS = test_opengl_core

AM_CPPFLAGS = -I../../includes -I../../ -I../
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CXXFLAGS = -std=gnu++11

test_opengl_core_SOURCES = \
	../main.cpp \
	../test_x11_display.cpp \
	../test_x11_render_system.cpp

test_opengl_core_LDFLAGS = -no-install \
	-L$(abs_top_builddir)/../../build/.libs -L/usr/lib64/nvidia \
	-lopengl_core -lGL -lX11 -glx
