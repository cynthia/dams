#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([dams], [4.3.4], [sagara@csis.u-tokyo.ac.jp])
AM_INIT_AUTOMAKE([dams], [4.3.4])
AC_CONFIG_SRCDIR([lib/itaiji.cpp.in])
AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_MACRO_DIR([m4])

# library version
LIB_VERSION_INFO='4.3.4'
AC_SUBST(LIB_VERSION_INFO)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([iconv], [libiconv_open])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h limits.h memory.h netinet/in.h stdlib.h string.h strings.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([gettimeofday memmove memset munmap])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 lib/Makefile
		 dams_makedic/Makefile
		 src/Makefile
                 php-extension/Makefile])
AC_OUTPUT
