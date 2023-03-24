#
# Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice (including
# the next paragraph) shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# SPDX-License-Identifier: MIT
#

Name: sst-sst
Version: %{PACKAGE_VERSION_RPM_V}
Release: %{PACKAGE_VERSION_RPM_R}%{?dist}
Summary: Basic utilities
License: Proprietary
Source0: sst-%{PACKAGE_VERSION}.tar.gz

BuildRequires: autoconf
BuildRequires: automake
BuildRequires: bc
BuildRequires: coreutils
BuildRequires: devtoolset-11
BuildRequires: gawk
BuildRequires: gmp
BuildRequires: gmp-devel
BuildRequires: java-1.7.0-openjdk
BuildRequires: java-1.7.0-openjdk-devel
BuildRequires: libtool
BuildRequires: m4
BuildRequires: nettle
BuildRequires: nettle-devel
BuildRequires: sed
BuildRequires: tar

Requires(post): glibc
Requires(postun): glibc
Requires: gmp
Requires: nettle

%description
Basic utilities.

%prep
%setup -n sst-%{PACKAGE_VERSION}

%build
./configure \
  --bindir='%{_bindir}' \
  --datadir='%{_datadir}' \
  --includedir='%{_includedir}' \
  --infodir='%{_infodir}' \
  --libdir='%{_libdir}' \
  --libexecdir='%{_libexecdir}' \
  --prefix='%{_prefix}' \
  --sbindir='%{_sbindir}' \
  CFLAGS='%{optflags}' \
  CPPFLAGS='-DNDEBUG' \
  LDFLAGS='%{__global_ldflags}' \
;
make

%install
make DESTDIR='%{buildroot}' install

%files
%defattr(-, root, root, -)
%{_bindir}/*
%{_datadir}/*
%{_includedir}/*
%{_libdir}/*

%post
/sbin/ldconfig

%postun
/sbin/ldconfig
