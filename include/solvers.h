/**
 * @file solvers.h
 * @brief Определитель и обратная матрица.
 */

#pragma once

#include "matrix.h"
#include <vector>

/**
 * @brief Решение системы линейных уравнений Ax = b методом LU.
 * @tparam T Тип элементов.
 * @param A Матрица коэффициентов (квадратная).
 * @param b Вектор правой части.
 * @return Вектор x.
 * @throw std::invalid_argument если A не квадратная или размеры не совпадают.
 * @throw std::runtime_error если A вырождена.
 */
template<typename T>
std::vector<T> solve_lu(const Matrix<T>& A, const std::vector<T>& b);

/**
 * @brief Вычисление обратной матрицы через LU-разложение.
 * @tparam T Тип элементов.
 * @param A Квадратная невырожденная матрица.
 * @return Обратная матрица.
 */
template<typename T>
Matrix<T> inverse_lu(const Matrix<T>& A);

/**
 * @brief Вычисление определителя.
 * @tparam T Тип элементов.
 * @param A Квадратная матрица.
 * @return Определитель (0 для вырожденной матрицы).
 */
template<typename T>
T determinant_gaussian(const Matrix<T>& A);
