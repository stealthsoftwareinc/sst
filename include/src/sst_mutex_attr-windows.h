/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#ifndef SRC_SST_MUTEX_ATTR_WINDOWS_H
#define SRC_SST_MUTEX_ATTR_WINDOWS_H

struct sst_mutex_attr {
  unsigned char magic[sizeof(unsigned int)];
};

#endif
