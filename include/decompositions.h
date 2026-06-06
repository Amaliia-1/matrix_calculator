/**
 * @file decompositions.h
 * @brief Матричные разложения (LU и QR).
 */

#pragma once

#include "matrix.h"
#include <vector>
#include <tuple>
#include <utility>

/**
 * @brief LU-разложение с частичным выбором ведущего элемента.
 * @tparam T Тип элементов.
 * @param A Исходная квадратная матрица.
 * @return Кортеж (L, U, permutation).
 * @throw std::invalid_argument если матрица не квадратная.
 * @throw std::runtime_error если матрица вырождена.
 */
template<typename T>
std::tuple<Matrix<T>, Matrix<T>, std::vector<size_t>> lu_decomposition(const Matrix<T>& A);

/**
 * @brief QR-разложение.
 * @tparam T Тип элементов.
 * @param A Квадратная матрица.
 * @return Пара (Q, R), где Q ортогональна, R верхняя треугольная.
 * @throw std::invalid_argument если матрица не квадратная.
 */
template<typename T>
std::pair<Matrix<T>, Matrix<T>> qr_decomposition(const Matrix<T>& A);

/**
 * @brief Вычисление чётности перестановки.
 * @param perm Вектор перестановки.
 * @return true если число транспозиций нечётное.
 */
bool perm_parity(const std::vector<size_t>& perm);
