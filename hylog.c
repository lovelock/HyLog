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
static char *base_path;

zend_class_entry *hylog_ce;

/* {{{ ARG_INFO
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(set_base_path_arginfo, 0, 0, 1)
	ZEND_ARG_INFO(0, basePath)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(log_arginfo, 0, 0, 3)
	ZEND_ARG_INFO(0, level)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(concret_log_arginfo, 0, 0, 2)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, context)
ZEND_END_ARG_INFO()
/* }}} */

PHP_METHOD(Hylog, __construct)
{
	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	HYLOG_G(base_path) = estrndup(HYLOG_G(default_base_path), strlen(HYLOG_G(default_base_path)));
}

PHP_METHOD(Hylog, log)
{
	char *_level;
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssa", &_level, &_message, &_context) == FAILURE) {
		return;
	}
}

PHP_METHOD(Hylog, emergency)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, critical)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, alert)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, error)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, warning)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, notice)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, info)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, debug)
{
	char *_message;
	HashTable *_context;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa", &_message, &_context)) {
		return;
	}
}

PHP_METHOD(Hylog, getBasePath)
{
	char *str;
	int len;

	len = spprintf(&str, 0, "%s", HYLOG_G(base_path));

	if (zend_parse_parameters_none() == FAILURE)
		return;

	RETURN_STRINGL(str, len);
}

PHP_METHOD(Hylog, setBasePath)
{
	zval *_base_path;
	int argc = ZEND_NUM_ARGS();

	if (zend_parse_parameters(argc TSRMLS_CC, "z", &_base_path) == FAILURE) {
		return;
	}

	if (argc > 0 && (Z_TYPE_P(_base_path) == IS_STRING ||  Z_STRLEN_P(_base_path) > 0)) {
		if (!HYLOG_G(base_path) || !strcmp(HYLOG_G(base_path), HYLOG_G(default_base_path))) {
			efree(HYLOG_G(base_path));
		}

		HYLOG_G(base_path) = estrndup(Z_STRVAL_P(_base_path), Z_STRLEN_P(_base_path));

		zval_ptr_dtor(_base_path);
		RETURN_TRUE;
	}

	RETURN_FALSE;
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
	PHP_ME(Hylog, __construct, arginfo_void,          ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, getBasePath, arginfo_void,          ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, setBasePath, set_base_path_arginfo, ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, log,         log_arginfo,           ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, emergency,   concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, alert,       concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, critical,    concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, error,       concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, warning,     concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, notice,      concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, info,        concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_ME(Hylog, debug,       concret_log_arginfo,   ZEND_ACC_PUBLIC)
	PHP_FE_END
};

PHP_MINIT_FUNCTION(hylog)
{
	zend_class_entry ce;

	REGISTER_INI_ENTRIES();

	INIT_CLASS_ENTRY(ce, "Hylog", hylog_methods);

	hylog_ce = zend_register_internal_class(&ce TSRMLS_CC);

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
	PHP_FE_END	/* Must be the last line in hylog_functions[] */
};
/* }}} */

/* {{{ hylog_module_entry
 */
zend_module_entry hylog_module_entry = {
	STANDARD_MODULE_HEADER,
	"Hylog",
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
