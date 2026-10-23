#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_VECTOR_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_VECTOR_H_

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>

namespace util::math {

/**
 * @class Vector
 * @brief Organizes generic data and exposes common vector operations. 
 */
template<typename T, std::size_t N>
class Vector {
  public:
    /**
     * @brief Constructs a vector of the given size where every element contains the default value for the given datatype.
     */
    Vector();

    /**
     * @brief Constructs a vector of the given size where every element contains the provided value.
     * @param value The value for each element.
     */
    explicit Vector(const T& value);

    /**
     * @brief Constructs a vector of the given size from the provided elements.
     * @param values The values to initialize the vector with.
     * @throws std::runtime_error If values.size() != N.
     */
    explicit Vector(const std::initializer_list<T> values);
    ~Vector() = default;

    /**
     * @brief Returns a non-const reference to the element at the given index.
     * @param index The element index to access.
     * @return A non-const reference to the element at the given index.
     * @throws std::runtime_error If index is < 0 or >= N.
     */
    [[nodiscard]] T& operator[](const std::size_t index);

    /**
     * @brief Returns a const reference to the element at the given index.
     * @param index The element index to access.
     * @return A const reference to the element at the given index.
     * @throws std::runtime_error If index is < 0 or >= N.
     */
    [[nodiscard]] const T& operator[](const std::size_t index) const;

    /**
     * @brief Returns the sum of two vectors.
     * @param addend The right-hand vector to add.
     * @return The sum of both vectors.
     */
    [[nodiscard]] Vector<T, N> operator+(const Vector<T, N>& addend) const noexcept;

    /**
     * @brief Returns the difference of two vectors.
     * @param subtrahend The right-hand vector to subtract.
     * @return The difference of both vectors.
     */
    [[nodiscard]] Vector<T, N> operator-(const Vector<T, N>& subtrahend) const noexcept;

    /**
     * @brief Returns the scalar product by a given scalar.
     * @param multiplicand The scalar to multiply by.
     * @return The scalar product by the given multiplicand.
     */
    [[nodiscard]] Vector<T, N> operator*(const T multiplicand) const noexcept;

    /**
     * @brief Returns the scalar quotient from a given scalar.
     * @param divisor The scalar to divide by.
     * @return The scalar quotient from a given divisor.
     */
    [[nodiscard]] Vector<T, N> operator/(const T divisor) const noexcept;

    /**
     * @brief Computes the sum of two vectors and assigns the result to the left-hand vector.
     * @param addend The right-hand vector to add.
     * @return A reference to the left-hand vector.
     */
    [[nodiscard]] Vector<T, N>& operator+=(const Vector<T, N>& addend) noexcept;

    /**
     * @brief Computes the difference of two vectors and assigns the result to the left-hand vector.
     * @param subtrahend The right-hand vector to subtract.
     * @return A reference to the left-hand vector.
     */
    [[nodiscard]] Vector<T, N>& operator-=(const Vector<T, N>& subtrahend) noexcept;

    /**
     * @brief Computes the scalar product by a given scalar and assigns the result to the left-hand vector.
     * @param multiplicand The scalar to multiply by.
     * @return A reference to the left-hand vector.
     */
    [[nodiscard]] Vector<T, N>& operator*=(const T multiplicand) noexcept;

    /**
     * @brief Computes the scalar quotient from a given scalar.
     * @param divisor The scalar to divide by.
     * @return A reference to the left-hand vector.
     */
    [[nodiscard]] Vector<T, N>& operator/=(const T divisor) noexcept;

    /**
     * @brief Computes the dot product of two vectors.
     * @param target The right-hand vector to compute the inner product with.
     * @return The scalar result of the inner product of both vectors.
     */
    [[nodiscard]] T Dot(const Vector<T, N>& target) const noexcept;

