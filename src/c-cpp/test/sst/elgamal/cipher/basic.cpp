//
// Copyright (C) 2012-2024 Stealth Software Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice (including
// the next paragraph) shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// SPDX-License-Identifier: MIT
//

#undef SST_COMPILE_TIME_TESTS
#define SST_COMPILE_TIME_TESTS 1

// Include first to test independence.
#include <sst/catalog/elgamal.hpp>
// Include twice to test idempotence.
#include <sst/catalog/elgamal.hpp>

//
#include <sst/catalog/SST_WITH_OPENSSL_CRYPTO.h>

#if SST_WITH_OPENSSL_CRYPTO

#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER >= 0x10100000

#define SKIP 0
#else
#define SKIP 1
#endif
#else // !SST_WITH_OPENSSL_CRYPTO
#define SKIP 1
#endif

#if !SKIP

#include <cstddef>
#include <iostream>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/bignum.hpp>
#include <sst/catalog/test_main.hpp>
#include <sst/config.h>

#include <openssl/obj_mac.h>

int main() {
  return sst::test_main([] {
    //------------------------------------------------------------------

    {
      sst::elgamal::cipher cipher(NID_secp256k1);
      cipher.keygen();

      for (std::size_t in = 0; in != 256; ++in) {
        auto ct = cipher.encrypt_small_domain(in);
        ct = ct + ct + ct;
        auto const out1 = cipher.decrypt_small_domain(ct);
        ct /= 3;
        auto const out = cipher.decrypt_small_domain(ct);
        std::cout << "in = " << in << "---> out-before = " << out1 << "---> out-after = " << out << "\n";
        SST_TEST_BOOL(out == in);
      }
    }
    
    //------------------------------------------------------------------
  });
}

#else // SKIP

#include <sst/catalog/test_skip.hpp>

int main() {
  return sst::test_skip();
}

#endif // SKIP
