// Copyright [2026] Purdue National Security and Defense Society
#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_MATH_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_MATH_H_

#include <cstddef>
#include <cstdint>

#include "utility/math/Matrix.h"
#include "utility/math/Vector.h"

namespace util::math {

template <typename T>
using Vector2 = Vector<T, 2>;
using Vector2i32 = Vector2<int32_t>;
using Vector2ui32 = Vector2<uint32_t>;
using Vector2i64 = Vector2<int64_t>;
using Vector2ui64 = Vector2<uint64_t>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

template <typename T>
using Vector3 = Vector<T, 3>;
using Vector3i32 = Vector3<int32_t>;
using Vector3ui32 = Vector3<uint32_t>;
using Vector3i64 = Vector3<int64_t>;
using Vector3ui64 = Vector3<uint64_t>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

template <typename T>
using Vector4 = Vector<T, 4>;
using Vector4i32 = Vector4<int32_t>;
using Vector4ui32 = Vector4<uint32_t>;
using Vector4i64 = Vector4<int64_t>;
using Vector4ui64 = Vector4<uint64_t>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template <std::size_t N, std::size_t M>
using Matrixi32 = Matrix<int32_t, N, M>;
template <std::size_t N, std::size_t M>
using Matrixui32 = Matrix<uint32_t, N, M>;
template <std::size_t N, std::size_t M>
using Matrixi64 = Matrix<int64_t, N, M>;
template <std::size_t N, std::size_t M>
using Matrixui64 = Matrix<uint64_t, N, M>;
template <std::size_t N, std::size_t M>
using Matrixf = Matrix<float, N, M>;
template <std::size_t N, std::size_t M>
using Matrixd = Matrix<double, N, M>;

}  // namespace util::math

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_MATH_H_
