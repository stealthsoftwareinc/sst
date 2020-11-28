#
# For the copyright information for this file, please search up the
# directory tree for the first COPYING file.
#

#
# The following files are very similar:
#
#   rpm/centos-7/x86_64/rpm.Dockerfile
#   rpm/rhel-7/x86_64/rpm.Dockerfile
#
# You should keep these files in sync.
#

FROM centos:7

RUN yum -y install \
  autoconf \
  automake \
  bc \
  coreutils \
  gawk \
  gcc \
  gcc-c++ \
  gmp \
  gmp-devel \
  java-1.7.0-openjdk \
  java-1.7.0-openjdk-devel \
  libtool \
  make \
  nettle \
  nettle-devel \
  perl-devel \
  redhat-rpm-config \
  rpm-build \
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
COPY rpm.spec /root/rpmbuild/SPECS/

RUN rpmbuild -ba \
  -D "PACKAGE_VERSION $ARG_PACKAGE_VERSION" \
  -D "PACKAGE_VERSION_RPM_R $ARG_PACKAGE_VERSION_RPM_R" \
  -D "PACKAGE_VERSION_RPM_V $ARG_PACKAGE_VERSION_RPM_V" \
  /root/rpmbuild/SPECS/rpm.spec \
;

CMD sh
