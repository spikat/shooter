AC_INIT([spishooter], [0.0.1], [])
AC_PREREQ([2.59])

AC_DEFINE_UNQUOTED([SPISHOOTER_VERSION_GIT], ["`git rev-parse HEAD`"], [current version])
AC_DEFINE([SPISHOOTER_VERSION_TAG], PACKAGE_VERSION , [current tag])

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE
AC_PROG_CC
dnl AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_CC_C_O

PKG_PROG_PKG_CONFIG
dnl PKG_CHECK_MODULES(libsdl2, libsdl2-dev >= 2.0.0 )

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

######## DEBUG options #######
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [turns on debug compiler, default:no]))
if test x$enable_debug = xyes; then
    AC_DEFINE([DEBUG], [1], [debug enabled])
    CFLAGS="$CFLAGS -ggdb -W -Wall -O0"
    dnl CXXFLAGS="$CXXFLAGS -ggdb -W -Wall -O0"
else
    CFLAGS="$CFLAGS -W -Wall -DNDEBUG"
    dnl CXXFLAGS="$CXXFLAGS -Wall -DNDEBUG"
fi

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT

