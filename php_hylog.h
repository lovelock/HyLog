/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_HYLOG_H
#define PHP_HYLOG_H

extern zend_module_entry hylog_module_entry;
#define phpext_hylog_ptr &hylog_module_entry

#define PHP_HYLOG_VERSION "0.1.0"

#ifdef HYLOG_DEBUG
#undef HYLOG_DEBUG
#define HYLOG_DEBUG(m) fprintf(stderr, "%s\n", m);
#else
#define HYLOG_DEBUG(m)
#endif

#ifdef PHP_WIN32
#	define PHP_HYLOG_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_HYLOG_API __attribute__ ((visibility("default")))
#else
#	define PHP_HYLOG_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(hylog)
	char *default_base_path;
	char *default_logger;
	char *default_datetime_format;
	char *base_path;
	char *logger;
	char *datetime_format;
	zend_bool slicing_type;
	zend_bool slice_by_hour;
	zend_bool use_buffer;
	int buffer_size;
	int level;
	int trace_error;
	int trace_exception;
ZEND_END_MODULE_GLOBALS(hylog)

#define HYLOG_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(hylog, v)

PHP_MINIT_FUNCTION(hylog);
PHP_MSHUTDOWN_FUNCTION(hylog);
#ifndef ZTS
PHP_RINIT_FUNCTION(hylog);
#endif
PHP_MINFO_FUNCTION(hylog);
PHP_GINIT_FUNCTION(hylog);

extern ZEND_DECLARE_MODULE_GLOBALS(hylog);

BEGIN_EXTERN_C()
	PHP_HYLOG_API zval *php_hylog_getBasePath(zend_string *name);
	PHP_HYLOG_API int php_hylog_setBasePath(zend_string *name, zend_string *path);
END_EXTERN_C()


#if defined(ZTS) && defined(COMPILE_DL_HYLOG)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_HYLOG_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
