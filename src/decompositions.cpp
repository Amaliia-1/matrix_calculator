#include "../include/decompositions.h"
#include "../include/matrix.h"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>

// LU-разложение
template<typename T>
std::tuple<Matrix<T>, Matrix<T>, std::vector<size_t>> lu_decomposition(const Matrix<T>& A) {
	if (!A.isSquare())
		throw std::invalid_argument("LU-разложение требует квадратную матрицу");
	size_t n = A.rows();
	Matrix<T> L(n, n, T{0});
	Matrix<T> U = A;
	std::vector<size_t> perm(n);
	std::iota(perm.begin(), perm.end(), 0);
	
	for (size_t k = 0; k < n; ++k) {
		size_t maxRow = k;
		T maxVal = std::abs(U(k, k));
		for (size_t i = k+1; i < n; ++i) {
			if (std::abs(U(i, k)) > maxVal) {
				maxVal = std::abs(U(i, k));
				maxRow = i;
			}
		}
		if (maxVal < T{1e-12})
			throw std::runtime_error("Матрица вырождена (нулевой ведущий элемент).\nПожалуйста, введите невырожденную матрицу.");
		if (maxRow != k) {
			for (size_t j = 0; j < n; ++j)
				std::swap(U(k, j), U(maxRow, j));
			std::swap(perm[k], perm[maxRow]);
		}
		L(k, k) = T{1};
		for (size_t i = k+1; i < n; ++i) {
			T factor = U(i, k) / U(k, k);
			L(i, k) = factor;
			for (size_t j = k; j < n; ++j)
				U(i, j) -= factor * U(k, j);
		}
	}
	return {L, U, perm};
}

bool perm_parity(const std::vector<size_t>& perm) {
	size_t n = perm.size();
	std::vector<bool> visited(n, false);
	size_t swaps = 0;
	for (size_t i = 0; i < n; ++i) {
		if (!visited[i]) {
			size_t cycleLen = 0;
			size_t j = i;
			while (!visited[j]) {
				visited[j] = true;
				j = perm[j];
				++cycleLen;
			}
			if (cycleLen > 0) swaps += (cycleLen - 1);
		}
	}
	return (swaps % 2) == 1;
}

// QR-разложение
template<typename T>
std::pair<Matrix<T>, Matrix<T>> qr_decomposition(const Matrix<T>& A) {
	if (!A.isSquare()) {
		throw std::invalid_argument("QR-разложение требует квадратную матрицу");
	}
	size_t n = A.rows();
	Matrix<T> Q = A;  // копия исходной матрицы
	Matrix<T> R(n, n, T{0});
	
	for (size_t j = 0; j < n; ++j) {
		// Норма j-го столбца
		T norm = 0;
		for (size_t i = 0; i < n; ++i) {
			norm += Q(i, j) * Q(i, j);
		}
		norm = std::sqrt(norm);
		if (norm < T{1e-12}) {
			R(j, j) = T{0};
			continue;
		}
		R(j, j) = norm;
		// Нормализация j-го столбца
		for (size_t i = 0; i < n; ++i) {
			Q(i, j) /= norm;
		}
		// Вычитание проекции из последующих столбцов
		for (size_t k = j + 1; k < n; ++k) {
			T dot = 0;
			for (size_t i = 0; i < n; ++i) {
				dot += Q(i, j) * Q(i, k);
			}
			R(j, k) = dot;
			for (size_t i = 0; i < n; ++i) {
				Q(i, k) -= dot * Q(i, j);
			}
		}
	}
	return {Q, R};
}

// Явные инстанциации для double
template std::tuple<Matrix<double>, Matrix<double>, std::vector<size_t>> lu_decomposition(const Matrix<double>&);
template std::pair<Matrix<double>, Matrix<double>> qr_decomposition(const Matrix<double>&);
