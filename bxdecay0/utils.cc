// Copyright 2011-2017 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <bxdecay0/utils.h>

// Standard library:
#include <cmath>
#include <stdexcept>

namespace bxdecay0 {

  const std::map<std::string, bool> & traces()
  {
    static bool devel = false;
    // devel = true;
    static std::map<std::string, bool> _t;
    if (_t.empty()) {
      if (devel) {
        std::cerr << "[devel] bxdecay0::traces: "
                  << "Populating trace map..." << std::endl;
      }
      _t["bxdecay0"] = false;
      _t["genbbsub"] = false;
      _t["bb"]       = false;
      _t["gauss"]    = false;
      _t["fe12"]     = false;
      _t["fermi"]    = false;
      {
        const char * env_key = "BXDECAY0_TRACE";
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          _t["bxdecay0"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_GENBBSUB";
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          _t["genbbsub"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_BB";
        if (devel) {
          std::cerr << "[devel] bxdecay0::traces: BXDECAY0_TRACE_BB='" << std::getenv(env_key) << "'" << std::endl;
        }
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          if (devel) {
            std::cerr << "[devel] bxdecay0::traces: "
                      << "Activate BB trace." << std::endl;
          }
          _t["bb"] = true;
        } else {
          if (devel) {
            std::cerr << "[devel] bxdecay0::traces: "
                      << "Don't activate BB trace." << std::endl;
          }
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_GAUSS";
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          _t["gauss"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_FE12";
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          _t["fe12"] = true;
        }
      }
      {
        const char * env_key = "BXDECAY0_TRACE_FERMI";
        if ((std::getenv(env_key) != nullptr) && std::string(std::getenv(env_key)) == "1") {
          _t["fermi"] = true;
        }
      }
      for (const auto & p : _t) {
        if (devel) {
          std::cerr << "[devel] bxdecay0::traces: "
                    << "Topic '" << p.first << "' -> trace = " << std::boolalpha << p.second << std::endl;
        }
      }
    }
    return _t;
  }

  bool is_trace(const std::string & label_)
  {
    const std::map<std::string, bool> & tr = traces();
    if (tr.count(label_) != 0U) {
      bool t = tr.find(label_)->second;
      if (t) {
        return true;
      }
    }
    return false;
  }

  bool name_starts_with(const std::string & name_, const std::string & prefix_)
  {
    std::size_t len = prefix_.size();
    if (name_.size() < len) {
      return false;
    }
    return name_.substr(0, prefix_.size()) == prefix_;
  }

  double dot(const vector3 & v1_, const vector3 & v2_)
  {
    return v1_.x * v2_.x + v1_.y * v2_.y + v1_.z * v2_.z;
  }

  void print(const vector3 & v_, std::ostream & out_)
  {
    out_ << v_.x << ' ' << v_.y << ' ' << v_.z;
    return;
  }

  vector3 make_vector3(const double x_, const double y_, const double z_)
  {
    vector3 v;
    v.x = x_;
    v.y = y_;
    v.z = z_;
    return v;
  }

  void print(const matrix3 & m_, std::ostream & out_)
  {
    out_ << '[' << m_.xx << ' ' << m_.yx << ' ' << m_.zx << ']' << '\n';
    out_ << '[' << m_.xy << ' ' << m_.yy << ' ' << m_.zy << ']' << '\n';
    out_ << '[' << m_.xz << ' ' << m_.yz << ' ' << m_.zz << ']' << '\n';
    return;
  }

  matrix3 make_matrix3(const vector3 & colx_, const vector3 & coly_, const vector3 & colz_)
  {
    matrix3 m;
    m.xx = colx_.x;
    m.xy = colx_.y;
    m.xz = colx_.z;
    m.yx = coly_.x;
    m.yy = coly_.y;
    m.yz = coly_.z;
    m.zx = colz_.x;
    m.zy = colz_.y;
    m.zz = colz_.z;
    return m;
  }

  matrix3 transpose(const matrix3 & m_)
  {
    matrix3 m;
    m.xx = m_.xx;
    m.xy = m_.yx;
    m.xz = m_.zx;
    m.yx = m_.xy;
    m.yy = m_.yy;
    m.yz = m_.zy;
    m.zx = m_.xz;
    m.zy = m_.yz;
    m.zz = m_.zz;
    return m;
  }

  void multiply(const matrix3 & m1_, const matrix3 & m2_, matrix3 & mr_)
  {
    vector3 l1x = make_vector3(m1_.xx, m1_.yx, m1_.zx);
    vector3 l1y = make_vector3(m1_.xy, m1_.yy, m1_.zy);
    vector3 l1z = make_vector3(m1_.xz, m1_.yz, m1_.zz);
    vector3 c2x = make_vector3(m2_.xx, m2_.xy, m2_.xz);
    vector3 c2y = make_vector3(m2_.yx, m2_.yy, m2_.yz);
    vector3 c2z = make_vector3(m2_.zx, m2_.zy, m2_.zz);

    mr_.xx = dot(l1x, c2x);
    mr_.xy = dot(l1y, c2x);
    mr_.xz = dot(l1z, c2x);

    mr_.yx = dot(l1x, c2y);
    mr_.yy = dot(l1y, c2y);
    mr_.yz = dot(l1z, c2y);

    mr_.zx = dot(l1x, c2z);
    mr_.zy = dot(l1y, c2z);
    mr_.zz = dot(l1z, c2z);

    return;
  }

  matrix3 operator*(const matrix3 & m1_, const matrix3 & m2_)
  {
    matrix3 mr;
    multiply(m1_, m2_, mr);
    return mr;
  }

  void multiply(const matrix3 & m_, const vector3 & v_, vector3 & vr_)
  {
    vr_.x = m_.xx * v_.x + m_.yx * v_.y + m_.zx * v_.z;
    vr_.y = m_.xy * v_.x + m_.yy * v_.y + m_.zy * v_.z;
    vr_.z = m_.xz * v_.x + m_.yz * v_.y + m_.zz * v_.z;
    return;
  }

  vector3 operator*(const matrix3 & m_, const vector3 & v_)
  {
    vector3 vr;
    multiply(m_, v_, vr);
    return vr;
  }

  vector3 rotate_zyz(const vector3 & p_, const double phi_, const double theta_, const double psi_)
  {
    // R1 (Z-axis)
    //  cos(phi)  -sin(phi)    0
    //  sin(phi)   cos(phi)    0
    //  0                 0    1
    matrix3 R1z = make_matrix3(make_vector3(std::cos(phi_), std::sin(phi_), 0.0),
                               make_vector3(-std::sin(phi_), std::cos(phi_), 0.0),
                               make_vector3(0.0, 0.0, 1.0));
    // std::cerr << "[devel] R1z = \n";
    // print(R1z, std::cerr);
    // R2 (Y'-axis)
    //  cos(theta)  0    sin(theta)
    //  0           1           0
    //  -sin(theta) 0    cos(theta)
    matrix3 R2y = make_matrix3(make_vector3(std::cos(theta_), 0.0, -std::sin(theta_)),
                               make_vector3(0.0, 1.0, 0.0),
                               make_vector3(std::sin(theta_), 0.0, std::cos(theta_)));
    // std::cerr << "[devel] R2y = \n";
    // print(R2y, std::cerr);
    // R3 (Z''-axis)
    //  cos(psi)  -sin(psi)    0
    //  sin(psi)   cos(psi)    0
    //  0                 0    1
    matrix3 R3z = make_matrix3(make_vector3(std::cos(psi_), std::sin(psi_), 0.0),
                               make_vector3(-std::sin(psi_), std::cos(psi_), 0.0),
                               make_vector3(0.0, 0.0, 1.0));
    // std::cerr << "[devel] R3z = \n";
    // print(R3z, std::cerr);
    vector3 p1 = R3z * p_;
    vector3 p2 = R2y * p1;
    vector3 p3 = R1z * p2;
    return p3;
  }

} // end of namespace bxdecay0
