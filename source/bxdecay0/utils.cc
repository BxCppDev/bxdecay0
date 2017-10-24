
// Ourselves:
#include <bxdecay0/utils.h>

// Third party:
// // - Boost:
// #include <boost/algorithm/string/predicate.hpp>

namespace bxdecay0 {

  bool name_starts_with(const std::string & name_,
                        const std::string & prefix_)
  {
    // Remove Boost dependency:
    // return boost::algorithm::starts_with(name_, prefix_);
    std::size_t len = prefix_.size();
    if (name_.size() < len) return false;
    if (name_.substr(0, prefix_.size()) == prefix_) return true;
    return false;
  }


} // end of namespace bxdecay0
