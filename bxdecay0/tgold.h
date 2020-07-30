#ifndef BXDECAY0_TGOLD_H
#define BXDECAY0_TGOLD_H 1

// This project:
#include <bxdecay0/common.h>

namespace bxdecay0 {

  /// \brief Subroutine decay0_tgold determines maximum or minimum of the function f(x) in the interval [a,b] by the
  /// Gold section method.
  // Input:  a,c    - beginning and the end of the interval [a,c];
  //         b      - some point in the middle of the interval
  //         f      - name of the external function; should be as
  //                  function f(x,params), and additional parameters have
  //                  to be transmitted with help of the void pointer params;
  //         eps    - desired uncertainty of xextr determination;
  //         minmax - if minmax = 1 minimum of f(x) is searched,
  //                            = 2 maximum of f(x) is searched.
  //         params - a void pointer referencing additional parameters for f
  // Output: xextr  - x-point of extremum;
  //         fextr  - f(xextr).
  // V.Tretyak, 25.09.1985.
  void decay0_tgold(double a_,
                    double b_,
                    double c_,
                    func_type f_,
                    double eps_,
                    int minmax_,
                    double & xextr_,
                    double & fextr_,
                    void * params_ = 0);

  void decay0_tgold_o(double a_,
                      double b_,
                      double c_,
                      func_type f_,
                      double eps_,
                      int minmax_,
                      double & xextr_,
                      double & fextr_,
                      void * params_ = 0);

} // end of namespace bxdecay0

#endif // BXDECAY0_TGOLD_H
