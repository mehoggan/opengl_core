lib_LTLIBRARIES = libopengl_core.la
pkginclude_HEADERS = \
	$(top_builddir)/declspec.h \
	$(top_builddir)/include/opengl_core/core/concurrent_queue.h \
	$(top_builddir)/include/opengl_core/core/init.h \
	$(top_builddir)/include/opengl_core/core/non_copyable.h \
	$(top_builddir)/include/opengl_core/core/platform.h \
	$(top_builddir)/include/opengl_core/core/symbol_loader.h

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects

libopengl_core_la_SOURCES = \
	posix_symbol_loader.cpp

if LINUX
libopengl_core_la_SOURCES += \
	x11/x11_display.cpp \
	x11/x11_extension_checker.cpp \
	x11/x11_gl_functions.cpp \
	x11/x11_init.cpp
pkginclude_HEADERS += \
	$(top_builddir)/include/opengl_core/core/x11/x11_display.h \
	$(top_builddir)/include/opengl_core/core/x11/x11_extension_checker.h
	$(top_builddir)/include/opengl_core/core/x11/x11_gl_functions.h
AM_CPPFLAGS = -I/usr/local/include/ \
	-I$(top_builddir)/include/ -Werror -Wall -pedantic -std=c++11
libopengl_core_la_LDFLAGS = $(INIT_LIBS) -lGL -pthread
endif

if OSX
libopengl_core_la_CXX=/usr/bin/clang
libopengl_core_la_OBJCXX=/usr/bin/clang
libopengl_core_la_SOURCES +=
pkginclude_HEADERS +=
AM_CXXFLAGS = $(INTI_CXXFLAGS) -Werror -Wall -pedantic \
	-I$(top_builddir)/include/ -I$(top_builddir)/objc \
	-std=c++11 -Wall -Werror -pedantic
AM_OBJCXXFLAGS = -x objective-c++ -I$(top_builddir)/include -std=c++11 \
	-I$(top_builddir)/include/objc -framework Cocoa
libopengl_core_la_LDFLAGS = $(INIT_LIBS) -framework Foundation,OpenGL,UIKit
endif
