dnl $Id$
dnl config.m4 for extension hylog

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(hylog, for hylog support,
dnl Make sure that the comment is aligned:
dnl [  --with-hylog             Include hylog support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(hylog, whether to enable hylog support,
dnl Make sure that the comment is aligned:
 [  --enable-hylog           Enable hylog support])

if test "$PHP_HYLOG" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-hylog -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/hylog.h"  # you most likely want to change this
  dnl if test -r $PHP_HYLOG/$SEARCH_FOR; then # path given as parameter
  dnl   HYLOG_DIR=$PHP_HYLOG
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for hylog files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       HYLOG_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$HYLOG_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the hylog distribution])
  dnl fi

  dnl # --with-hylog -> add include path
  dnl PHP_ADD_INCLUDE($HYLOG_DIR/include)

  dnl # --with-hylog -> check for lib and symbol presence
  dnl LIBNAME=hylog # you may want to change this
  dnl LIBSYMBOL=hylog # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $HYLOG_DIR/$PHP_LIBDIR, HYLOG_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_HYLOGLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong hylog lib version or lib not found])
  dnl ],[
  dnl   -L$HYLOG_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(HYLOG_SHARED_LIBADD)

  PHP_NEW_EXTENSION(hylog, hylog.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
