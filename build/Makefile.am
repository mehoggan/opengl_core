lib_LTLIBRARIES = libopengl_core.la

AM_CPPFLAGS = -I../includes -I../
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4
AM_CXXFLAGS = -std=gnu++11

# List your sources
libopengl_core_la_SOURCES = \
	../src/extension_checker.cpp \
	../src/posix_symbol_loader.cpp \
	../src/x11_gl_functions.cpp \
	../src/x11_display.cpp \
	../src/x11_fb_config.cpp \
	../src/x11_render_context.cpp \
	../src/x11_render_system.cpp \
	../src/x11_render_window.cpp

# List version info and other linker flags.
libopengl_core_la_LDFLAGS = -version-info 1:0:0 -L/usr/lib64/nvidia/xorg \
	-lX11 -glx -pthread


