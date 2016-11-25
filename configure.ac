#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([opengl_core],[1.0.0-dev],[mhoggan@uber.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT()
AC_CONFIG_SRCDIR([lib/posix_symbol_loader.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Conditionals
AC_CANONICAL_HOST

build_linux=no
build_windows=no
build_mac=no

# Detect the target system
case "${host_os}" in
	linux*)
		build_linux=yes
		AC_CHECK_HEADERS([limits.h])
		AC_CHECK_LIB(m, sincos,
			[LIBS="-lm $LIBS" AC_DEFINE(HAVE_LIBM, 1, [Define if you have m.])],
			[AC_MSG_ERROR([lib m is required - see https://www.gnu.org/software/libc/])])
		;;
	cygwin*|mingw*)
		build_windows=yes
		;;
	darwin*)
		build_mac=yes
		;;
	*)
		AC_MSG_ERROR(["OS $host_os is not supported"])
		;;
esac

AM_CONDITIONAL([LINUX], [test "$build_linux" = "yes"])
AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([OSX], [test "$build_mac" = "yes"])

# Checks for programs.
AC_PROG_CXX

AC_CHECK_HEADERS([\
	math.h
	])

AX_VALGRIND_DFLT()
AX_VALGRIND_CHECK

AC_CONFIG_FILES([Makefile \
	lib/Makefile \
	bin/Makefile \
	tests/Makefile ])
AC_OUTPUT
