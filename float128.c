#include "awk.h"

#if defined(LDBLTEST) && LDBLTEST == 1
#include <math.h>
#include "random.h"
#if 0
#include "floatmagic.h"	/* definition of isnan -- XXX: only for float or double or long double */
#endif

#include "format.h"

/* XXX: No libquadmath, and don't want or need it anyway. */

/*
 * Macros copied from quadmath.h
 * 	https://github.com/mirrors/gcc/blob/master/libquadmath/quadmath.h
 */

#define FLT128_MAX 1.18973149535723176508575932662800702e4932Q
#define FLT128_MIN 3.36210314311209350626267781732175260e-4932Q
#define FLT128_EPSILON 1.92592994438723585305597794258492732e-34Q
#define FLT128_DENORM_MIN 6.475175119438025110924438958227646552e-4966Q
#define FLT128_MANT_DIG 113
#define FLT128_MIN_EXP (-16381)
#define FLT128_MAX_EXP 16384
#define FLT128_DIG 33
#define FLT128_MIN_10_EXP (-4931)
#define FLT128_MAX_10_EXP 4932

/* #define HUGE_VALQ __builtin_huge_valq() */
/* The following alternative is valid, but brings the warning:
   (floating constant exceeds range of ‘__float128’)  */
#define HUGE_VALQ (__extension__ 0x1.0p32767Q)

/* end of Macros from quadmath.h */


#define LDBL_FRAC_BITS	FLT128_MANT_DIG
#define	LDBL_INT_BITS	128

#define AWKLDBL	__float128
#define LDBL_VAL(n)	(*((AWKLDBL *) (n)->qnumbr))
#define LDC(x)		x##Q

#define get_long_double(d)	emalloc(d, void *, sizeof(AWKLDBL), "float128")
#define free_long_double(d)	efree(d)

static int format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x);
static int format_uint_finite_p(char *str, size_t size, AWKLDBL x);

/*
 * format_uint_1 --- format a AWKLDBL as an unsigned integer. The double value
 *	must be finite and >= 0.
 */

static inline int
format_uint_1(char *str, size_t size, AWKLDBL x)
{
	int ret;
	if ((ret = format_uint_finite_p(str, size, x)) < 0)
		return snprintf(str, size, "%.0f", (double) x);
	return ret;
}

static AWKLDBL double_to_int(AWKLDBL);

/* if have __float128, also have strtold. No ? */

static inline AWKLDBL
gawk_strtold(const char *str, char **endptr)
{
	return strtold(str, endptr);
}

/* Define isnan() and isinf() before including the two files */

static inline int isnan_awkldbl(AWKLDBL x) { return x != x; }
#ifdef isnan
#undef isnan
#endif
#define isnan isnan_awkldbl

static inline int isinf_awkldbl(AWKLDBL x) { return isnan(x - x); }
#ifdef isinf
#undef isinf
#endif
#define isinf isinf_awkldbl

#define GAWK_INFINITY	HUGE_VALQ
#define GAWK_NAN	(LDC(0.0) / LDC(0.0))


/* XXX: Don't want floorl() or ceill() */ 

#ifdef HAVE_FLOORL
#undef HAVE_FLOORL
#endif
#ifdef HAVE_CEILL
#undef HAVE_CEILL
#endif
#ifdef PRINTF_HAS_LF_FORMAT
#undef PRINTF_HAS_LF_FORMAT
#endif

numbr_handler_t float128_hndlr;

#define awkldbl_hndlr float128_hndlr

#define gawk_int_t long long
#define gawk_uint_t unsigned long long
#ifdef SIZEOF_GAWK_INT
#undef SIZEOF_GAWK_INT
#undef GAWK_INT_MAX
#undef GAWK_INT_MIN
#undef GAWK_UINT_MAX
#endif

#define SIZEOF_GAWK_INT	8
#define	GAWK_INT_MAX	LLONG_MAX
#define	GAWK_INT_MIN	LLONG_MIN
#define	GAWK_UINT_MAX	ULLONG_MAX

#define TEST_NUMBR 1

#include "misc/gawk_math.h"
#include "long_double.h"

#endif	/* LDBLTEST == 1 */
