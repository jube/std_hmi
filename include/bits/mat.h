#ifndef HMI_BITS_MAT_H
#define HMI_BITS_MAT_H

#include <cstddef>
#include <initializer_list>

namespace hmi {

  template<typename T, std::size_t N, std::size_t IndexRow, std::size_t IndexCol>
  struct mat_accessor {
    static_assert(IndexCol < N, "IndexCol should be less than N");
    static_assert(IndexRow < N, "IndexRow should be less than N");

    T data[N][N];

    constexpr operator T() const noexcept {
      return data[IndexRow][IndexCol];
    }

    constexpr mat_accessor& operator=(T value) noexcept {
      data[IndexRow][IndexCol] = value;
      return *this;
    }

    constexpr T* operator&() noexcept {
      return &data[IndexRow][IndexCol];
    }

    constexpr const T* operator&() const noexcept {
      return &data[IndexRow][IndexCol];
    }

    constexpr mat_accessor& operator++() noexcept {
      ++data[IndexRow][IndexCol];
      return *this;
    }

    constexpr mat_accessor operator++(int) noexcept {
      mat_accessor copy(*this);
      ++data[IndexRow][IndexCol];
      return copy;
    }
  };

  template<typename T, std::size_t N>
  struct mat {
    T data[N][N];

    mat() {
    }

    mat(const mat& other) = default;

    template<typename U>
    mat(const mat<U, N>& other) noexcept {
      for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
          data[i][j] = static_cast<T>(other.data[i][j]);
        }
      }
    }

    constexpr T operator()(std::size_t row, std::size_t col) const noexcept {
      return data[row][col];
    }

    constexpr T& operator()(std::size_t row, std::size_t col) noexcept {
      return data[row][col];
    }
  };

  template<typename T>
  struct mat<T, 2> {
    union {
      T data[2][2];

      mat_accessor<T, 2, 0, 0> xx;
      mat_accessor<T, 2, 0, 1> xy;
      mat_accessor<T, 2, 1, 0> yx;
      mat_accessor<T, 2, 1, 1> yy;
    };

    mat() {
    }

    constexpr mat(T xx, T xy, T yx, T yy) noexcept
    : data{ { xx, xy }, { yx, yy } }
    {

    }

    mat(const mat& other) = default;

    template<typename U>
    mat(const mat<U, 2>& other) noexcept {
      for (std::size_t i = 0; i < 2; ++i) {
        for (std::size_t j = 0; j < 2; ++j) {
          data[i][j] = static_cast<T>(other.data[i][j]);
        }
      }
    }

    constexpr T operator()(std::size_t row, std::size_t col) const noexcept {
      return data[row][col];
    }

    constexpr T& operator()(std::size_t row, std::size_t col) noexcept {
      return data[row][col];
    }
  };

  template<typename T>
  struct mat<T, 3> {
    union {
      T data[3][3];

      mat_accessor<T, 3, 0, 0> xx;
      mat_accessor<T, 3, 0, 1> xy;
      mat_accessor<T, 3, 0, 2> xz;
      mat_accessor<T, 3, 1, 0> yx;
      mat_accessor<T, 3, 1, 1> yy;
      mat_accessor<T, 3, 1, 2> yz;
      mat_accessor<T, 3, 2, 0> zx;
      mat_accessor<T, 3, 2, 1> zy;
      mat_accessor<T, 3, 2, 2> zz;
    };

    mat() {
    }

    constexpr mat(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz) noexcept
    : data{ { xx, xy, xz }, { yx, yy, yz }, { zx, zy, zz } }
    {

    }

    mat(const mat& other) = default;

    template<typename U>
    mat(const mat<U, 3>& other) noexcept {
      for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
          data[i][j] = static_cast<T>(other.data[i][j]);
        }
      }
    }

    constexpr T operator()(std::size_t row, std::size_t col) const noexcept {
      return data[row][col];
    }

    constexpr T& operator()(std::size_t row, std::size_t col) noexcept {
      return data[row][col];
    }
  };


  template<typename T>
  struct mat<T, 4> {
    union {
      T data[4][4];

      mat_accessor<T, 4, 0, 0> xx;
      mat_accessor<T, 4, 0, 1> xy;
      mat_accessor<T, 4, 0, 2> xz;
      mat_accessor<T, 4, 0, 3> xw;
      mat_accessor<T, 4, 1, 0> yx;
      mat_accessor<T, 4, 1, 1> yy;
      mat_accessor<T, 4, 1, 2> yz;
      mat_accessor<T, 4, 1, 3> yw;
      mat_accessor<T, 4, 2, 0> zx;
      mat_accessor<T, 4, 2, 1> zy;
      mat_accessor<T, 4, 2, 2> zz;
      mat_accessor<T, 4, 2, 3> zw;
      mat_accessor<T, 4, 3, 0> wx;
      mat_accessor<T, 4, 3, 1> wy;
      mat_accessor<T, 4, 3, 2> wz;
      mat_accessor<T, 4, 3, 3> ww;
    };

    mat() {
    }

    constexpr mat(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww) noexcept
    : data{ { xx, xy, xz, xw }, { yx, yy, yz, yw }, { zx, zy, zz, zw }, { wx, wy, wz, ww  } }
    {

    }

    mat(const mat& other) = default;

    template<typename U>
    mat(const mat<U, 4>& other) noexcept {
      for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < 4; ++j) {
          data[i][j] = static_cast<T>(other.data[i][j]);
        }
      }
    }

    constexpr T operator()(std::size_t row, std::size_t col) const noexcept {
      return data[row][col];
    }

    constexpr T& operator()(std::size_t row, std::size_t col) noexcept {
      return data[row][col];
    }
  };


  template<typename T>
  using mat2 = mat<T, 2>;

  using mat2f = mat2<float>;

  using mat2d = mat2<double>;

  using mat2i = mat2<int>;

  template<typename T>
  using mat3 = mat<T, 3>;

  using mat3f = mat3<float>;

  using mat3d = mat3<double>;

  using mat3i = mat3<int>;

  template<typename T>
  using mat4 = mat<T, 4>;

  using mat4f = mat4<float>;

  using mat4d = mat4<double>;

  using mat4i = mat4<int>;

} // namespace hmi

#endif // HMI_BITS_MAT_H
