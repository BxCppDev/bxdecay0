#ifndef BXDECAY0_UTILS_H
#define BXDECAY0_UTILS_H

// Standard library:
#include <string>
#include <map>

namespace bxdecay0 {

  const std::map<std::string, bool> & traces();

  bool is_trace(const std::string & label_);

  bool name_starts_with(const std::string & name_,
                        const std::string & prefix_);

} // end of namespace bxdecay0

#endif // BXDECAY0_UTILS_H

// Local Variables: --
// mode: c++ --
// End: --
