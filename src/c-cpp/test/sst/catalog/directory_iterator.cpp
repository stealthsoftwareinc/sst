//
// Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
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
#include <sst/catalog/posix_directory_iterator.hpp>
// Include twice to test idempotence.
#include <sst/catalog/posix_directory_iterator.hpp>
//

#include <sst/catalog/SST_WITH_POSIX.h>

#if SST_WITH_POSIX

#include <string>

#include <sst/catalog/SST_TEST_BOOL.hpp>
#include <sst/catalog/SST_TEST_SHOW.hpp>
#include <sst/catalog/mkdir_p.hpp>
#include <sst/catalog/mktemp_d.hpp>
#include <sst/catalog/test_main.hpp>

int main() {
  return sst::test_main([] {
    ;

    //------------------------------------------------------------------

    {

      std::string const tmp = sst::mktemp_d();
      sst::mkdir_p(tmp + "/foo/bar");
      std::string d;
      sst::posix_directory_iterator i;

      SST_TEST_BOOL((d = "/foo",
                     i = sst::posix_directory_iterator(tmp + d),
                     i.prefix() == tmp.size() + d.size() + 1),
                    SST_TEST_SHOW((tmp.size())),
                    SST_TEST_SHOW((d.size())),
                    SST_TEST_SHOW((i.prefix())));

      SST_TEST_BOOL((d = "/foo/",
                     i = sst::posix_directory_iterator(tmp + d),
                     i.prefix() == tmp.size() + d.size()),
                    SST_TEST_SHOW((tmp.size())),
                    SST_TEST_SHOW((d.size())),
                    SST_TEST_SHOW((i.prefix())));

      SST_TEST_BOOL((d = "/foo//",
                     i = sst::posix_directory_iterator(tmp + d),
                     i.prefix() == tmp.size() + d.size()),
                    SST_TEST_SHOW((tmp.size())),
                    SST_TEST_SHOW((d.size())),
                    SST_TEST_SHOW((i.prefix())));

      SST_TEST_BOOL((d = "/foo///",
                     i = sst::posix_directory_iterator(tmp + d),
                     i.prefix() == tmp.size() + d.size()),
                    SST_TEST_SHOW((tmp.size())),
                    SST_TEST_SHOW((d.size())),
                    SST_TEST_SHOW((i.prefix())));

    } //

    //------------------------------------------------------------------
  });
}

#else // !SST_WITH_POSIX

#include <sst/catalog/test_skip.hpp>

int main() {
  return sst::test_skip();
}

#endif // !SST_WITH_POSIX
