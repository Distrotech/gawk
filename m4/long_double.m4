# long_double.m4
dnl Copyright (C) 2012 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl size comparison copied from gnulib math_h.m4 serial 114
dnl gl_LONG_DOUBLE_VS_DOUBLE
dnl determines whether 'long double' and 'double' have the same representation.
dnl Sets variable HAVE_SAME_LONG_DOUBLE_AS_DOUBLE to 0 or 1, and defines
dnl HAVE_SAME_LONG_DOUBLE_AS_DOUBLE accordingly.
dnl The currently known platforms where this is the case are:
dnl Linux/HPPA, Minix 3.1.8, AIX 5, AIX 6 and 7 with xlc, MSVC 9.

dnl Defines USE_LONG_DOUBLE to 1 if long double is found and usable.
dnl Also checks for math functions with long double arguments.

AC_DEFUN([GAWK_USE_LONG_DOUBLE],
[
  gawk_has_long_double=no
  USE_LONG_DOUBLE=

  AC_REQUIRE([AC_TYPE_LONG_DOUBLE])
  if test $ac_cv_type_long_double = yes; then
    AC_CACHE_CHECK([whether long double and double are the same],
     [gl_cv_long_double_equals_double],
     [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[#include <float.h>]],
         [[typedef int check[sizeof (long double) == sizeof (double)
                           && LDBL_MANT_DIG == DBL_MANT_DIG
                           && LDBL_MAX_EXP == DBL_MAX_EXP
                           && LDBL_MIN_EXP == DBL_MIN_EXP
                              ? 1 : -1];
         ]])],
       [gl_cv_long_double_equals_double=yes],
       [gl_cv_long_double_equals_double=no])
     ])
    if test $gl_cv_long_double_equals_double = no; then
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

    AC_CHECK_LIB(m, sinl)
    if test $ac_cv_lib_m_sinl = yes; then
      AC_DEFINE([HAVE_SINL], 1,	[Define to 1 if you have 'sinl' function.])
    fi
    AC_CHECK_LIB(m, cosl)
    if test $ac_cv_lib_m_cosl = yes; then
      AC_DEFINE([HAVE_COSL], 1,	[Define to 1 if you have 'cosl' function.])
    fi
    AC_CHECK_LIB(m, atan2l)
    if test $ac_cv_lib_m_atan2l = yes; then
      AC_DEFINE([HAVE_ATAN2L], 1, [Define to 1 if you have 'atan2l' function.])
    fi
    AC_CHECK_LIB(m, logl)
    if test $ac_cv_lib_m_logl = yes; then
      AC_DEFINE([HAVE_LOGL], 1,	[Define to 1 if you have 'logl' function.])
    fi
    AC_CHECK_LIB(m, expl)
    if test $ac_cv_lib_m_expl = yes; then
      AC_DEFINE([HAVE_EXPL], 1,	[Define to 1 if you have 'expl' function.])
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
    AC_CHECK_LIB(m, powl)
    if test $ac_cv_lib_m_powl = yes; then
      AC_DEFINE([HAVE_POWL], 1,	[Define to 1 if you have 'powl' function.])
    fi
    AC_CHECK_LIB(m, sqrtl)
    if test $ac_cv_lib_m_sqrtl = yes; then
      AC_DEFINE([HAVE_SQRTL], 1, [Define to 1 if you have 'sqrtl' function.])
    fi
  fi

  AC_SUBST(USE_LONG_DOUBLE)
  AC_SUBST(PRINTF_HAS_LF_FORMAT)
])
