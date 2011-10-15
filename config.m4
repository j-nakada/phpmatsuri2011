dnl $Id$
dnl config.m4 for extension test_ext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(test_ext, for test_ext support,
dnl Make sure that the comment is aligned:
dnl [  --with-test_ext             Include test_ext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(test_ext, whether to enable test_ext support,
Make sure that the comment is aligned:
[  --enable-test_ext           Enable test_ext support])

if test "$PHP_TEST_EXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-test_ext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/test_ext.h"  # you most likely want to change this
  dnl if test -r $PHP_TEST_EXT/$SEARCH_FOR; then # path given as parameter
  dnl   TEST_EXT_DIR=$PHP_TEST_EXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for test_ext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TEST_EXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TEST_EXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the test_ext distribution])
  dnl fi

  dnl # --with-test_ext -> add include path
  dnl PHP_ADD_INCLUDE($TEST_EXT_DIR/include)

  dnl # --with-test_ext -> check for lib and symbol presence
  dnl LIBNAME=test_ext # you may want to change this
  dnl LIBSYMBOL=test_ext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TEST_EXT_DIR/lib, TEST_EXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TEST_EXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong test_ext lib version or lib not found])
  dnl ],[
  dnl   -L$TEST_EXT_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TEST_EXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(test_ext, test_ext.c, $ext_shared)
fi
