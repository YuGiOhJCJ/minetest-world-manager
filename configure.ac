# Minetest World Manager: Manage Minetest worlds.
# Copyright (C) 2016  YuGiOhJCJ
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
AC_INIT([Minetest World Manager], [20160621], [yugiohjcj@1s.fr], [], [http://yugiohjcj.1s.fr/])
AM_INIT_AUTOMAKE
AM_PROG_CC_C_O
AC_CHECK_HEADER([ctype.h], [], [AC_MSG_ERROR([missing header: ctype.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([errno.h], [], [AC_MSG_ERROR([missing header: errno.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([getopt.h], [], [AC_MSG_ERROR([missing header: getopt.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([gmp.h], [], [AC_MSG_ERROR([missing header: gmp.h (see https://gmplib.org/)])])
AC_CHECK_HEADER([limits.h], [], [AC_MSG_ERROR([missing header: limits.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([openssl/sha.h], [], [AC_MSG_ERROR([missing header: openssl/sha.h (see https://www.openssl.org/)])])
AC_CHECK_HEADER([stdarg.h], [], [AC_MSG_ERROR([missing header: stdarg.h (see https://gcc.gnu.org/)])])
AC_CHECK_HEADER([stdio.h], [], [AC_MSG_ERROR([missing header: stdio.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([stdlib.h], [], [AC_MSG_ERROR([missing header: stdlib.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([string.h], [], [AC_MSG_ERROR([missing header: string.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_HEADER([time.h], [], [AC_MSG_ERROR([missing header: time.h (see https://www.gnu.org/software/libc/)])])
AC_CHECK_LIB([gmp], [__gmpz_init], [], [AC_MSG_ERROR([missing library: gmp (see https://gmplib.org/)])])
AC_CHECK_LIB([crypto], [SHA1_Init], [], [AC_MSG_ERROR([missing library: crypto (see https://www.openssl.org/)])])
AC_ARG_ENABLE([maintainer-version], [AS_HELP_STRING([--enable-maintainer-version], [enable the maintainer version])], [case "${enableval}" in yes) maintainer_version=true ;; no) maintainer_version=false ;; *) AC_MSG_ERROR([bad value ${enableval} for --enable-maintainer-version]) ;; esac], [maintainer_version=false])
AS_IF([test "x$maintainer_version" = "xtrue"], [AC_DEFINE([MAINTAINER_VERSION]) AC_SUBST([MAINTAINER_CFLAGS], ['-std=c89 -Wall -Werror -pedantic -g'])], [AC_SUBST([MAINTAINER_CFLAGS], [''])])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
