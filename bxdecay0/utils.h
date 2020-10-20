#ifndef BXDECAY0_UTILS_H
#define BXDECAY0_UTILS_H

// Standard library:
#include <iostream>
#include <map>
#include <string>

namespace bxdecay0 {

  const std::map<std::string, bool> & traces();

  bool is_trace(const std::string & label_);

  bool name_starts_with(const std::string & name_, const std::string & prefix_);

  /// 3D-vector
  ///
  ///  v = ( x )
  ///      ( y )
  ///      ( z )
  struct vector3
  {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };

  double dot(const vector3 & v1_, const vector3 & v2_);

  void print(const vector3 & v_, std::ostream & out_);

  vector3 make_vector3(const double x_, const double y_, const double z_);

  /// 3D- matrix
  ///
  ///  m = ( xx yx zx )
  ///      ( xy yy zy )
  ///      ( xz yz zz )
  struct matrix3
  {
    double xx = 1.0;
    double xy = 0.0;
    double xz = 0.0; // Column 0
    double yx = 0.0;
    double yy = 1.0;
    double yz = 0.0; // Column 1
    double zx = 0.0;
    double zy = 0.0;
    double zz = 1.0; // Column 2
  };

  void print(const matrix3 & m_, std::ostream & out_);

  matrix3 make_matrix3(const vector3 & colx_, const vector3 & coly_, const vector3 & colz_);

  matrix3 transpose(const matrix3 & m_);

  /// Multiply a matrix with a matrix
  void multiply(const matrix3 & m1_, const matrix3 & m2_, matrix3 & mr_);

  /// Multiplication operator between a matrix and a matrix
  matrix3 operator*(const matrix3 & m1_, const matrix3 & m2_);

  /// Multiply a matrix with a vector
  void multiply(const matrix3 & m_, const vector3 & v_, vector3 & vr_);

  /// Multiplication operator between a matrix and a vector
  vector3 operator*(const matrix3 & m_, const vector3 & v_);

  /// Rotate a 3D-vector through ZYZ Euler angles
  vector3 rotate_zyz(const vector3 & p_, const double phi_, const double theta_ = 0.0, const double psi_ = 0.0);

} // end of namespace bxdecay0

#endif // BXDECAY0_UTILS_H

// Local Variables: --
// mode: c++ --
// End: --
