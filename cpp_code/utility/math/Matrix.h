#ifndef NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_H_
#define NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_H_

#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "utility/math/Vector.hpp"

namespace util::math {

/**
 * @brief Inserts the formatted data of a matrix into an ostream.
 * @param os The ostream to insert the formatted matrix data into.
 * @param mat The matrix to pull the data from.
 * @return A reference to the ostream with the matrix data inserted.
 */
template <typename T, std::size_t N, std::size_t M>
std::ostream& operator<<(std::ostream& os, const ame::Matrix<T, N, M> mat) {
  os << N << "x" << M << "\:" << std::endl;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < M; j++) {
      os << mat(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

/**
 * @class Matrix
 * @brief Organizes generic data and exposes common matrix operations.
 */
template <typename T, std::size_t N, std::size_t M>
class alignas(16) Matrix {
  public:
    /**
     * @brief Constructs a matrix of the given dimensions where every element contains the default value for the given datatype.
     */
    Matrix();

    /**
     * @brief Constructs a matrix of the given dimensions where every element contains the given value.
     * @param value The value for each element.
     */
    explicit Matrix(const T& value);

    /**
     * @brief Constructs a matrix of the given domensions from the provided elements.
     * @param values The values to initialize the matrix with.
     * @throws std::runtime_error If values.size != N * M.
     */
    explicit Matrix(std::initializer_list<T> values);
    ~Vector() = default;

    /**
     * @brief Returns a non-const reference to the element at the given indices.
     * @param n The row of the target element.
     * @param m The column of the target element.
     * @return A non-const reference to the element at the given indices.
     * @throws std::runtime_error If n < 0 or n >= N or m < 0 or m >= M.
     */
    [[nodiscard]] T& operator()(std::size_t n, std::size_t m);

    /**
     * @brief Returns a const reference to the element at the given indices.
     * @param n The row of the target element.
     * @param m The column of the target element.
     * @return A const reference to the element at the given indices.
     * @throws std::runtime_error If n < 0 or n >= N or m < 0 or m >= M.
     */
    [[nodiscard]] const T& operator()(std::size_t n, std::size_t m) const;

    /**
     * @brief Returns the matrix as a column major matrix. This is the same as the transpose of the matrix.
     * @return A column-major version of the matrix.
     */
    [[nodiscard]] const Matrix<T, M, N> as_column_major() const noexcept;

    /**
     * @brief Returns the sum of two matrices.
     * @param addend The right-hand matrix to add.
     * @return The sum of both matrices.
     */
    [[nodiscard]] Matrix<T, N, M> operator+(const Matrix<T, N, M>& addend) const noexcept;

    /**
     * @brief Returns the difference of two matrices.
     * @param subtrahend The right-hand matrix to subtract.
     * @return The difference of both matrices.
     */
    [[nodiscard]] Matrix<T, N, M> operator-(const Matrix<T, N, M>& subtrahend) const noexcept;

    /**
     * @brief Returns the product of two matrices.
     * @param multiplicand The right hand matrix to multiply by.
     * @return The product of both matrices.
     */
    template <std::size_t P>
    [[nodiscard]] Matrix<T, N, P> operator*(const Matrix<T, M, P>& multiplicand) const noexcept;

    /**
     * @brief Returns the product of a matrix and a vector.
     * @param multiplicand The right hand vector to multiply by.
     * @return The product of the matrix and the vector.
     */
    [[nodiscard]] Vector<T, N> operator*(const Vector<T, M>& multiplicand) const noexcept;

    /**
     * @brief Returns the scalar product by a given scalar.
     * @param multiplicand The scalar to multiply by.
     * @return The scalar product by the given multiplicand.
     */
    [[nodiscard]] Matrix<T, N, M> operator*(const T& multiplicand) const noexcept;

    /**
     * @brief Returns the scalar quotient from a given scalar.
     * @param multiplicand The scalar to divide by.
     * @return The scalar quotient from the given divisor.
     */
    [[nodiscard]] Matrix<T, N, M> operator/(T& divisor) const noexcept;

    /**
     * @brief Computes the sum of two matrices and assigns the result to the left-hand matrix.
     * @param addend The right-hand matrix to add.
     * @return A reference to the left-hand matrix.
     */
    [[nodiscard]] Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& addend) noexcept;

    /**
     * @brief Computes the difference of two matrices and assigns the result to the left-hand matrix.
     * @param subtrahend The right-hand matrix to subtract.
     * @return A reference to the left-hand matrix.
     */
    [[nodiscard]] Matrix<T, N, M>& operator-=(const Matrix<T, N, M>& subtrahend) noexcept;

    /**
     * @brief Computes the scalar product by a given scalar and assigns the result to the left-hand matrix.
     * @param multiplicand The scalar to multiply by.
     * @return A reference to the left-hand matrix.
     */
    [[nodiscard]] Matrix<T, N, M>& operator*=(T& multiplicand) noexcept;

    /**
     * @brief Computes the scalar quotient from a given scalar and assigns the result to the left-hand matrix.
     * @param divisor The scalar to divide by.
     * @return A reference to the left-hand matrix.
     */
    [[nodiscard]] Matrix<T, N, M>& operator/=(T& divisor) noexcept;

    /**
     * @brief Returns a square identity matrix of the given size.
     * @return A square identity matrix.
     */
    [[nodiscard]] static Matrix<T, N, M> Identity() requires(N == M) noexcept;

    /**
     * @brief Returns the transpose of the given matrix.
     * @return The transpose of the given matrix.
     */
    [[nodiscard]] Matrix<T, M, N> Transpose() const noexcept;

    /**
     * @brief Returns the inverse of the given matrix.
     * @return The inverse of the given matrix.
     */
    [[nodiscard]] Matrix<T, N, M> Inverse() const requires(N == M);

    /**
     * @brief Returns the determinant of the given matrix.
     * @return The determinant of the given matrix.
     */
    [[nodiscard]] T Determinant() const noexcept requires(N == M);

    /**
     * @brief Returns the augment of the given matrix and the target matrix.
     * @param target The matrix to augment the given matrix with.
     * @return The given matrix augmented with the target matrix.
     */
    template <std::size_t P>
    Matrix<T, N, M + P> Augment(const Matrix<T, N, P>& target) const noexcept;

  protected:
    /**
     * @brief Returns the element at the provided linear index.
     * @param i The index of the target element.
     * @return A non-const reference to the element at the given index.
     * @throws std::runtime_error If i < 0 or i >= M * N.
     */
    T& operator[](const std::size_t i) {
      if (i < 0 || i > M * N) throw new std::runtime_error("AME: Index Out of Bounds.");
      return Data[i];
    }

    /**
     * @brief Returns the element at the provided linear index.
     * @param i The index of the target element.
     * @return A const reference to the element at the given index.
     * @throws std::runtime_error If i < 0 or i >= M * N.
     */
    const T& operator[](const std::size_t i) const {
      if (i < 0 || i > M * N) throw new std::runtime_error("AME: Index Out of Bounds.");
      return Data[i];
    }

  private:
    T Data[N * M];

    /**
     * @brief Returns the linear index of the provided row-column indices.
     * @param n The row index.
     * @param m The column index.
     * @return A linear index.
     */
    constexpr std::size_t Index(std::size_t n, std::size_t m) const noexcept { return n * M + m; }
};

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix() {
  for (std::size_t i = 0; i < N * M; i++) {
    Data[i] = T{};
  }
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix(const T& value) {
  for (std::size_t i = 0; i < N * M; i++) {
    Data[i] = value;
  }
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix(std::initializer_list<T> values) {
  if (values.size() != N * M) throw std::runtime_error("ARE: Matrix Initializer Array Contains Incorrect Number of Elements.");

  std::size_t i = 0;
  for (const auto& value : values) {
    Data[i] = value;
    i++;
  }
}

template <typename T, std::size_t N, std::size_t M>
T& Matrix<T, N, M>::operator()(std::size_t n, std::size_t m) {
  if (n < 0 || n >= N || m < 0 || m >= M) throw std::runtime_error("AME: Index Out of Bounds.");
  return Data[Index(n, m)];
}

template <typename T, std::size_t N, std::size_t M>
const T& Matrix<T, N, M>::operator()(std::size_t n, std::size_t m) const {
  if (n < 0 || n >= N || m < 0 || m >= M) throw std::runtime_error("AME: Index Out of Bounds.");
  return Data[this->Index(n, m)];
}

template <typename T, std::size_t N, std::size_t M>
const Matrix<T, M, N> Matrix<T, N, M>::as_column_major() const noexcept {
  Matrix<M, N, T> column_major;
  for (std::size_t i = 0; i < M; i++) {
    for (std::size_t j = 0; j < N; j++) {
      column_major(i, j) = Data[Index(j, i)];
    }
  }
  return column_major;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator+(const Matrix<T, N, M>& addend) const noexcept {
  Matrix<T, N, M> sum;
  for (std::size_t i = 0; i < N * M; i++) {
    sum[i] = Data[i] + addend[i];
  }
  return sum;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator-(const Matrix<T, N, M>& subtrahend) const noexcept {
  Matrix<T, N, M> difference;
  for (std::size_t i = 0; i < N * M; i++) {
    difference[i] = Data[i] - subtrahend[i];
  }
  return difference;
}

template <typename T, std::size_t N, std::size_t M>
template <std::size_t P>
Matrix<T, N, P> Matrix<T, N, M>::operator*(const Matrix<T, M, P>& multiplicand) const noexcept {
  Matrix<T, N, P> product;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < P; j++) {
      T sum{};
      for (std::size_t k = 0; k < M; k++) {
        sum += Data[Index(i, k)] * multiplicand(k, j);
      }
      product(i, j) = sum;
    }
  }
  return product;
}

template <typename T, std::size_t N, std::size_t M>
Vector<T, N> Matrix<T, N, M>::operator*(const Vector<T, M>& multiplicand) const noexcept {
  Vector<T, N> product;
  for (std::size_t i = 0; i < N; i++) {
    T sum{};
    for (std::size_t j = 0; j < M; j++) {
      sum += Data[Index(i, j)] * multiplicand(j);
    }
    product[i] = sum;
  }
  return product;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::operator*(const T& multiplicand) const noexcept {
  Matrix<T, N, M> product;
  for (std::size_t i = 0; i < N * M; i++) {
    product[i] = Data[i] * multiplicand;
  }
  return product;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(const Matrix<T, N, M>& addend) noexcept {
  for (int i = 0; i < N * M; i++) {
    Data[i] += addend[i];
  }
  return *this;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(const Matrix<T, N, M>& subtrahend) noexcept {
  for (int i = 0; i < N * M; i++) {
    Data[i] -= subtrahend[i];
  }
  return *this;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(T& multiplicand) noexcept {
  for (int i = 0; i < N * M; i++) {
    Data[i] += multiplicand;
  }
  return *this;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator/=(T& divisor) noexcept {
  for (int i = 0; i < N * M; i++) {
    Data[i] /= divisor;
  }
  return *this;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::Identity() requires(N == M) noexcept {
  Matrix<T, N, N> identity;
  for (std::size_t i = 0; i < N; i++) {
    identity(i, i) = T{ 1 };
  }
  return identity;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, M, N> Matrix<T, N, M>::Transpose() const noexcept {
  Matrix<T, M, N> transpose;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < M; j++) {
      transpose(j, i) = Data[Index(i, j)];
    }
  }
  return transpose;
}

template <typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::Inverse() const requires(N == M) {
  // TODO(ChristopherStackpole57): requires Determinant to be implemented
  // static_assert(this->Determinant() != 0);

  // Implements Gauss - Jordan Elimination
  Matrix<T, N, N> A = *this;  // Copy current matrix for easier manipulation
  Matrix<T, N, N> I = Matrix<T, N, N>::Identity();  // Identity Matrix

  for (std::size_t col = 0; col < N; col++) {
    // Find Pivot Row
    std::size_t pivot = col;
    for (std::size_t row = col + 1; row < N; row++) {
      if (std::abs(A(row, col)) > std::abs(A(pivot, row))) {
        pivot = row;
      }
    }

    // Check for Singular Matrix
    if (A(pivot, col) == T{ 0 }) {
      throw std::runtime_error("AME: Singular Matrices Cannot Be Inverted.");
    }

    // Swap Current Row with Pivot Row in Both A and I
    if (pivot != col) {
      for (std::size_t j = 0; j < N; j++) {
        std::swap(A(col, j), A(pivot, j));
        std::swap(I(col, j), I(pivot, j));
      }
    }

    // Normalize Pivot Row
    T pivot_val = A(col, col);
    for (std::size_t j = 0; j < N; j++) {
      A(col, j) /= pivot_val;
      I(col, j) /= pivot_val;
    }

    // Eliminate All Other Entries in This Column
    for (std::size_t row = 0; row < N; row++) {
      if (row == col) continue;

      T factor = A(row, col);
      for (std::size_t j = 0; j < N; j++) {
        A(row, j) -= factor * A(col, j);
        I(row, j) -= factor * I(col, j);
      }
    }
  }

  return I;
}

template <typename T, std::size_t N, std::size_t M>
T Matrix<T, N, M>::Determinant() const noexcept requires(N == M) {
  // TODO(ChristopherStackple57): implement
}

template <typename T, std::size_t N, std::size_t M>
template <std::size_t P>
Matrix<T, N, M + P> Matrix<T, N, M>::Augment(const Matrix<T, N, P>& target) const noexcept {
  Matrix<T, N, M + P> augment;
  for (std::size_t i = 0; i < N; i++) {
    // Copy data from this
    for (std::size_t j = 0; j < M; j++) {
      augment(i, j) = this->Data[this->Index(i, j)];
    }

    // Copy data from target
    for (std::size_t j = 0; j < P; j++) {
      augment(i, j + M) = target(i, j);
    }
  }
  return augment;
}

}  // namespace util::math

#endif  // NSDS_COUNTER_UAS_CPP_CODE_UTILITY_MATH_H_
