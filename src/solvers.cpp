#include "../include/solvers.h"
#include "../include/decompositions.h"

template<typename T>
std::vector<T> solve_lu(const Matrix<T>& A, const std::vector<T>& b) {
	auto [L, U, perm] = lu_decomposition(A);
	size_t n = A.rows();
	std::vector<T> pb(n);
	for (size_t i = 0; i < n; ++i) pb[i] = b[perm[i]];
	
	std::vector<T> y(n);
	for (size_t i = 0; i < n; ++i) {
		T sum = T{0};
		for (size_t j = 0; j < i; ++j) sum += L(i, j) * y[j];
		y[i] = pb[i] - sum;
	}
	std::vector<T> x(n);
	for (size_t i = n; i-- > 0; ) {
		T sum = T{0};
		for (size_t j = i+1; j < n; ++j) sum += U(i, j) * x[j];
		x[i] = (y[i] - sum) / U(i, i);
	}
	return x;
}


template<typename T>
Matrix<T> inverse_lu(const Matrix<T>& A) {
	size_t n = A.rows();
	Matrix<T> inv(n, n);
	for (size_t j = 0; j < n; ++j) {
		std::vector<T> e(n, T{0});
		e[j] = T{1};
		std::vector<T> col = solve_lu(A, e);
		for (size_t i = 0; i < n; ++i) inv(i, j) = col[i];
	}
	return inv;
}

template<typename T>
T determinant_gaussian(const Matrix<T>& A) {
	if (!A.isSquare())
		throw std::invalid_argument("Определитель существует только у квадратных матриц");
	
	size_t n = A.rows();
	Matrix<T> M = A;
	T det = 1.0;
	
	for (size_t col = 0; col < n; ++col) {
		size_t pivot_row = col;
		T max_val = std::abs(M(col, col));
		for (size_t row = col + 1; row < n; ++row) {
			T val = std::abs(M(row, col));
			if (val > max_val) {
				max_val = val;
				pivot_row = row;
			}
		}
		
		if (max_val < T{1e-12}) {
			// Матрица вырождена -> определитель = 0
			return T{0};
		}
		
		if (pivot_row != col) {
			// Меняем строки местами
			for (size_t j = 0; j < n; ++j) {
				std::swap(M(col, j), M(pivot_row, j));
			}
			det = -det;  // перестановка меняет знак
		}
		
		det *= M(col, col);
		
		// Обнуляем элементы ниже текущего
		for (size_t row = col + 1; row < n; ++row) {
			T factor = M(row, col) / M(col, col);
			for (size_t j = col; j < n; ++j) {
				M(row, j) -= factor * M(col, j);
			}
		}
	}
	return det;
}

// Явная инстанциация
template std::vector<double> solve_lu(const Matrix<double>&, const std::vector<double>&);
template Matrix<double> inverse_lu(const Matrix<double>&);
template double determinant_gaussian(const Matrix<double>&);
