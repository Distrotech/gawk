static AWKLDBL gawk_sinl(AWKLDBL x);
static AWKLDBL gawk_cosl(AWKLDBL x);
static AWKLDBL gawk_atan2l(AWKLDBL y, AWKLDBL x);
static AWKLDBL gawk_logl(AWKLDBL x);
static AWKLDBL gawk_expl(AWKLDBL x);
static AWKLDBL gawk_fmodl(AWKLDBL x, AWKLDBL y);
static AWKLDBL gawk_powl(AWKLDBL x, AWKLDBL y);
static AWKLDBL gawk_sqrtl(AWKLDBL x);

static AWKLDBL
gawk_sinl(AWKLDBL x)
{
#ifdef HAVE_SINL
	return sinl( (long double) x);
#else
	return sin( (double) x);
#endif
}

static AWKLDBL
gawk_cosl(AWKLDBL x)
{
#ifdef HAVE_COSL
	return cosl( (long double) x);
#else
	return cos( (double) x);
#endif
}

static AWKLDBL
gawk_atan2l(AWKLDBL y, AWKLDBL x)
{
#ifdef HAVE_ATAN2L
	return atan2l( (long double) y, (long double) x);
#else
	return atan2( (double) y, (double) x);
#endif
}

static AWKLDBL
gawk_logl(AWKLDBL x)
{
#ifdef HAVE_LOGL
	return logl( (long double) x);
#else
	return log( (double) x);
#endif
}

static AWKLDBL
gawk_expl(AWKLDBL x)
{
#ifdef HAVE_LOGL
	return expl( (long double) x);
#else
	return exp( (double) x);
#endif
}

static AWKLDBL
gawk_fmodl(AWKLDBL x, AWKLDBL y)
{
#ifdef HAVE_FMODL
	return fmodl( (long double) x, (long double) y);
#else
	return fmod( (double) x, (double) y);
#endif
}

static AWKLDBL
gawk_powl(AWKLDBL x, AWKLDBL y)
{
#ifdef HAVE_POWL
	return powl( (long double) x, (long double) y);
#else
	return pow( (double) x, (double) y);
#endif
}

static AWKLDBL
gawk_sqrtl(AWKLDBL x)
{
#ifdef HAVE_SQRTL
	return sqrtl( (long double) x);
#else
	return sqrt( (double) x);
#endif 
}
