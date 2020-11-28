/*
 * For the copyright information for this file, please search up the
 * directory tree for the first COPYING file.
 */

/* begin_includes */

#include <TEST_EXIT.h>
#include <ios>
#include <iostream>
#include <sst/fs/mkdir_p.h>
#include <stdexcept>
#include <string>

/* end_includes */

// Make sure sst::fs::mkdir_p(path) returns expect.
template<class Line>
static bool test(
  std::string const & file,
  Line const line,
  std::string const & path,
  bool const expect
) {
  try {
    bool const actual = sst::fs::mkdir_p(path);
    if (actual == expect) {
      return true;
    }
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::fs::mkdir_p(\"" << path << "\") "
      << "returned " << actual << " "
      << "(expected " << expect << ")"
      << std::endl;
    ;
    return false;
  } catch (std::exception const & e) {
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::fs::mkdir_p(\"" << path << "\") "
      << "threw an exception "
      << "(expected " << expect << "): "
      << e.what()
      << std::endl;
    ;
    throw;
  } catch (...) {
    std::cerr
      << std::boolalpha
      << file << ":" << std::to_string(line) << ": "
      << "sst::fs::mkdir_p(\"" << path << "\") "
      << "threw an exception "
      << "(expected " << expect << ")"
      << std::endl;
    ;
    throw;
  }
}

#define test(path, expect) test(__FILE__, __LINE__, path, expect)

int main(
) {
  try {
    bool pass = true;
    pass &= test(".", false);
    pass &= test("..", false);
    return pass ? TEST_EXIT_PASS : TEST_EXIT_FAIL;
  } catch (...) {
    return TEST_EXIT_ERROR;
  }
}
