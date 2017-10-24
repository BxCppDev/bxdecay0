// Ourselves:
#include <bxdecay0/gdrot.h>

// Standard library:
#include <cmath>

namespace bxdecay0 {

  void decay0_gdrot(double * p_,
                    const double costh_, const double sinth_,
                    const double cosph_, const double sinph_)
  {
    double p1 = p_[0];
    double p2 = p_[1];
    double p3 = p_[2];
    p_[0] =  p1*costh_*cosph_ - p2*sinph_ + p3*sinth_*cosph_;
    p_[1] =  p1*costh_*sinph_ + p2*cosph_ + p3*sinth_*sinph_;
    p_[2] = -p1*sinth_                    + p3*costh_;
    return;
  }

} // end of namespace bxdecay0
