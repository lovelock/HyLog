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
  | Author: Qingchun.Wang  <frostwong@gmail.com>                         |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_hylog.h"

ZEND_DECLARE_MODULE_GLOBALS(hylog);

zend_class_entry *hylog_ce;

ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

PHP_METHOD(Hylog, getBasePath)
{
	char *str;
	int len;

	len = spprintf(&str, 0, "%s", HYLOG_G(default_base_path));

	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_STRINGL(str, len);
}

/* True global resources - no need for thread safety here */

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("hylog.default_base_path", "/var/logs", PHP_INI_ALL, OnUpdateString, default_base_path, zend_hylog_globals, hylog_globals)
PHP_INI_END()
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_hylog_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_hylog_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "hylog", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_hylog_init_globals
 */
static void php_hylog_init_globals(zend_hylog_globals *hylog_globals)
{
}
/* }}} */

zend_function_entry hylog_methods[] = {
};

PHP_MINIT_FUNCTION(hylog)
{
	zend_class_entry ce;

	REGISTER_INI_ENTRIES();

	INIT_CLASS_ENTRY(ce, "Hylog", hylog_methods);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(hylog)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(hylog)
{
#if defined(COMPILE_DL_HYLOG) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(hylog)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(hylog)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "hylog support", "enabled");
	php_info_print_table_row(2, "version", PHP_HYLOG_VERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ hylog_functions[]
 *
 * Every user visible function must have an entry in hylog_functions[].
 */
const zend_function_entry hylog_functions[] = {
	PHP_FE(confirm_hylog_compiled,	NULL)		/* For testing, remove later. */
	PHP_ME(Hylog, getBasePath, arginfo_void, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_FE_END	/* Must be the last line in hylog_functions[] */
};
/* }}} */

/* {{{ hylog_module_entry
 */
zend_module_entry hylog_module_entry = {
	STANDARD_MODULE_HEADER,
	"hylog",
	hylog_functions,
	PHP_MINIT(hylog),
	PHP_MSHUTDOWN(hylog),
	PHP_RINIT(hylog),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(hylog),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(hylog),
	PHP_HYLOG_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_HYLOG
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(hylog)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
