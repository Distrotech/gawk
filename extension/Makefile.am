#
# extension/Makefile.am --- automake input file for gawk
#
# Copyright (C) 1995-2006, 2012 the Free Software Foundation, Inc.
#
# This file is part of GAWK, the GNU implementation of the
# AWK Programming Language.
#
# GAWK is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# GAWK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
#

## Process this file with automake to produce Makefile.in.

AM_CPPFLAGS = -I$(srcdir) -I$(srcdir)/..

# This variable insures that aclocal runs
# correctly after changing configure.ac
ACLOCAL_AMFLAGS = -I m4

# Note that various SHOBJ_* and SHLIB_* variables are defined by
# support/shobj-conf (pulled in by configure.ac and then by automake).

# N.B. This Makefile.am has several known defects:
# 1. It does not generate header file dependencies.
# 2. The install rule is a hideous hack.
# 3. There is no support for uninstall.
# 4. On some platforms, e.g. MacOS, SHLIB_LIBSUFF is not correct.  The
#    shobj-conf script should be enhanced to add SHOBJ_LIBSUFF.

.c.o:
	$(SHOBJ_CC) $(SHOBJ_CFLAGS) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS) -c -o $@ $<

PFX = .libs/
SFX = .$(SHLIB_LIBSUFF)

# on Cygwin, gettext requires that we link with -lintl 
MY_LIBS = $(SHOBJ_LIBS) $(LIBINTL)
SHLINK = $(MKDIR_P) .libs && $(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS)

ALL = $(PFX)filefuncs$(SFX) $(PFX)fnmatch$(SFX) $(PFX)fork$(SFX) \
	$(PFX)inplace$(SFX) \
	$(PFX)ordchr$(SFX) $(PFX)readdir$(SFX) $(PFX)readfile$(SFX) \
	$(PFX)revoutput$(SFX) $(PFX)revtwoway$(SFX) $(PFX)rwarray$(SFX) \
	$(PFX)testext$(SFX) $(PFX)time$(SFX) 

all:	$(SHOBJ_STATUS)

supported:	$(ALL)

unsupported:
	@echo "Your system (${host_os}) is not supported by the"
	@echo "${topdir}/support/shobj-conf script."
	@echo "If your operating system provides facilities for dynamic"
	@echo "loading of shared objects using the dlopen(3) interface,"
	@echo "please update the script and re-run configure.
	@echo "Please send the changes you made to bash-maintainers@gnu.org"
	@echo "for inclusion in future bash releases."

$(PFX)filefuncs$(SFX): filefuncs.o stack.o gawkfts.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)fnmatch$(SFX): fnmatch.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)fork$(SFX): fork.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)inplace$(SFX): inplace.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)ordchr$(SFX): ordchr.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)readdir$(SFX): readdir.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)readfile$(SFX): readfile.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)revoutput$(SFX): revoutput.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)revtwoway$(SFX): revtwoway.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)rwarray$(SFX): rwarray.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)testext$(SFX): testext.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

$(PFX)time$(SFX): time.o
	$(SHLINK) -o $@ $^ $(MY_LIBS)

install-data-hook:
	for i in $(pkgextension_LTLIBRARIES) ; do \
		$(RM) $(pkgextensiondir)/$$i ; \
	done

clean-local:
	$(RM) -fr $(PFX)
	$(RM) -f *.$(OBJEXT)

EXTRA_DIST = build-aux/config.rpath  \
	ChangeLog \
	ChangeLog.0 \
	README.fts \
	fts.3 \
	filefuncs.c \
	fnmatch.c \
	fork.c \
	gawkfts.c \
	gawkfts.h \
	inplace.c \
	ordchr.c \
	readdir.c \
	readfile.c \
	revoutput.c \
	revtwoway.c \
	rwarray.c \
	rwarray0.c \
	stack.c \
	stack.h \
	testext.c \
	time.c \
	support

install-exec-hook:
	$(MKDIR_P) "$(DESTDIR)$(pkgextensiondir)" || exit 1; \
	for i in $(ALL) ; do \
	$(INSTALL) $(INSTALL_STRIP_FLAG) $$i "$(DESTDIR)$(pkgextensiondir)/$$i" ; \
	done

dist_man_MANS = \
	filefuncs.3am fnmatch.3am fork.3am ordchr.3am \
	inplace.3am \
	readdir.3am readfile.3am revoutput.3am \
	revtwoway.3am rwarray.3am time.3am

# gettext requires this
SUBDIRS =

# This is an ugly hack, initially for MirBSD but probably needed for other
# systems. If gawk doesn't have the API built in, don't try to build the
# extensions.
#
# Given the workaround in configure, this isn't strictly necessary, but
# we're leaving it in, in case of some other system needing it.
check-recursive all-recursive: check-for-shared-lib-support

check-for-shared-lib-support:
	@if ../gawk$(EXEEXT) --version | sed 1q | grep API > /dev/null; \
	then	: do nothing ; \
	else	echo Building the extensions is not supported on this platform ; \
		exit 1; \
	fi
