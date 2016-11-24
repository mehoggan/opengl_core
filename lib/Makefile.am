lib_LTLIBRARIES = libopengl_core.la
pkginclude_HEADERS = \
	$(top_srcdir)/declspec.h \
	$(top_srcdir)/include/opengl_core/core/concurrent_queue.h \
	$(top_srcdir)/include/opengl_core/core/extension_checker.h \
	$(top_srcdir)/include/opengl_core/core/fb_config.h \
	$(top_srcdir)/include/opengl_core/core/gl_functions.h \
	$(top_srcdir)/include/opengl_core/core/memory_leaks.h \
	$(top_srcdir)/include/opengl_core/core/non_copyable.h \
	$(top_srcdir)/include/opengl_core/core/platform.h \
	$(top_srcdir)/include/opengl_core/core/render_context.h \
	$(top_srcdir)/include/opengl_core/core/render_system.h \
	$(top_srcdir)/include/opengl_core/core/render_window.h \
	$(top_srcdir)/include/opengl_core/core/symbol_loader.h

if LINUX
pkginclude_HEADERS += $(top_srcdir)/include/opengl_core/core/x11_display.h \
	$(top_srcdir)/include/opengl_core/core/x11_event_mask.h
AM_CXXFLAGS = $(INTI_CFLAGS) -Werror -Wall -pedantic \
	-I/usr/local/include/ -I$(top_srcdir)/include/ -std=c++11 -Wall -Werror \
	-pedantic
else
AM_CXXFLAGS = $(INTI_CFLAGS) -Werror -Wall -pedantic \
	-I/usr/local/include/ -I$(top_srcdir)/include/ -std=c++11 -Wall -Werror \
	-pedantic
endif

ACLOCAL_AMFLAGS = -I m4

libopengl_core_la_SOURCES = \
	extension_checker.cpp \
	posix_symbol_loader.cpp

if LINUX
libopengl_core_la_SOURCES += x11_display.cpp \
	x11_fb_config.cpp \
	x11_gl_functions.cpp \
	x11_render_context.cpp \
	x11_render_system.cpp \
	x11_render_window.cpp
else
endif

if LINUX
libopengl_core_la_LDFLAGS = $(INIT_LIBS) -lSDL2 -lGL -pthread
else
libopengl_core_la_LDFLAGS = $(INIT_LIBS) -lSDL2 -framework OpenGL
endif
