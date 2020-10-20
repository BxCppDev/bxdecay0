#ifndef BXDECAY0_COMMON_H
#define BXDECAY0_COMMON_H

namespace bxdecay0 {

  typedef double (*func_type)(double, void *);

  typedef void (*fsub1_type)(int, const double *, double *, double *, void *);

  typedef void (*fsub2_type)(int, const double *, double *, double *, void *);

} // end of namespace bxdecay0

#endif // BXDECAY0_COMMON_H

// Local Variables: --
// mode: c++ --
// End: --
