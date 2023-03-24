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

FROM registry.stealthsoftwareinc.com/stealth/builder-images/rhel:7

RUN yum -y install \
  centos-release-scl \
  epel-release \
;

RUN yum -y install \
  autoconf \
  automake \
  bc \
  coreutils \
  devtoolset-11 \
  gawk \
  gmp \
  gmp-devel \
  java-1.7.0-openjdk \
  java-1.7.0-openjdk-devel \
  libtool \
  m4 \
  nettle \
  nettle-devel \
  perl-devel \
  redhat-rpm-config \
  rpm-build \
  scl-utils \
  sed \
  tar \
;

COPY texinfo-6.3.tar.xz /x/

RUN : \
  && cd /x \
  && tar xf texinfo-6.3.tar.xz \
  && cd texinfo-6.3 \
  && ./configure \
  && make \
  && make install \
;

ARG ARG_PACKAGE_VERSION
ARG ARG_PACKAGE_VERSION_RPM_R
ARG ARG_PACKAGE_VERSION_RPM_V

COPY sst-*.tar.* /root/rpmbuild/SOURCES/
COPY sst.spec /root/rpmbuild/SPECS/

RUN . scl_source enable devtoolset-11 && rpmbuild -ba \
  -D "PACKAGE_VERSION $ARG_PACKAGE_VERSION" \
  -D "PACKAGE_VERSION_RPM_R $ARG_PACKAGE_VERSION_RPM_R" \
  -D "PACKAGE_VERSION_RPM_V $ARG_PACKAGE_VERSION_RPM_V" \
  /root/rpmbuild/SPECS/sst.spec \
;

RUN : \
  && mkdir /x/out \
  && cp /root/rpmbuild/RPMS/*/*.rpm /x/out \
  && cp /root/rpmbuild/SRPMS/*.rpm /x/out \
;