    /**
     * @brief Computes the cross product of two three element vectors.
     * @param other The right-hand vector to compute the cross product with.
     * @return A vector orthogonal to the two given vectors.
     */
    Vector<T, 3> Cross(const Vector<T, 3>& other) const noexcept requires(N == 3);

    /**
    * @brief Computes the magnitude of the vector.
    * @return The scalar magnitude of the vector.
    */
    [[nodiscard]] T Magnitude() const noexcept;

    /**
     * @brief Computes the normalized version of the vector.
     * @return The normalized vector.
     */
    [[nodiscard]] Vector<T, N> Normalized() const noexcept;

  private:
    T Data[N];
};

template <typename T, std::size_t N>
Vector<T, N>::Vector() {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] = T{};
  }
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const T& value) {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] = value;
  }
}

template <typename T, std::size_t N>
Vector<T, N>::Vector(const std::initializer_list<T> values) {
  if (values.size() != N) throw std::runtime_error("AME: Vector Initializer Array Contains Incorrect Number of Elements.");

  std::size_t i = 0;
  for (const auto& value : values) {
    Data[i] = value;
    i++;
  }
}

template <typename T, std::size_t N>
T& Vector<T, N>::operator[](const std::size_t index) {
  if (index < 0 || index >= N) throw std::runtime_error("AME: Index Out of Bounds.");
  return Data[index];
}

template <typename T, std::size_t N>
const T& Vector<T, N>::operator[](const std::size_t index) const {
  if (index < 0 || index >= N) throw std::runtime_error("AME: Index Out of Bounds.");
  return Data[index];
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& target) const noexcept {
  Vector<T, N> sum;
  for (std::size_t i = 0; i < N; i++) {
    sum[i] = Data[i] + target[i];
  }
  return sum;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& target) const noexcept {
  Vector<T, N> difference;
  for (std::size_t i = 0; i < N; i++) {
    difference[i] = Data[i] - target[i];
  }
  return difference;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator*(T scalar) const noexcept {
  Vector<T, N> product;
  for (std::size_t i = 0; i < N; i++) {
    product[i] = Data[i] * scalar;
  }
  return product;
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::operator/(T divisor) const noexcept {
  Vector<T, N> quotient;
  for (std::size_t i = 0; i < N; i++) {
    quotient[i] = Data[i] / divisor;
  }
  return quotient;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& target) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] += target[i];
  }
  return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& target) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] -= target[i];
  }
  return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T scalar) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] *= scalar;
  }
  return *this;
}

template <typename T, std::size_t N>
Vector<T, N>& Vector<T, N>::operator/=(T divisor) noexcept {
  for (std::size_t i = 0; i < N; i++) {
    Data[i] /= divisor;
  }
  return *this;
}

template <typename T, std::size_t N>
T Vector<T, N>::Dot(const Vector<T, N>& target) const noexcept {
  T sum{};
  for (std::size_t i = 0; i < N; i++) {
    sum += Data[i] * target[i];
  }
  return sum;
}

template <typename T, std::size_t N>
Vector<T, 3> Vector<T, N>::Cross(const Vector<T, 3>& other) const noexcept requires(N == 3) {
  return Vector<T, 3>{
    Data[1] * other[2] - Data[2] * other[1],
    Data[2] * other[0] - Data[0] * other[2],
    Data[0] * other[1] - Data[1] * other[0]
  };
}

template <typename T, std::size_t N>
T Vector<T, N>::Magnitude() const noexcept {
  T sum{};
  for (std::size_t i = 0; i < N; i++) {
    sum += Data[i] * Data[i];
  }
  return std::sqrt(sum);
}

template <typename T, std::size_t N>
Vector<T, N> Vector<T, N>::Normalized() const noexcept {
  T magnitude = Magnitude();
  Vector<T, N> norm;
  for (std::size_t i = 0; i < N; i++) {
    norm[i] = Data[i] / magnitude;
  }
  return norm;
}

}  // namespace util::math

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_VECTOR_H_
