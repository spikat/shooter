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

PKG_CHECK_MODULES( sdl2, sdl2 >= 2.0.0 )
PKG_CHECK_MODULES( SDL2_ttf, SDL2_ttf >= 2.0.0 )
PKG_CHECK_MODULES( SDL2_mixer, SDL2_mixer >= 2.0.0 )
PKG_CHECK_MODULES( SDL2_image, SDL2_image >= 2.0.0 )

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

######## DEBUG options #######
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [turns on debug compiler, default:no]))
if test x$enable_debug = xyes; then
    AC_DEFINE([DEBUG], [1], [debug enabled])
    CFLAGS="$CFLAGS -ggdb -W -Wall -O0"
else
    CFLAGS="$CFLAGS -W -Wall -DNDEBUG"
fi

######## SOUND options #######
AC_ARG_ENABLE(sound, AS_HELP_STRING([--disable-sound], [turns off sound, default:enabled]))
if test x$enable_sound = xno; then
    CFLAGS="$CFLAGS -DNSOUND"
else
    AC_DEFINE([SOUND], [1], [sound enabled])
fi
AM_CONDITIONAL(USE_SOUND, test x$enable_sound = xyes)

AC_CONFIG_FILES([Makefile
                 src/Makefile])

AC_OUTPUT

