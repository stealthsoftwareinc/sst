/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/config_private.h>

#include <sst/sst_dynlock.h>
#include <sst/sst_dynlock.h>

/* begin_includes */

#include <sst/SST_SUCCESS.h>
#include <sst/sst_mutex.h>
#include <sst/sst_status.h>
#include <sst/sst_status_name.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* end_includes */

#if HAVE_CRYPTO_LOCK
  #include <openssl/crypto.h>
#endif

struct CRYPTO_dynlock_value {
  unsigned char magic[sizeof(unsigned int)];
  struct sst_mutex * mtx;
};

static unsigned int const dyn_mlive =  (unsigned int)0x956AB4D2U;
static unsigned int const dyn_mdead = ~(unsigned int)0x956AB4D2U;

struct CRYPTO_dynlock_value * sst_dynlock_create(
  char const * const file,
  int const line
) {
  struct CRYPTO_dynlock_value * const dyn = malloc(sizeof(*dyn));
  if (dyn == NULL) {
    (void)fprintf(stderr, "sst_dynlock_create: "
      "malloc failed at OpenSSL:%s:%d\n",
      file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  {
    sst_status const s = sst_mutex_create(&dyn->mtx, NULL);
    if (s != SST_SUCCESS) {
      free(dyn);
      (void)fprintf(stderr, "sst_dynlock_create: "
        "sst_mutex_create returned %s at OpenSSL:%s:%d\n",
        sst_status_name(s), file != NULL ? file : "?", line
      );
    }
  }
  (void)
    memcpy(
      dyn->magic,
      &dyn_mlive,
      sizeof(unsigned int)
    )
  ;
  return dyn;
}

void sst_dynlock_lock(
  int const mode,
  struct CRYPTO_dynlock_value * const dyn,
  char const * const file,
  int const line
) {
  if (dyn == NULL) {
    (void)fprintf(stderr, "sst_dynlock_lock: "
      "dyn = NULL at OpenSSL:%s:%d\n",
      file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  if (
    memcmp(
      dyn->magic,
      &dyn_mlive,
      sizeof(unsigned int)
    )
  ) {
    (void)fprintf(stderr, "sst_dynlock_lock: "
      "bad dyn magic at OpenSSL:%s:%d\n",
      file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  #if HAVE_CRYPTO_LOCK
    if (mode & CRYPTO_LOCK) {
      sst_status const s = sst_mutex_lock(dyn->mtx);
      if (s != SST_SUCCESS) {
        (void)fprintf(stderr, "sst_dynlock_lock: "
          "sst_mutex_lock returned %s at OpenSSL:%s:%d\n",
          sst_status_name(s), file != NULL ? file : "?", line
        );
        (void)fflush(stderr);
        exit(EXIT_FAILURE);
      }
    } else {
      sst_status const s = sst_mutex_unlock(dyn->mtx);
      if (s != SST_SUCCESS) {
        (void)fprintf(stderr, "sst_dynlock_lock: "
          "sst_mutex_unlock returned %s at OpenSSL:%s:%d\n",
          sst_status_name(s), file != NULL ? file : "?", line
        );
        (void)fflush(stderr);
        exit(EXIT_FAILURE);
      }
    }
  #else
    (void)mode;
    (void)fprintf(stderr, "sst_dynlock_lock: "
      "CRYPTO_LOCK is not defined\n"
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  #endif
}

void sst_dynlock_destroy(
  struct CRYPTO_dynlock_value * const dyn,
  char const * const file,
  int const line
) {
  if (dyn == NULL) {
    (void)fprintf(stderr, "sst_dynlock_destroy: "
      "dyn = NULL at OpenSSL:%s:%d\n",
      file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  if (
    memcmp(
      dyn->magic,
      &dyn_mlive,
      sizeof(unsigned int)
    )
  ) {
    (void)fprintf(stderr, "sst_dynlock_destroy: "
      "bad dyn magic at OpenSSL:%s:%d\n",
      file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  (void)sst_mutex_destroy(dyn->mtx);
  (void)
    memcpy(
      dyn->magic,
      &dyn_mdead,
      sizeof(unsigned int)
    )
  ;
  free(dyn);
}
