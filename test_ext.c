/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2011 The PHP Group                                |
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

/* $Id: header 310447 2011-04-23 21:14:10Z bjori $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_test_ext.h"

/* If you declare any globals in php_test_ext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(test_ext)
*/

/* True global resources - no need for thread safety here */
static int le_test_ext;

/* {{{ test_ext_functions[]
 *
 * Every user visible function must have an entry in test_ext_functions[].
 */
const zend_function_entry test_ext_functions[] = {
	PHP_FE(confirm_test_ext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(ext_substr , NULL)
	PHP_FE(ext_pi , NULL)
	PHP_FE_END	/* Must be the last line in test_ext_functions[] */
};
/* }}} */

/* {{{ test_ext_module_entry
 */
zend_module_entry test_ext_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"test_ext",
	test_ext_functions,
	PHP_MINIT(test_ext),
	PHP_MSHUTDOWN(test_ext),
	PHP_RINIT(test_ext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(test_ext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(test_ext),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TEST_EXT
ZEND_GET_MODULE(test_ext)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("test_ext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_test_ext_globals, test_ext_globals)
    STD_PHP_INI_ENTRY("test_ext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_test_ext_globals, test_ext_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_test_ext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_test_ext_init_globals(zend_test_ext_globals *test_ext_globals)
{
	test_ext_globals->global_value = 0;
	test_ext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(test_ext)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(test_ext)
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
PHP_RINIT_FUNCTION(test_ext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(test_ext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(test_ext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "test_ext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_test_ext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_test_ext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "test_ext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

PHP_FUNCTION(ext_substr)
{
	
	 
	zval ***params;
	char *str;
	int argc,str_len;
	long l = 0, f;

	argc = ZEND_NUM_ARGS();

	if(argc != 2 && argc != 3 ){
        RETURN_FALSE
	}

    params = safe_emalloc(sizeof(zval **), argc, 0);

    if (zend_get_parameters_array_ex(argc, params) == FAILURE) {
        efree(params);
        RETURN_FALSE
    }    

	str = Z_STRVAL_PP(params[0]);
	f = Z_LVAL_PP(params[1]);
	str_len = strlen(str);

	if (argc > 2) {
		l = Z_LVAL_PP(params[2]);
		if ((l < 0 && -l > str_len)) {
	        efree(params);
			RETURN_FALSE;
		} else if (l > str_len) {
			l = str_len;
		}
	} else {
		l = str_len;
	}
	
	if (f > str_len) {
        efree(params);
		RETURN_FALSE;
	} else if (f < 0 && -f > str_len) {
		f = 0;
	}

	if (l < 0 && (l + str_len - f) < 0) {
        efree(params);
		RETURN_FALSE;
	}

	/* if "from" position is negative, count start position from the end
	 * of the string
	 */
	if (f < 0) {
		f = str_len + f;
		if (f < 0) {
			f = 0;
		}
	}

	/* if "length" position is negative, set it to the length
	 * needed to stop that many chars from the end of the string
	 */
	if (l < 0) {
		l = (str_len - f) + l;
		if (l < 0) {
			l = 0;
		}
	}

	if (f >= str_len) {
        efree(params);
		RETURN_FALSE;
	}

	if ((f + l) > str_len) {
		l = str_len - f;
	}

    efree(params);
	RETURN_STRINGL(str + f, l, 1);

/*
	if (Z_TYPE_PP(params[0]) != IS_STRING){
        efree(params);
        RETURN_FALSE
	}



//	SEPARATE_ZVAL(params[0]);
//	SEPARATE_ZVAL(params[1]);

	str = Z_STRVAL_PP(params[0]);
	count = Z_LVAL_PP(params[1]);
	len = strlen(str);


//    printf("%s\n", str);

//    printf("%d\n", count);


	if(count<0){
		count=0;
	}else if (count>len){
		count=len;
		max_count=0;
	}
	
	
//	i=0;
	
//	char substr[len];


	if(argc == 3){
		max_count = Z_LVAL_PP(params[2]);
	}else{
		max_count = len -count;
	}

/*	
	while( i <= max_count){
		substr[i] = str[count];
		i++;
		count++;
	}
*/
/*
str+=count;

//    printf("%c\n", substr[7]);

//    printf("%d\n", len);
//    printf("%d\n", count);
//    printf("%d\n", i);


//    printf("%s\n", substr);


    efree(params);
//    RETURN_STRING(substr, 1);
//    RETURN_STRINGL(substr, max_count, 1);
    RETURN_STRINGL(str, max_count, 1);
    */
}

PHP_FUNCTION(ext_pi){

int a = 10000;
int c = 52500;
int b;
int d;
int e;
int g;
int f[52514];



 for( b = 0 ; b < c ; b++ ) {
    f[b] = a / 5;
  }

  e = 0;
  for( c = 52500 ; c > 0 ; c -= 14 ) {
    d = 0;
    for( b = c - 1 ; b > 0 ; b-- ) {
      g = 2 * b - 1;
      d = d * b + f[b] * a;
      f[b] = d % g;
      d /= g;
    }
    printf("%04d", e + d / a);
    e = d % a;
  }
  return ;



}
