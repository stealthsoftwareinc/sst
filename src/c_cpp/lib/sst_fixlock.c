/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

#include <sst/config_private.h>

#include <sst/sst_fixlock.h>
#include <sst/sst_fixlock.h>

/* begin_includes */

#include <sst/SST_FALSE.h>
#include <sst/SST_INVALID_ARGUMENT.h>
#include <sst/SST_INVALID_OPERATION.h>
#include <sst/SST_OUT_OF_MEMORY.h>
#include <sst/SST_SUCCESS.h>
#include <sst/SST_TRUE.h>
#include <sst/sst_bool.h>
#include <sst/sst_mutex.h>
#include <sst/sst_status.h>
#include <sst/sst_status_name.h>
#include <stdio.h>
#include <stdlib.h>

/* end_includes */

#if HAVE_CRYPTO_LOCK
  #include <openssl/crypto.h>
#endif

/*
 * Note that create_initiated and friends are not thread safe. If no
 * calls to sst_fixlock_create nor sst_fixlock_destroy overlap other
 * calls to sst_fixlock_{create,lock,destroy}, then the calling order
 * error checking is perfect. Otherwise, the behavior is undefined, but
 * it should still be good in practice. Note that atomics could be used
 * to always give perfect checking.
 */

static sst_bool create_initiated = SST_FALSE;
static sst_bool create_succeeded = SST_FALSE;
static struct sst_mutex * * mutexes = NULL;
static int mutex_count = 0;
static int mutex_touch = 0;

sst_status sst_fixlock_create(
  int const n
) {
  if (create_initiated) {
    return SST_INVALID_OPERATION;
  }
  create_initiated = SST_TRUE;
  if (n < 0) {
    return SST_INVALID_ARGUMENT;
  }
  if (n == 0) {
    create_succeeded = SST_TRUE;
    return SST_SUCCESS;
  }
  if (n + (size_t)0 > (size_t)-1 / sizeof(*mutexes)) {
    return SST_OUT_OF_MEMORY;
  }
  mutexes = malloc(n * sizeof(*mutexes));
  if (mutexes == NULL) {
    return SST_OUT_OF_MEMORY;
  }
  {
    int i;
    for (i = 0; i != n; ++i) {
      sst_status const s = sst_mutex_create(&mutexes[i], NULL);
      if (s != SST_SUCCESS) {
        {
          int j;
          for (j = 0; j != i; ++j) {
            (void)sst_mutex_destroy(mutexes[j]);
          }
        }
        free(mutexes);
        mutexes = NULL;
        return s;
      }
    }
  }
  mutex_count = n;
  create_succeeded = SST_TRUE;
  return SST_SUCCESS;
}

void sst_fixlock_lock(
  int const mode,
  int const i,
  char const * const file,
  int const line
) {
  if (!create_succeeded) {
    (void)fprintf(stderr, "sst_fixlock_lock: "
      "sst_fixlock_create has not succeeded\n"
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  if (mutex_touch < 0) {
    (void)fprintf(stderr, "sst_fixlock_lock: "
      "sst_fixlock_destroy has been initiated\n"
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  if (i < 0) {
    (void)fprintf(stderr, "sst_fixlock_lock: "
      "i = %d < 0 at OpenSSL:%s:%d\n",
      i, file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  if (i >= mutex_count) {
    (void)fprintf(stderr, "sst_fixlock_lock: "
      "i = %d >= mutex_count = %d at OpenSSL:%s:%d\n",
      i, mutex_count, file != NULL ? file : "?", line
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  }
  #if HAVE_CRYPTO_LOCK
    if (mode & CRYPTO_LOCK) {
      sst_status const s = sst_mutex_lock(mutexes[i]);
      if (s != SST_SUCCESS) {
        (void)fprintf(stderr, "sst_fixlock_lock: "
          "sst_mutex_lock returned %s at OpenSSL:%s:%d\n",
          sst_status_name(s), file != NULL ? file : "?", line
        );
        (void)fflush(stderr);
        exit(EXIT_FAILURE);
      }
    } else {
      sst_status const s = sst_mutex_unlock(mutexes[i]);
      if (s != SST_SUCCESS) {
        (void)fprintf(stderr, "sst_fixlock_lock: "
          "sst_mutex_unlock returned %s at OpenSSL:%s:%d\n",
          sst_status_name(s), file != NULL ? file : "?", line
        );
        (void)fflush(stderr);
        exit(EXIT_FAILURE);
      }
    }
  #else
    (void)mode;
    (void)fprintf(stderr, "sst_fixlock_lock: "
      "CRYPTO_LOCK is not defined\n"
    );
    (void)fflush(stderr);
    exit(EXIT_FAILURE);
  #endif
}

sst_status sst_fixlock_destroy(
  void
) {
  if (mutex_touch != 0) {
    return SST_INVALID_OPERATION;
  }
  mutex_touch = -1;
  if (!create_succeeded) {
    return SST_INVALID_OPERATION;
  }
  if (mutex_count == 0) {
    return SST_SUCCESS;
  }
  {
    sst_status s = SST_SUCCESS;
    {
      int i;
      for (i = 0; i != mutex_count; ++i) {
        sst_status const t = sst_mutex_destroy(mutexes[i]);
        if (t != SST_SUCCESS && s == SST_SUCCESS) {
          s = t;
        }
      }
    }
    free(mutexes);
    mutexes = NULL;
    mutex_count = 0;
    return s;
  }
}
