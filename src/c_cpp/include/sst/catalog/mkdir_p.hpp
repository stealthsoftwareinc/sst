//
// For the copyright information for this file, please search up the
// directory tree for the first COPYING file.
//

#ifndef SST_CATALOG_MKDIR_P_HPP
#define SST_CATALOG_MKDIR_P_HPP

//----------------------------------------------------------------------
// All platforms
//----------------------------------------------------------------------

#include <sst/catalog/SST_PUBLIC_CPP_FUNCTION.hpp>
#include <sst/config.h>
#include <string>

namespace sst {

SST_PUBLIC_CPP_FUNCTION
bool mkdir_p(std::string const & path);

// DEPRECATED
namespace fs {
using sst::mkdir_p;
} // namespace fs

} // namespace sst

//----------------------------------------------------------------------
// POSIX only
//----------------------------------------------------------------------
#if SST_HAVE_POSIX

//----------------------------------------------------------------------
// Windows only
//----------------------------------------------------------------------
#elif SST_HAVE_WINDOWS

//----------------------------------------------------------------------
#endif

#endif // SST_CATALOG_MKDIR_P_HPP
