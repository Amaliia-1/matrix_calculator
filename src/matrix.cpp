#include "../include/matrix.h"
#include "../include/solvers.h"

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T init)
: rows_(rows), cols_(cols), data_(rows * cols, init) {}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
	rows_ = init.size();
	if (rows_ == 0) {
		cols_ = 0;
		return;
	}
	cols_ = init.begin()->size();
	data_.reserve(rows_ * cols_);
	for (const auto& row : init) {
		if (row.size() != static_cast<size_t>(cols_)) {
			throw std::invalid_argument("Все строки должны иметь одинаковую длину");
		}
		data_.insert(data_.end(), row.begin(), row.end());
	}
}

template<typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
	if (i >= rows_ || j >= cols_)
		throw std::out_of_range("Индекс матрицы вне диапазона");
	return data_[i * cols_ + j];
}

template<typename T>
const T& Matrix<T>::operator()(size_t i, size_t j) const {
	if (i >= rows_ || j >= cols_)
		throw std::out_of_range("Индекс матрицы вне диапазона");
	return data_[i * cols_ + j];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_)
		throw std::invalid_argument("Сложение невозможно: размеры матриц должны совпадать");
	Matrix<T> res(rows_, cols_);
	for (size_t i = 0; i < data_.size(); ++i)
		res.data_[i] = data_[i] + other.data_[i];
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
	if (rows_ != other.rows_ || cols_ != other.cols_)
		throw std::invalid_argument("Вычитание невозможно: размеры матриц должны совпадать");
	Matrix<T> res(rows_, cols_);
	for (size_t i = 0; i < data_.size(); ++i)
		res.data_[i] = data_[i] - other.data_[i];
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (cols_ != other.rows_)
		throw std::invalid_argument("Умножение невозможно: число столбцов первой матрицы не равно числу строк второй");
	Matrix<T> res(rows_, other.cols_, T{0});
	for (size_t i = 0; i < rows_; ++i) {
		for (size_t k = 0; k < cols_; ++k) {
			T aik = (*this)(i, k);
			for (size_t j = 0; j < other.cols_; ++j) {
				res(i, j) += aik * other(k, j);
			}
		}
	}
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
	Matrix<T> res(rows_, cols_);
	for (size_t i = 0; i < data_.size(); ++i)
		res.data_[i] = data_[i] * scalar;
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> res(cols_, rows_);
	for (size_t i = 0; i < rows_; ++i)
		for (size_t j = 0; j < cols_; ++j)
			res(j, i) = (*this)(i, j);
	return res;
}

template<typename T>
T Matrix<T>::determinant() const {
	return determinant_gaussian(*this);
}

template<typename T>
Matrix<T> Matrix<T>::inverse() const {
	return inverse_lu(*this);
}

// Явная инстанциация для double (можно использовать и другие типы)
template class Matrix<double>;
