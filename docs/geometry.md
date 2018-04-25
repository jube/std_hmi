# Small Vectors and Matrices

## Introduction

### Rationale

The idea is to provide simple vector and matrix implementations with a set of useful operators and free functions.

Simple means: optimized for 2, 3 and 4 dimensions, no swizzling, only square matrices.

### Prior art

Libraries with the same purpose:

- [OpenGL Mathematics (GLM)](https://glm.g-truc.net/0.9.8/index.html)
- [Boost QVM: Quaternions, Vectors, Matrices](http://boostorg.github.io/qvm/)
- [linalg](https://github.com/sgorsten/linalg)

Some articles about vector/matrix libraries:

- [On Vector Math Libraries - Nathan Reed](http://www.reedbeta.com/blog/on-vector-math-libraries/)
- [SIMD Scalar Accessor. How to make the type system work for you. - t0rakka](https://t0rakka.silvrback.com/simd-scalar-accessor)

## Vector types

### Rationale

The type for vectors is named `vec` (as `std::vector` is something else). It has two template parameters: the type `T` of the elements and the number `N` of elements. The following table shows the name of the base vector type in different libraries.

| Library | Name for vector type | References |
|---------|----------------------|------------|
| glm     | `vec`                | [ref](https://github.com/g-truc/glm/blob/master/glm/detail/qualifier.hpp#L36) |
| QVM     | `vec`                | [ref](http://boostorg.github.io/qvm/vec.html) |
| linalg  | `vec`                | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L64) |
| hmi     | `vec`                |            |

Specialization are defined for `N` equals to 2, 3 and 4 with special accessors for the fields of the vector.

Specializations for `N` = 2 should provide `x`/`y`, `u`/`v`, `s`/`t`, `width`/`height` accessors.

| Library | Accessors for ̀`N` = 2                       | References |
|---------|---------------------------------------------|------------|
| glm     | `x`/`y`, `r`/`g`, `s`/`t`                   | [ref](https://github.com/g-truc/glm/blob/master/glm/detail/type_vec2.hpp#L70) |
| QVM     | free functions `X`/`Y`                      | [ref](http://boostorg.github.io/qvm/accessing_vector_elements.html) |
| linalg  | `x`/`y`                                     | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L65) |
| hmi     | `x`/`y`, `u`/`v`, `s`/`t`, `width`/`height` |            |

Specializations for `N` = 3 should provide `x`/`y`/`z`, `r`/`g`/`b` accessors.

| Library | Accessors for ̀`N` = 3                 | References |
|---------|---------------------------------------|------------|
| glm     | `x`/`y`/`z`, `r`/`g`/`b`, `s`/`t`/`p` | [ref](https://github.com/g-truc/glm/blob/master/glm/detail/type_vec3.hpp#L69) |
| QVM     | free functions `X`/`Y`/`Z`            | [ref](http://boostorg.github.io/qvm/accessing_vector_elements.html) |
| linalg  | `x`/`y`/`z`                           | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L77) |
| hmi     | `x`/`y`/`z`, `r`/`g`/`b`              |            |

Specializations for `N` = 4 should provide `x`/`y`/`z`/`w`, `r`/`g`/`b`/`a` accessors.

| Library | Accessors for ̀`N` = 4                             | References |
|---------|---------------------------------------------------|------------|
| glm     | `x`/`y`/`z`/`w`, `r`/`g`/`b`/`a`, `s`/`t`/`p`/`q` | [ref](https://github.com/g-truc/glm/blob/master/glm/detail/type_vec4.hpp#L71) |
| QVM     | free functions `X`/`Y`/`Z`/`W`                    | [ref](http://boostorg.github.io/qvm/accessing_vector_elements.html) |
| linalg  | `x`/`y`/`z`                                       | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L94) |
| hmi     | `x`/`y`/`z`/`w`, `r`/`g`/`b`/`a`                  |            |

Type aliases are defined for specialisations with `N` equals to 2, 3 and 4, and `T` equals to `float`, `double` and `int`, with the name `vecNt` where `t` is the first letter of type `T`. The following table shows the conventions for types aliases in different libraries (`T` should be replaced by the whole type name, `t` by the type initial and `N` by the dimension).

| Library | Aliases naming                  | References |
|---------|---------------------------------|------------|
| glm     | `tvecN` (and `vecN` for floats) | [ref](https://glm.g-truc.net/0.9.8/api/a00157.html) |
| QVM     |                                 |            |
| linalg  | `TN`                            | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L415) |
| hmi     | `vecNt`                         |            |

Type aliases are provided for color types: `color3f` (alias of `vec3f`) and `color4f` (alias of `vec4f`). No tag is used, this is the same type with a different name. Tagging would prevent mixing vectors and colors.

### Synopsis

```cpp

template<typename T, std::size_t N>
struct vec {
  T data[N];

  vec();
  vec(const vec& other) = default;

  template<typename U>
  vec(const vec<U, N>& other) noexcept;

  constexpr T operator[](std::size_t i) const noexcept;
  constexpr T& operator[](std::size_t i) noexcept;
};

template<typename T>
struct vec<T, 2> {
  union {
    T data[2];

    /* implementation-defined */ x;
    /* implementation-defined */ y;

    /* implementation-defined */ width;
    /* implementation-defined */ height;
  };

  vec();
  constexpr vec(T m1, T m2) noexcept;

  vec(const vec& other) = default;

  template<typename U>
  vec(const vec<U, 2>& other) noexcept;

  constexpr T operator[](std::size_t i) const noexcept;
  constexpr T& operator[](std::size_t i) noexcept;
};

template<typename T>
struct vec<T, 3> {
  union {
    T data[3];

    /* implementation-defined */ x;
    /* implementation-defined */ y;
    /* implementation-defined */ z;

    /* implementation-defined */ r;
    /* implementation-defined */ g;
    /* implementation-defined */ b;
  };

  vec();
  constexpr vec(T m1, T m2, T m3) noexcept;

  vec(const vec& other) = default;

  template<typename U>
  vec(const vec<U, 3>& other) noexcept;

  constexpr T operator[](std::size_t i) const noexcept;
  constexpr T& operator[](std::size_t i) noexcept;
};

template<typename T>
struct vec<T, 4> {
  union {
    T data[4];

    /* implementation-defined */ x;
    /* implementation-defined */ y;
    /* implementation-defined */ z;
    /* implementation-defined */ w;

    /* implementation-defined */ r;
    /* implementation-defined */ g;
    /* implementation-defined */ b;
    /* implementation-defined */ a;
  };

  vec();
  constexpr vec(T m1, T m2, T m3, T m4) noexcept;

  vec(const vec& other) = default;

  template<typename U>
  vec(const vec<U, 4>& other) noexcept;

  constexpr T operator[](std::size_t i) const noexcept;
  constexpr T& operator[](std::size_t i) noexcept;
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
```

## Vector operations

### Rationale

Common operators (`+`, `-`, `*`, `/`) are overloaded with vector-vector, vector-scalar and scalar-vector operands. These operators are defined as component-wise operations.

### Synopsis

```cpp
template<typename T, std::size_t N>
bool operator==(vec<T, N> lhs, vec<T, N> rhs);

template<typename T, std::size_t N>
bool operator!=(vec<T, N> lhs, vec<T, N> rhs);

template<typename T, std::size_t N>
vec<T, N> operator-(vec<T, N> v);

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator+(vec<T,N> lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator+=(vec<T,N>& lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator+(T lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator+(vec<T,N> lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator+=(vec<T,N>& lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator-(vec<T,N> lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator-=(vec<T,N>& lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator-(T lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator-(vec<T,N> lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator-=(vec<T,N>& lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator*(vec<T,N> lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator*=(vec<T,N>& lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator*(T lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator*(vec<T,N> lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator*=(vec<T,N>& lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator/(vec<T,N> lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator/=(vec<T,N>& lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator/(T lhs, vec<U,N> rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>,N> operator/(vec<T,N> lhs, U rhs) noexcept;

template<typename T, typename U, std::size_t N>
constexpr
vec<T,N>& operator/=(vec<T,N>& lhs, U rhs) noexcept;
```

## Matrix types

### Rationale

The type for matrices is named `mat`. It has two template parameters: the type `T` of the elements and the size of the matrix `N`. Only square matrix are defined. The following table shows the name of the base matrix type in different libraries.

| Library | Name for matrix type | References |
|---------|----------------------|------------|
| glm     | `mat`                | [ref](https://github.com/g-truc/glm/blob/master/glm/detail/qualifier.hpp#L37) |
| QVM     | `mat`                | [ref](http://boostorg.github.io/qvm/mat.html) |
| linalg  | `mat`                | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L117) |
| hmi     | `mat`                |            |

An `operator()` is defined with two parameters: `row` for the row of the element and `col` for the column of the element. This is the traditional order to access matrix elements.

Elements are stored in a [row-major order](https://en.wikipedia.org/wiki/Row-_and_column-major_order).

| Library | Name for matrix type | References |
|---------|----------------------|------------|
| glm     | column-major         | [ref](http://glm.g-truc.net/glm.pdf) at 4.19 |
| QVM     | row-major            | [ref](https://github.com/boostorg/qvm/blob/master/include/boost/qvm/mat.hpp#L19) |
| linalg  | column-major         | [ref](https://github.com/sgorsten/linalg/blob/master/linalg.h#L116) |
| hmi     | row-major            |            |

Specialization are defined for `N` equals to 2, 3 and 4 with special accessors for the fields of the matrix.

### Synopsis

```cpp
template<typename T, std::size_t N>
struct mat {
  T data[N][N];

  mat();
  mat(const mat& other) = default;

  template<typename U>
  mat(const mat<U, N>& other) noexcept;

  constexpr T operator()(std::size_t row, std::size_t col) const noexcept;
  constexpr T& operator()(std::size_t row, std::size_t col) noexcept;
};

template<typename T>
struct mat<T, 2> {
  union {
    T data[2][2];

    /* implementation-defined */ xx;
    /* implementation-defined */ xy;
    /* implementation-defined */ yx;
    /* implementation-defined */ yy;
  };

  mat();
  constexpr mat(T xx, T xy, T yx, T yy) noexcept;
  mat(const mat& other) = default;

  template<typename U>
  mat(const mat<U, 2>& other) noexcept;

  constexpr T operator()(std::size_t row, std::size_t col) const noexcept;
  constexpr T& operator()(std::size_t row, std::size_t col) noexcept;
};

template<typename T>
struct mat<T, 3> {
  union {
    T data[3][3];

    /* implementation-defined */ xx;
    /* implementation-defined */ xy;
    /* implementation-defined */ xz;
    /* implementation-defined */ yx;
    /* implementation-defined */ yy;
    /* implementation-defined */ yz;
    /* implementation-defined */ zx;
    /* implementation-defined */ zy;
    /* implementation-defined */ zz;
  };

  mat();
  constexpr mat(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz) noexcept;
  mat(const mat& other) = default;

  template<typename U>
  mat(const mat<U, 3>& other) noexcept;

  constexpr T operator()(std::size_t row, std::size_t col) const noexcept;
  constexpr T& operator()(std::size_t row, std::size_t col) noexcept;
};

template<typename T>
struct mat<T, 4> {
  union {
    T data[4][4];

    /* implementation-defined */ xx;
    /* implementation-defined */ xy;
    /* implementation-defined */ xz;
    /* implementation-defined */ xw;
    /* implementation-defined */ yx;
    /* implementation-defined */ yy;
    /* implementation-defined */ yz;
    /* implementation-defined */ yw;
    /* implementation-defined */ zx;
    /* implementation-defined */ zy;
    /* implementation-defined */ zz;
    /* implementation-defined */ zw;
    /* implementation-defined */ wx;
    /* implementation-defined */ wy;
    /* implementation-defined */ wz;
    /* implementation-defined */ ww;
  };

  mat();

  constexpr mat(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww) noexcept;
  mat(const mat& other) = default;

  template<typename U>
  mat(const mat<U, 4>& other) noexcept;

  constexpr T operator()(std::size_t row, std::size_t col) const noexcept;
  constexpr T& operator()(std::size_t row, std::size_t col) noexcept;
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

```

## Matrix operations

### Rationale

Operators `+` and `-` are defined for matrix-scalar, scalar-matrix and matrix-matrix as component-wise operations.

Operator `*` is defined for scalar-matrix, matrix-scalar, vector-matrix, matrix-vector and matrix-matrix multiplications in the [usual sense](https://en.wikipedia.org/wiki/Matrix_multiplication).

### Synopsis

```cpp
template<typename T, std::size_t N>
constexpr
bool operator==(const mat<T, N>& lhs, const mat<T, N>& rhs);

template<typename T, std::size_t N>
constexpr
bool operator!=(const mat<T, N>& lhs, const mat<T, N>& rhs);

template<typename T, std::size_t N>
constexpr
mat<T, N> operator-(const mat<T, N>& m);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator+(const mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<T, N>& operator+=(mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator-(const mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<T, N>& operator-=(mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator*(const mat<T, N>& lhs, U rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<T, N>& operator*=(mat<T, N>& lhs, U rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator*(T lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator/(const mat<T, N>& lhs, U rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<T, N>& operator/=(mat<T, N>& lhs, U rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T,U>, N> operator/(T lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>, N> operator*(const mat<T, N>& lhs, const vec<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
vec<std::common_type_t<T,U>, N> operator*(const vec<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<std::common_type_t<T, U>, N> operator*(const mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, typename U, std::size_t N>
constexpr
mat<T, N>& operator*=(mat<T, N>& lhs, const mat<U, N>& rhs);

template<typename T, std::size_t N>
constexpr
mat<T, N> transpose(const mat<T, N>& m);

template<typename T>
constexpr
mat<T, 2> invert(const mat<T, 2>& input);

template<typename T>
constexpr
mat<T, 3> invert(const mat<T, 3>& input);

template<typename T>
constexpr
mat<T, 4> invert(const mat<T, 4>& input);
```
