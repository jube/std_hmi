#ifndef HMI_BITS_MAT_OPS_H
#define HMI_BITS_MAT_OPS_H

#include "mat.h"
#include "vec.h"

namespace hmi {
  template<typename T, std::size_t N>
  constexpr
  bool operator==(const mat<T, N>& lhs, const mat<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        if (lhs(i, j) != rhs(i, j)) {
          return false;
        }
      }
    }

    return true;
  }

  template<typename T, std::size_t N>
  constexpr
  bool operator!=(const mat<T, N>& lhs, const mat<T, N>& rhs) {
    return !(lhs == rhs);
  }

  template<typename T, std::size_t N>
  constexpr
  mat<T, N> operator-(const mat<T, N>& m) {
    mat<T, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i, j) = - m(i, j);
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator+(const mat<T, N>& lhs, const mat<U, N>& rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i, j) = lhs(i, j) + rhs(i, j);
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<T, N>& operator+=(mat<T, N>& lhs, const mat<U, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        lhs(i, j) += rhs(i, j);
      }
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator-(const mat<T, N>& lhs, const mat<U, N>& rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i, j) = lhs(i, j) - rhs(i, j);
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<T, N>& operator-=(mat<T, N>& lhs, const mat<U, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        lhs(i, j) -= rhs(i, j);
      }
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator*(const mat<T, N>& lhs, U rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i,j) = lhs(i,j) * rhs;
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<T, N>& operator*=(mat<T, N>& lhs, U rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        lhs(i,j) *= rhs;
      }
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator*(T lhs, const mat<U, N>& rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i,j) = lhs * rhs(i,j);
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator/(const mat<T, N>& lhs, U rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i,j) = lhs(i,j) / rhs;
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<T, N>& operator/=(mat<T, N>& lhs, U rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        lhs(i,j) /= rhs;
      }
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T,U>, N> operator/(T lhs, const mat<U, N>& rhs) {
    mat<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(i,j) = lhs / rhs(i,j);
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>, N> operator*(const mat<T, N>& lhs, const vec<U, N>& rhs) {
    vec<std::common_type_t<T,U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      std::common_type_t<T,U> value = 0;

      for (std::size_t j = 0; j < N; ++j) {
        value += lhs(i, j) * rhs[j];
      }

      result[i] = value;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>, N> operator*(const vec<T, N>& lhs, const mat<U, N>& rhs) {
    vec<std::common_type_t<T,U>, N> result;

    for (std::size_t j = 0; j < N; ++j) {
      std::common_type_t<T,U> value = 0;

      for (std::size_t i = 0; i < N; ++i) {
        value += lhs[j] * rhs(i, j);
      }

      result[j] = value;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<std::common_type_t<T, U>, N> operator*(const mat<T, N>& lhs, const mat<U, N>& rhs) {
    mat<std::common_type_t<T, U>, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        std::common_type_t<T, U> value = 0;

        for (std::size_t k = 0; k < N; ++k) {
          value += lhs(i, k) * rhs(k, j);
        }

        result(i, j) = value;
      }
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  mat<T, N>& operator*=(mat<T, N>& lhs, const mat<U, N>& rhs) {
    lhs = lhs * rhs;
    return lhs;
  }

  template<typename T, std::size_t N>
  constexpr
  mat<T, N> transpose(const mat<T, N>& m) {
    mat<T, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        result(j, i) = m(i, j);
      }
    }
  }

  template<typename T>
  constexpr
  mat<T, 2> invert(const mat<T, 2>& input) {
    mat<T, 2> result;

    result.xx = input.yy;
    result.xy = - input.xy;
    result.yx = - input.yx;
    result.yy = input.xx;

    T det = input.xx * input.yy - input.yx * input.xy;
    result /= det;
    return result;
  }

  template<typename T>
  constexpr
  mat<T, 3> invert(const mat<T, 3>& input) {
    mat<T, 3> result;

    result.xx = input.yy * input.zz - input.zy * input.yz;
    result.xy = - (input.xy * input.zz - input.zy * input.xz);
    result.xz = input.xy * input.yz - input.yy * input.xz;
    result.yx = - (input.yx * input.zz - input.zx * input.yz);
    result.yy = input.xx * input.zz - input.zx * input.xz;
    result.yz = - (input.xx * input.yz - input.yx * input.xz);
    result.zx = input.yx * input.zy - input.zx * input.yy;
    result.zy = - (input.xx * input.zy - input.zx * input.xy);
    result.zz = input.xx * input.yy - input.yx * input.xy;

    T det = input.xx * result.xx + input.xy * result.yx + input.xz * result.zx;
    result /= det;
    return result;
  }

}

#endif // HMI_BITS_MAT_OPS_H
