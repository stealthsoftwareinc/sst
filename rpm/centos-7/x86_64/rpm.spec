#
# For the copyright information for this file, please search up the
# directory tree for the first COPYING file.
#

#
# The following files are very similar:
#
#   rpm/centos-7/x86_64/rpm.spec
#   rpm/rhel-7/x86_64/rpm.spec
#
# You should keep these files in sync.
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
BuildRequires: gawk
BuildRequires: gcc
BuildRequires: gcc-c++
BuildRequires: gmp
BuildRequires: gmp-devel
BuildRequires: java-1.7.0-openjdk
BuildRequires: java-1.7.0-openjdk-devel
BuildRequires: libtool
BuildRequires: make
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
%{_datadir}/*
%{_includedir}/*
%{_libdir}/*

%post
/sbin/ldconfig

%postun
/sbin/ldconfig
