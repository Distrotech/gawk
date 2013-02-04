LIBSTATIC = libmisc.a

CC = gcc
LD = gcc
AR = ar
AWKPROG = ../gawk
CMP = cmp

AWK = LC_ALL=$${GAWKLOCALE:-C} LANG=$${GAWKLOCALE:-C} $(AWKPROG)

ALL_CFLAGS = $(CFLAGS) -fPIC -DGAWK -DHAVE_CONFIG_H -c -I.. -I.

all: $(LIBSTATIC)

OBJS := float128.o float80.o

$(LIBSTATIC): $(OBJS)
	$(AR) rc $(LIBSTATIC) $(OBJS)
	ranlib $(LIBSTATIC)

float128.o: float128.c ../awk.h ../long_double.h ./gawk_math.h ./gawk_math.c

float80.o: float80.c ../awk.h ../long_double.h ./gawk_math.h ./gawk_math.c

.c.o:
	$(CC) $(ALL_CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(LIBSTATIC)

distclean: clean

check:

LDBL_TESTS = \
	ldblint64 \
	ldblint128 \
	sqrt64 \
	sqrt113 \
	log64 \
	log113 \
	exp64 \
	exp113 \
	pow64 \
	pow113 \
	sin64 \
	sin113 \
	cos64 \
	cos113

INFILE = ldbl-tests/data.in
INFILE32 = ldbl-tests/sincos.in

# An attempt to print something that can be grepped for in build logs
pass-fail:
	@COUNT=`ls "$(TESTDIR)"/_* 2>/dev/null | wc -l` ; \
	if test $$COUNT = 0 ; \
	then	echo ALL TESTS PASSED ; \
	else	echo $$COUNT TESTS FAILED ; \
	fi

ldbl-tests: $(LDBL_TESTS)
	@$(MAKE) pass-fail TESTDIR=ldbl-tests


$(INFILE):
	@$(AWK) -M -vPREC=quad -f ldblin.awk > $(INFILE) 2>&1

$(INFILE32): $(INFILE)
	@$(AWK) -M -vPREC=quad -f ldblin.awk | \
$(AWK) -M -vPREC=quad '($$1 > -2^32 && $$1 < 2^32){ print $$0 }' > $(INFILE32) 2>&1

ldblint64:
	@echo $@
	@$(AWK) -B0 -f ldbl-tests/$@.awk > ldbl-tests/_$@ 2>&1
	@-$(CMP) ldbl-tests/$@.ok ldbl-tests/_$@ && rm -f ldbl-tests/_$@

ldblint128:
	@echo $@
	@$(AWK) -B1 -f ldbl-tests/$@.awk > ldbl-tests/_$@ 2>&1
	@-$(CMP) ldbl-tests/$@.ok ldbl-tests/_$@ && rm -f ldbl-tests/_$@

sqrt64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/sqrt.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/sqrt.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

sqrt113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/sqrt.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/sqrt.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

log64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/log.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/log.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

log113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/log.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/log.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

exp64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/exp.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/exp.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

exp113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/exp.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/exp.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

pow64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/pow.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/pow.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -vTOL=10 -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

pow113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/pow.awk $(INFILE) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/pow.awk $(INFILE) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -vTOL=20 -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

sin64:
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/sin.awk $(INFILE32) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/sin.awk $(INFILE32) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

sin113: $(INFILE32)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/sin.awk $(INFILE32) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/sin.awk $(INFILE32) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

cos64:
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f ldbl-tests/cos.awk $(INFILE32) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f ldbl-tests/cos.awk $(INFILE32) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@

cos113: $(INFILE32)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f ldbl-tests/cos.awk $(INFILE32) > ldbl-tests/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f ldbl-tests/cos.awk $(INFILE32) > ldbl-tests/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk ldbl-tests/_$@ ldbl-tests/$@.ok && rm ldbl-tests/_$@
