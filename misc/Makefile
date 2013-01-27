LIBSTATIC = libmisc.a

CC = gcc
LD = gcc
AR = ar
AWKPROG = ../gawk
CMP = cmp

AWK = LC_ALL=$${GAWKLOCALE:-C} LANG=$${GAWKLOCALE:-C} $(AWKPROG)

ALL_CFLAGS = $(CFLAGS) -fPIC -DGAWK -DHAVE_CONFIG_H -c -I.. -I.

all: $(LIBSTATIC)

OBJS := float128.o

$(LIBSTATIC): $(OBJS)
	$(AR) rc $(LIBSTATIC) $(OBJS)
	ranlib $(LIBSTATIC)

float128.o: float128.c ../awk.h ../long_double.h ./gawk_math.h ./gawk_math.c

.c.o:
	$(CC) $(ALL_CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(LIBSTATIC)

distclean: clean

check:

LDBL_TESTS = \
	ldblint64 \
	ldblint128

# An attempt to print something that can be grepped for in build logs
pass-fail:
	@COUNT=`ls "$(TESTDIR)"/_* 2>/dev/null | wc -l` ; \
	if test $$COUNT = 0 ; \
	then	echo ALL TESTS PASSED ; \
	else	echo $$COUNT TESTS FAILED ; \
	fi

ldbl-tests: $(LDBL_TESTS)
	@$(MAKE) pass-fail TESTDIR=ldbl-tests

ldblint64:
	@echo $@
	@$(AWK) -B -f ldbl-tests/$@.awk > ldbl-tests/_$@ 2>&1
	@-$(CMP) ldbl-tests/$@.ok ldbl-tests/_$@ && rm -f ldbl-tests/_$@

ldblint128:
	@echo $@
	@$(AWK) -B1 -f ldbl-tests/$@.awk > ldbl-tests/_$@ 2>&1
	@-$(CMP) ldbl-tests/$@.ok ldbl-tests/_$@ && rm -f ldbl-tests/_$@
