CC = gcc
LD = gcc
AR = ar
CMP = cmp

srcdir = .
top_srcdir = ..
top_builddir = ..

AWKPROG = $(top_srcdir)/gawk
AWK = LC_ALL=C LANG=C $(AWKPROG)
LIBM_DIR = gawk_libm_tests

LIBSTATIC = libmisc.a

ALL_CFLAGS = $(CFLAGS) -fPIC -DGAWK -DHAVE_CONFIG_H -c -I.. -I.

all: $(LIBSTATIC)

OBJS := float128.o float80.o

$(LIBSTATIC): $(OBJS)
	$(AR) rc $(LIBSTATIC) $(OBJS)
	ranlib $(LIBSTATIC)

float128.o: float128.c $(top_srcdir)/awk.h $(top_srcdir)/long_double.h $(srcdir)/gawk_math.h $(srcdir)/gawk_math.c $(srcdir)/rem_pio2.c

float80.o: float80.c $(top_srcdir)/awk.h $(top_srcdir)/long_double.h $(srcdir)/gawk_math.h $(srcdir)/gawk_math.c $(srcdir)/rem_pio2.c

.c.o:
	$(CC) $(ALL_CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(LIBSTATIC)
	cd $(LIBM_DIR) && rm -f core core.* _*
	cd ldbl_tests && $(MAKE) clean

distclean: clean

check:
	@if grep 'USE_LONG_DOUBLE 1' $(top_builddir)/config.h > /dev/null ; then \
	   cd ldbl_tests && $(MAKE) check GAWK_FLOAT=LDBL ; \
	else \
	   echo long double is not supported on this system ; \
	fi ;

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
	cos113 \
	atan64 \
	atan113 \
	fmod64 \
	fmod113

INFILE = $(LIBM_DIR)/data.in

# An attempt to print something that can be grepped for in build logs
pass-fail:
	@COUNT=`ls "$(TESTDIR)"/_* 2>/dev/null | wc -l` ; \
	if test $$COUNT = 0 ; \
	then	echo ALL TESTS PASSED ; \
	else	echo $$COUNT TESTS FAILED ; \
	fi

libm-tests: $(LDBL_TESTS)
	@$(MAKE) pass-fail TESTDIR=$(LIBM_DIR)


$(INFILE):
	@$(AWK) -M -vPREC=quad -f ldblin.awk > $(INFILE) 2>&1

ldblint64:
	@echo $@
	@$(AWK) -B0 -f $(LIBM_DIR)/$@.awk > $(LIBM_DIR)/_$@ 2>&1
	@-$(CMP) $(LIBM_DIR)/$@.ok $(LIBM_DIR)/_$@ && rm -f $(LIBM_DIR)/_$@

ldblint128:
	@echo $@
	@$(AWK) -B1 -f $(LIBM_DIR)/$@.awk > $(LIBM_DIR)/_$@ 2>&1
	@-$(CMP) $(LIBM_DIR)/$@.ok $(LIBM_DIR)/_$@ && rm -f $(LIBM_DIR)/_$@

sqrt64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/sqrt.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/sqrt.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

sqrt113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/sqrt.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/sqrt.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

log64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/log.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/log.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

log113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/log.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/log.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

exp64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/exp.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/exp.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

exp113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/exp.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/exp.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

pow64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/pow.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/pow.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -vTOL=10 -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

pow113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/pow.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/pow.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -vTOL=20 -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

sin64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/sin.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/sin.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

sin113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/sin.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/sin.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

cos64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/cos.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/cos.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

cos113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/cos.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/cos.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

atan64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/atan2.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/atan2.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

atan113: $(INFILE)
	@echo $@
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/atan2.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/atan2.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

fmod64: $(INFILE)
	@echo $@
	@$(AWK) -B0 -vDIG=17 -f $(LIBM_DIR)/fmod.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=17 -vPREC=64 -f $(LIBM_DIR)/fmod.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@

fmod113: $(INFILE)
	@echo $@
	@echo 'This may take a while.'
	@$(AWK) -B1 -vDIG=32 -f $(LIBM_DIR)/fmod.awk $(INFILE) > $(LIBM_DIR)/_$@ 2>&1
	@$(AWK) -M -vDIG=32 -vPREC=113 -f $(LIBM_DIR)/fmod.awk $(INFILE) > $(LIBM_DIR)/$@.ok 2>&1
	@-$(AWK) -M -f floatcmp.awk $(LIBM_DIR)/_$@ $(LIBM_DIR)/$@.ok && rm $(LIBM_DIR)/_$@
