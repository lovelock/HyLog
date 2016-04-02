dnl $Id$
dnl config.m4 for extension hylog

 PHP_ARG_ENABLE(hylog, whether to enable hylog support,
 [  --enable-hylog           Enable hylog support])

if test "$PHP_HYLOG" != "no"; then
  PHP_SUBST(HYLOG_SHARED_LIBADD)
  PHP_NEW_EXTENSION(hylog, hylog.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_INSTALL_HEADERS([ext/hylog], [php_hylog.h])
fi
