#ifndef HMI_BITS_VEC_OPS_H
#define HMI_BITS_VEC_OPS_H

#include <type_traits>

#include "vec.h"

namespace hmi {

  template<typename T, std::size_t N>
  bool operator==(vec<T, N> lhs, vec<T, N> rhs) {
    for (std::size_t i = 0; i < N; ++i) {
      if (lhs[i] != rhs[i]) {
        return false;
      }
    }

    return true;
  }

  template<typename T, std::size_t N>
  bool operator!=(vec<T, N> lhs, vec<T, N> rhs) {
    return !(lhs == rhs);
  }

  template<typename T, std::size_t N>
  vec<T, N> operator-(vec<T, N> v) {
    vec<T, N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = - v[i];
    }

    return result;
  }

  // add

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator+(vec<T,N> lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] + rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator+=(vec<T,N>& lhs, vec<U,N> rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] += rhs[i];
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator+(T lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs + rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator+(vec<T,N> lhs, U rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] + rhs;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator+=(vec<T,N>& lhs, U rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] += rhs;
    }

    return lhs;
  }


  // sub

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator-(vec<T,N> lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] - rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator-=(vec<T,N>& lhs, vec<U,N> rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] -= rhs[i];
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator-(T lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs - rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator-(vec<T,N> lhs, U rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] - rhs;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator-=(vec<T,N>& lhs, U rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] -= rhs;
    }

    return lhs;
  }


  // mul

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator*(vec<T,N> lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] * rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator*=(vec<T,N>& lhs, vec<U,N> rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] *= rhs[i];
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator*(T lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs * rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator*(vec<T,N> lhs, U rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] * rhs;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator*=(vec<T,N>& lhs, U rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] *= rhs;
    }

    return lhs;
  }


  // div

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator/(vec<T,N> lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] / rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator/=(vec<T,N>& lhs, vec<U,N> rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] /= rhs[i];
    }

    return lhs;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator/(T lhs, vec<U,N> rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs / rhs[i];
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<std::common_type_t<T,U>,N> operator/(vec<T,N> lhs, U rhs) noexcept {
    vec<std::common_type_t<T,U>,N> result;

    for (std::size_t i = 0; i < N; ++i) {
      result[i] = lhs[i] / rhs;
    }

    return result;
  }

  template<typename T, typename U, std::size_t N>
  constexpr
  vec<T,N>& operator/=(vec<T,N>& lhs, U rhs) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
      lhs[i] /= rhs;
    }

    return lhs;
  }


}

#endif // HMI_BITS_VEC_OPS_H
