AC_INIT([libmogfs++], [0.1], [jesus@meetup.com], [libmogfspp])

AM_INIT_AUTOMAKE([silent-rules])

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CC

#LT_INIT([disable-static])

AM_PROG_LIBTOOL

AC_ARG_ENABLE([debug], AS_HELP_STRING([enable-debug], 
                            [Enable debugging messages]), 
                            [enable_debug=yes])

if test "$enable_debug" == "yes" 
then
    AC_MSG_NOTICE([Enabled debug]) 
    AC_SUBST(DEBUGSET, [-DDEBUG])
fi

dnl /* 
dnl  * Checking for PCRE++
PKG_CHECK_MODULES(PCRECPP, [libpcrecpp >= 8.12], [],
    [AC_MSG_ERROR([pcrecpp is required])])
AC_SUBST(PCRECPP_CFLAGS)
AC_SUBST(PCRECPP_LIBS)
dnl */

dnl /* 
dnl  * Checking for cURL
PKG_CHECK_MODULES(CURL, [libpcrecpp >= 7.24], [],
    [AC_MSG_ERROR([cURL is required])])
AC_SUBST(CURL_CFLAGS)
AC_SUBST(CURL_LIBS)
dnl */

dnl /* 
dnl  * Checking for Socket++
PKG_CHECK_MODULES(SOCKETCPP, [socket++ >= 1.12], [],
    [AC_MSG_ERROR([Socket++ is required])])
AC_SUBST(SOCKETCPP_CFLAGS)
AC_SUBST(SOCKETCPP_LIBS)
dnl */

AC_SUBST(INCLUDE_DIR, [-I../include])
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
