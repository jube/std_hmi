#ifndef HMI_BITS_VEC_H
#define HMI_BITS_VEC_H

#include <cstddef>
#include <initializer_list>

namespace hmi {

  template<typename T, std::size_t N, std::size_t Index>
  struct vec_accessor {
    static_assert(Index < N, "Index should be less than N");

    T data[N];

    constexpr operator T() const noexcept {
      return data[Index];
    }

    constexpr vec_accessor& operator=(T value) noexcept {
      data[Index] = value;
      return *this;
    }

    constexpr T* operator&() noexcept {
      return &data[Index];
    }

    constexpr const T* operator&() const noexcept {
      return &data[Index];
    }

    constexpr vec_accessor& operator++() noexcept {
      ++data[Index];
      return *this;
    }

    constexpr vec_accessor operator++(int) noexcept {
      vec_accessor copy(*this);
      ++data[Index];
      return copy;
    }

  };

  template<typename T, std::size_t N>
  struct vec {
    T data[N];

    vec() {
    }

    vec(const vec& other) = default;

    template<typename U>
    vec(const vec<U, N>& other) noexcept
    {
      for (std::size_t i = 0; i < N; ++i) {
        data[i] = static_cast<T>(other.data[i]);
      }
    }

    constexpr T operator[](std::size_t i) const noexcept {
      return data[i];
    }

    constexpr T& operator[](std::size_t i) noexcept {
      return data[i];
    }
  };

  template<typename T>
  struct vec<T, 2> {
    union {
      T data[2];

      vec_accessor<T, 2, 0> x;
      vec_accessor<T, 2, 1> y;

      vec_accessor<T, 2, 0> width;
      vec_accessor<T, 2, 1> height;
    };

    vec() {
    }

    constexpr vec(T m1, T m2) noexcept
    : data{ m1, m2 }
    {

    }

    vec(const vec& other) = default;

    template<typename U>
    vec(const vec<U, 2>& other) noexcept
    : data{ static_cast<T>(other[0]), static_cast<T>(other[1]) }
    {

    }

    constexpr T operator[](std::size_t i) const noexcept {
      return data[i];
    }

    constexpr T& operator[](std::size_t i) noexcept {
      return data[i];
    }

  };

  template<typename T>
  struct vec<T, 3> {
    union {
      T data[3];

      vec_accessor<T, 3, 0> x;
      vec_accessor<T, 3, 1> y;
      vec_accessor<T, 3, 1> z;

      vec_accessor<T, 3, 0> r;
      vec_accessor<T, 3, 1> g;
      vec_accessor<T, 3, 1> b;
    };

    vec() {
    }

    constexpr vec(T m1, T m2, T m3) noexcept
    : data{ m1, m2, m3 }
    {

    }

    vec(const vec& other) = default;

    template<typename U>
    vec(const vec<U, 3>& other) noexcept {
      for (std::size_t i = 0; i < 3; ++i) {
        data[i] = static_cast<T>(other.data[i]);
      }
    }

    constexpr T operator[](std::size_t i) const noexcept {
      return data[i];
    }

    constexpr T& operator[](std::size_t i) noexcept {
      return data[i];
    }
  };

  template<typename T>
  struct vec<T, 4> {
    union {
      T data[4];

      vec_accessor<T, 4, 0> x;
      vec_accessor<T, 4, 1> y;
      vec_accessor<T, 4, 1> z;
      vec_accessor<T, 4, 1> w;

      vec_accessor<T, 4, 0> r;
      vec_accessor<T, 4, 1> g;
      vec_accessor<T, 4, 1> b;
      vec_accessor<T, 4, 1> a;
    };

    vec() {
    }

    constexpr vec(T m1, T m2, T m3, T m4) noexcept
    : data{ m1, m2, m3, m4 }
    {

    }

    vec(const vec& other) = default;

    template<typename U>
    vec(const vec<U, 4>& other) noexcept
    {
      for (std::size_t i = 0; i < 4; ++i) {
        data[i] = static_cast<T>(other.data[i]);
      }
    }

    constexpr T operator[](std::size_t i) const noexcept {
      return data[i];
    }

    constexpr T& operator[](std::size_t i) noexcept {
      return data[i];
    }
  };


  template<typename T>
  using vec2 = vec<T, 2>;

  using vec2f = vec2<float>;

  using vec2d = vec2<double>;

  using vec2i = vec2<int>;


  template<typename T>
  using vec3 = vec<T, 3>;

  using vec3f = vec3<float>;

  using vec3d = vec3<double>;

  using vec3i = vec3<int>;


  template<typename T>
  using vec4 = vec<T, 4>;

  using vec4f = vec4<float>;

  using vec4d = vec4<double>;

  using vec4i = vec4<int>;


  using color3f = vec3f;

  using color4f = vec4f;

} // namespace hmi

#endif // HMI_BITS_VEC_H

