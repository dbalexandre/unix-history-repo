# $FreeBSD$
#
# Generic build infrastructure for test programs.
#
# The code in this file is independent of the implementation of the test
# programs being built; this file just provides generic infrastructure for the
# build and the definition of various helper variables and targets.
#
# Makefiles should never include this file directly.  Instead, they should
# include one of the various *.test.mk depending on the specific test programs
# being built.

.include <bsd.init.mk>

# Pointer to the top directory into which tests are installed.  Should not be
# overriden by Makefiles, but the user may choose to set this in src.conf(5).
TESTSBASE?= /usr/tests

# Directory in which to install tests defined by the current Makefile.
# Makefiles have to override this to point to a subdirectory of TESTSBASE.
TESTSDIR?= .

# Name of the test suite these tests belong to.  Should rarely be changed for
# Makefiles built into the FreeBSD src tree.
TESTSUITE?= FreeBSD

# List of subdirectories containing tests into which to recurse.  This has the
# same semantics as SUBDIR at build-time.  However, the directories listed here
# get registered into the run-time test suite definitions so that the test
# engines know to recurse into these directories.
#
# In other words: list here any directories that contain test programs but use
# SUBDIR for directories that may contain helper binaries and/or data files.
TESTS_SUBDIRS?=

# Knob to control the handling of the Kyuafile for this Makefile.
#
# If 'yes', a Kyuafile exists in the source tree and is installed into
# TESTSDIR.
#
# If 'auto', a Kyuafile is automatically generated based on the list of test
# programs built by the Makefile and is installed into TESTSDIR.  This is the
# default and is sufficient in the majority of the cases.
#
# If 'no', no Kyuafile is installed.
KYUAFILE?= auto

# List of variables to pass to the tests at run-time via the environment.
TESTS_ENV?=

# Ordered list of directories to construct the PATH for the tests.
TESTS_PATH+= ${DESTDIR}/bin ${DESTDIR}/sbin \
             ${DESTDIR}/usr/bin ${DESTDIR}/usr/sbin
TESTS_ENV+= PATH=${TESTS_PATH:tW:C/ +/:/g}

# Ordered list of directories to construct the LD_LIBRARY_PATH for the tests.
TESTS_LD_LIBRARY_PATH+= ${DESTDIR}/lib ${DESTDIR}/usr/lib
TESTS_ENV+= LD_LIBRARY_PATH=${TESTS_LD_LIBRARY_PATH:tW:C/ +/:/g}

# List of all tests being built.  This variable is internal should not be
# defined by the Makefile.  The various *.test.mk modules extend this variable
# as needed.
_TESTS?=

# Path to the prefix of the installed Kyua CLI, if any.
#
# If kyua is installed from ports, we automatically define a realtest target
# below to run the tests using this tool.  The tools are searched for in the
# hierarchy specified by this variable.
KYUA_PREFIX?= /usr/local

.if !empty(TESTS_SUBDIRS)
SUBDIR+= ${TESTS_SUBDIRS}
.endif

# it is rare for test cases to have man pages
.if !defined(MAN)
WITHOUT_MAN=yes
.export WITHOUT_MAN
.endif

# tell progs.mk we might want to install things
PROG_VARS+= BINDIR
PROGS_TARGETS+= install

.if ${KYUAFILE:tl} != "no"
FILES+=	Kyuafile
FILESDIR_Kyuafile= ${TESTSDIR}

.if ${KYUAFILE:tl} == "auto"
CLEANFILES+= Kyuafile Kyuafile.tmp

Kyuafile: Makefile
	@{ \
	    echo '-- Automatically generated by bsd.test.mk.'; \
	    echo; \
	    echo 'syntax(2)'; \
	    echo; \
	    echo 'test_suite("${TESTSUITE}")'; \
            echo; \
	} >Kyuafile.tmp
.for _T in ${_TESTS}
	@echo "${TEST_INTERFACE.${_T}}_test_program{name=\"${_T}\"}" \
	    >>Kyuafile.tmp
.endfor
.for _T in ${TESTS_SUBDIRS:N.WAIT}
	@echo "include(\"${_T}/Kyuafile\")" >>Kyuafile.tmp
.endfor
	@mv Kyuafile.tmp Kyuafile
.endif
.endif

KYUA?= ${KYUA_PREFIX}/bin/kyua
.if exists(${KYUA})
# Definition of the "make test" target and supporting variables.
#
# This target, by necessity, can only work for native builds (i.e. a FreeBSD
# host building a release for the same system).  The target runs Kyua, which is
# not in the toolchain, and the tests execute code built for the target host.
#
# Due to the dependencies of the binaries built by the source tree and how they
# are used by tests, it is highly possible for a execution of "make test" to
# report bogus results unless the new binaries are put in place.
realtest: .PHONY
	@echo "*** WARNING: make test is experimental"
	@echo "***"
	@echo "*** Using this test does not preclude you from running the tests"
	@echo "*** installed in ${TESTSBASE}.  This test run may raise false"
	@echo "*** positives and/or false negatives."
	@echo
	@set -e; \
	${KYUA} test -k ${DESTDIR}${TESTSDIR}/Kyuafile; \
	result=0; \
	echo; \
	echo "*** Once again, note that "make test" is unsupported."; \
	test $${result} -eq 0
.endif

beforetest: .PHONY
.if defined(TESTSDIR)
.if ${TESTSDIR} == ${TESTSBASE}
# Forbid running from ${TESTSBASE}.  It can cause false positives/negatives and
# it does not cover all the tests (e.g. it misses testing software in external).
	@echo "*** Sorry, you cannot use make test from src/tests.  Install the"
	@echo "*** tests into their final location and run them from ${TESTSBASE}"
	@false
.else
	@echo "*** Using this test does not preclude you from running the tests"
	@echo "*** installed in ${TESTSBASE}.  This test run may raise false"
	@echo "*** positives and/or false negatives."
.endif
.else
	@echo "*** No TESTSDIR defined; nothing to do."
	@false
.endif
	@echo

.if !target(realtest)
realtest: .PHONY
	@echo "$@ not defined; skipping"
.endif

test: .PHONY
.ORDER: beforetest realtest
test: beforetest realtest

.if target(aftertest)
.ORDER: realtest aftertest
test: aftertest
.endif

.if !empty(SUBDIR)
.include <bsd.subdir.mk>
.endif

.if !empty(PROGS) || !empty(PROGS_CXX) || !empty(SCRIPTS)
.include <bsd.progs.mk>
.elif !empty(FILES)
.include <bsd.files.mk>
.endif

.include <bsd.obj.mk>
