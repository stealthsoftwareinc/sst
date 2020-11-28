##
## For the copyright information for this file, please search up the
## directory tree for the first COPYING file.
##

#
# Some parts of this file are from the SST package.
#
# The following copyright notice is generally applicable:
#
#      Copyright (C) Stealth Software Technologies, Inc.
#
# The full copyright information depends on the distribution
# of the package. For more information, see the COPYING file.
# However, depending on the context in which you are viewing
# this file, the COPYING file may not be available.
#

## begin_variables

ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = \
  -I src/c_cpp/lib \
  -I $(srcdir)/src/c_cpp/lib \
  -I src/c_cpp/include \
  -I $(srcdir)/src/c_cpp/include \
  -I include \
  -I $(srcdir)/include \
$(prevent_an_empty_line)

AM_CXXFLAGS = \
$(prevent_an_empty_line)

AM_MAKEINFOFLAGS = \
  -I doc/texi \
  -I $(srcdir)/doc/texi \
$(prevent_an_empty_line)

AM_MAKEINFOHTMLFLAGS = \
  $(AM_MAKEINFOFLAGS) \
  --css-include=texinfo.css \
  --no-headers \
  --no-split \
  --set-customization-variable TOP_NODE_UP=Top \
$(prevent_an_empty_line)

AM_TEXI2DVIFLAGS = \
  $(AM_MAKEINFOFLAGS) \
$(prevent_an_empty_line)

BUILT_SOURCES =

DISTCLEANFILES =

EXTRA_DIST =

GATBPS_JAVADOCFLAGS =
GATBPS_JAVADOCFLAGS += \
  '-tag' 'param' \
  '-tag' 'return' \
  '-tag' 'throws' \
  '-tag' 'accesses:a:Accesses:' \
  '-tag' 'modifies:a:Modifies:' \
  '-tag' 'wellbehaved:a:Well-Behaved:' \
  '-tag' 'available:a:Available:' \
  '-tag' 'see' \
  '-tag' 'since' \
  '-tag' 'inheritancenotes:a:Inheritance Notes:' \
  '-tag' 'examples:a:Examples:' \
  '-tag' 'notablechanges:a:Notable Changes:' \
$(prevent_an_empty_line)

MAINTAINERCLEANFILES =

MOSTLYCLEANFILES =
MOSTLYCLEANFILES += $(java_src)

SUBDIRS =
SUBDIRS += gen

SUFFIXES =

TESTS =

TEXI2DVI = \
  'texi2dvi' \
  $(AM_TEXI2DVIFLAGS) \
  $(TEXI2DVIFLAGS) \
$(prevent_an_empty_line)

TMPEXT = .gitignorable.tmp

XFAIL_TESTS =

bin_PROGRAMS =

bin_SCRIPTS =

check_PROGRAMS =

dist_java_DATA =

dist_pkgdata_DATA =

dvi_dist_dep =
dvi_dist_dep += $(doc_sst_TEXINFOS)
dvi_dist_dep += doc/sst.texi

dvi_dist_dst =
dvi_dist_dst += doc/sst-$(PACKAGE_VERSION).dvi

dvi_dist_src =
dvi_dist_src += doc/sst.dvi

html_dist_dep =
html_dist_dep += $(doc_sst_TEXINFOS)
html_dist_dep += doc/sst.texi

html_dist_dst =
html_dist_dst += doc/sst-$(PACKAGE_VERSION).html

html_dist_src =
html_dist_src += doc/sst.html

include_HEADERS =

info_TEXINFOS =
info_TEXINFOS += doc/sst.texi

jar_classpath_files =

javadoc_JAVADOCFLAGS =
javadoc_JAVADOCFLAGS += $(GATBPS_JAVADOCFLAGS)
javadoc_JAVADOCFLAGS += '-windowtitle' '$(PACKAGE_STRING) Javadoc Reference'

javadoc_dist_dep =
javadoc_dist_dep += $(javadoc_src)

javadoc_dist_dst =
javadoc_dist_dst += doc/sst-$(PACKAGE_VERSION)-javadoc

javadoc_dist_src =
javadoc_dist_src += $(javadoc_dst)

javadoc_dst =
javadoc_dst += doc/sst-javadoc

lib_LTLIBRARIES =

libexec_PROGRAMS =

libexec_SCRIPTS =

nodist_noinst_HEADERS =

noinst_HEADERS =

noinst_LIBRARIES =

noinst_LTLIBRARIES =

noinst_PROGRAMS =

noinst_SCRIPTS =

pdf_dist_dep =
pdf_dist_dep += $(doc_sst_TEXINFOS)
pdf_dist_dep += doc/sst.texi

pdf_dist_dst =
pdf_dist_dst += doc/sst-$(PACKAGE_VERSION).pdf

pdf_dist_src =
pdf_dist_src += doc/sst.pdf

pkgdata_DATA =

pkglibexec_PROGRAMS =

pkglibexec_SCRIPTS =

pkgsysconfdir = $(sysconfdir)/$(PACKAGE_TARNAME)

plaintext_dep =
plaintext_dep += $(doc_sst_TEXINFOS)

