# long_double.m4
dnl Copyright (C) 2012 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl Defines USE_LONG_DOUBLE to 1 if long double is found and usable.
dnl Also checks for math functions with long double arguments.

AC_DEFUN([GAWK_USE_LONG_DOUBLE],
[
  gawk_has_long_double=no
  USE_LONG_DOUBLE=

  AC_REQUIRE([AC_TYPE_LONG_DOUBLE])
  if test $ac_cv_type_long_double = yes; then
    AC_CACHE_CHECK([whether long double and double are the same],
     [gawk_cv_long_double_equals_double],
     [AC_RUN_IFELSE(
       [AC_LANG_PROGRAM([[#include <float.h>]],
         [[
            return ! (LDBL_MANT_DIG > DBL_MANT_DIG
        	  	&& LDBL_MAX_EXP >= DBL_MAX_EXP
                	&& LDBL_MIN_EXP <= DBL_MIN_EXP);        
          ]])],
       [gawk_cv_long_double_equals_double=no],
       [gawk_cv_long_double_equals_double=yes])
     ])
    if test $gawk_cv_long_double_equals_double = no; then
      AC_CACHE_CHECK([whether printf supports %Lf],
       [gawk_cv_has_L_format],
       [AC_RUN_IFELSE(
         [AC_LANG_PROGRAM([[#include <stdio.h>]],
           [[char buf[100];
	   sprintf(buf, "%Lf,%Lg,%Le", (long double) 1.0, (long double) 1.0, (long double) 1.0);
           if (strcmp(buf, "1.000000,1,1.000000e+00") == 0)
              return 0;
	   return 1;
          ]])],
         [gawk_cv_has_L_format=yes],
	 [gawk_cv_has_L_format=no])
       ])
       gawk_has_long_double=yes
    fi
  fi

  if test $gawk_has_long_double = yes; then
    AC_DEFINE([USE_LONG_DOUBLE], [1],
           [Define to 1 if can use 'long double'.])
    if test $gawk_cv_has_L_format = yes; then
      AC_DEFINE([PRINTF_HAS_LF_FORMAT], [1],
           [Define to 1 if printf supports %Lf format.])
    fi

    AC_CHECK_FUNC(strtold)
    if test $ac_cv_func_strtold = yes; then
      AC_DEFINE([HAVE_STRTOLD], 1, [Define to 1 if you have 'strtold' function.])
    fi

    LONG_DOUBLE_SAVE_LIBS=$LIBS
    gawk_use_included_math=no
    AC_CHECK_LIB(m, sinl)
    AC_CHECK_LIB(m, cosl)
    AC_CHECK_LIB(m, atan2l)
    AC_CHECK_LIB(m, logl)
    AC_CHECK_LIB(m, expl)
    AC_CHECK_LIB(m, powl)
    AC_CHECK_LIB(m, sqrtl)
    if test $ac_cv_lib_m_sinl = no || test $ac_cv_lib_m_cosl = no \
          || test $ac_cv_lib_m_atan2l = no ||  test $ac_cv_lib_m_logl = no \
  	  || test $ac_cv_lib_m_expl = no ||  test $ac_cv_lib_m_powl = no \
  	  || test $ac_cv_lib_m_sqrtl = no; then
       gawk_use_included_math=yes
       AC_DEFINE([USE_INCLUDED_MATH_FUNCS], 1, [Define to 1 if you need our math functions.])
    fi

    AC_CHECK_LIB(m, fmodl)
    if test $ac_cv_lib_m_fmodl = yes; then
      AC_DEFINE([HAVE_FMODL], 1, [Define to 1 if you have 'fmodl' function.])
    fi
    AC_CHECK_LIB(m, floorl)
    if test $ac_cv_lib_m_floorl = yes; then
      AC_DEFINE([HAVE_FLOORL], 1, [Define to 1 if you have 'floorl' function.])
    fi
    AC_CHECK_LIB(m, ceill)
    if test $ac_cv_lib_m_ceill = yes; then
      AC_DEFINE([HAVE_CEILL], 1, [Define to 1 if you have 'ceill' function.])
    fi
    if test $ac_cv_lib_m_fmodl = yes || test $ac_cv_lib_m_floorl = yes \
          || test $ac_cv_lib_m_ceill = yes || test $gawk_use_included_math = no; then
       LIBS="$LONG_DOUBLE_SAVE_LIBS -lm"
    else
       LIBS="$LONG_DOUBLE_SAVE_LIBS"
    fi
  fi

  AC_SUBST(USE_LONG_DOUBLE)
  AC_SUBST(PRINTF_HAS_LF_FORMAT)
])