plaintext_dist_dep =
plaintext_dist_dep += $(doc_sst_TEXINFOS)
plaintext_dist_dep += doc/sst.texi

plaintext_dist_dst =
plaintext_dist_dst += doc/sst-$(PACKAGE_VERSION).txt

plaintext_dist_src =
plaintext_dist_src += doc/sst.txt

plaintext_dst =
plaintext_dst += doc/sst.txt

plaintext_src =
plaintext_src += doc/sst.texi

ps_dist_dep =
ps_dist_dep += $(doc_sst_TEXINFOS)
ps_dist_dep += doc/sst.texi

ps_dist_dst =
ps_dist_dst += doc/sst-$(PACKAGE_VERSION).ps

ps_dist_src =
ps_dist_src += doc/sst.ps

## end_variables

## begin_variable_additions

## end_variable_additions

$(distdir).tar.gz:
	$(MAKE) $(AM_MAKEFLAGS) dist-gzip

.PHONY: FORCE
FORCE:

#-----------------------------------------------------------------------
# Code generation
#-----------------------------------------------------------------------

gen_targets =

.PRECIOUS: $(gen_targets)

.PHONY: dummy.wqn2YGuE9D

$(gen_targets) dummy.wqn2YGuE9D:
	$(AM_V_at)cd gen && $(MAKE) $(AM_MAKEFLAGS) $@

##----------------------------------------------------------------------

##----------------------------------------------------------------------
## java-gatbps build group
##----------------------------------------------------------------------

if WITH_BUILD_GROUP_JAVA_GATBPS
if HAVE_JAVA
if HAVE_JAVAC

dist_java_DATA += $(jar_classpath_files)

## begin_rules

all-local: java-main

check-local: check-java

install-data-local: install-java-main

uninstall-local: uninstall-java-main

## end_rules

endif
endif
endif

##----------------------------------------------------------------------
## java-maven build group
##----------------------------------------------------------------------

.PHONY: maven-prep
maven-prep: FORCE
maven-prep: sst-java/src/main/java/com/stealthsoftwareinc/sst/BuildConfig.java

if WITH_BUILD_GROUP_JAVA_MAVEN
all-local: maven-prep
endif

##----------------------------------------------------------------------

## begin_includes

include $(srcdir)/bin/sst_status_map_generator.am
include $(srcdir)/build-aux/autogen.am
include $(srcdir)/include/src/sst_status_map.inc.am
include $(srcdir)/rpm/centos-7/x86_64/rpm.am
include $(srcdir)/rpm/rhel-7/x86_64/rpm.am
include $(srcdir)/src/com/stealthsoftwareinc/sst/BuildConfig.java.am
include $(srcdir)/src/com/stealthsoftwareinc/sst/BuildConfig.java.im.am_

## end_includes

## begin_includes

include $(srcdir)/build-aux/GATBPS_CONFIG_FILE_RULES.am
include $(srcdir)/build-aux/GATBPS_CONFIG_LATER_RULES.am
include $(srcdir)/build-aux/GATBPS_CP_RULES.am
include $(srcdir)/build-aux/GATBPS_DOCKER_BUILD_RULES.am
include $(srcdir)/build-aux/GATBPS_GIT_ARCHIVE_RULES.am
include $(srcdir)/build-aux/GATBPS_GIT_BUNDLE_RULES.am
include $(srcdir)/build-aux/GATBPS_GIT_CLONE_RULES.am
include $(srcdir)/build-aux/GATBPS_JAVA_CLASS_RULES.am
include $(srcdir)/build-aux/GATBPS_JAVA_RULES.am
include $(srcdir)/build-aux/GATBPS_M4_RULES.am
include $(srcdir)/build-aux/GATBPS_RECIPE_MARKER.am
include $(srcdir)/build-aux/GATBPS_TAR_RULES.am
include $(srcdir)/build-aux/GATBPS_VPATH_SEARCH.am
include $(srcdir)/build-aux/GATBPS_V_NOP.am
include $(srcdir)/build-aux/GATBPS_V_PAD.am
include $(srcdir)/build-aux/GATBPS_WGET_RULES.am
include $(srcdir)/build-aux/GATBPS_XZ_RULES.am
include $(srcdir)/build-aux/cp.am
include $(srcdir)/build-aux/docker.am
include $(srcdir)/build-aux/doxygen.am
include $(srcdir)/build-aux/dvi-dist.am
include $(srcdir)/build-aux/gatbps.am
include $(srcdir)/build-aux/git.am
include $(srcdir)/build-aux/gzip.am
include $(srcdir)/build-aux/html-dist.am
include $(srcdir)/build-aux/java.am
include $(srcdir)/build-aux/javadoc-dist.am
include $(srcdir)/build-aux/javadoc.am
include $(srcdir)/build-aux/m4.am
include $(srcdir)/build-aux/pdf-dist.am
include $(srcdir)/build-aux/plaintext-dist.am
include $(srcdir)/build-aux/plaintext.am
include $(srcdir)/build-aux/ps-dist.am
include $(srcdir)/build-aux/tar.am
include $(srcdir)/build-aux/wget.am
include $(srcdir)/build-aux/xz.am

## end_includes
