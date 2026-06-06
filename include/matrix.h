/**
 * @file matrix.h
 * @brief Определение шаблонного класса Matrix для работы с матрицами.
 */

#pragma once

#include <vector>
#include <initializer_list>
#include <ostream>
#include <stdexcept>

/**
 * @brief Класс матрицы с элементами типа T.
 * @tparam T Тип элементов (int, double и т.п.).
 */
template<typename T>
class Matrix {
public:
	/**
	 * @brief Конструктор с заданием размера и начального значения.
	 * @param rows Количество строк.
	 * @param cols Количество столбцов.
	 * @param init Начальное значение для всех элементов.
	 */
	Matrix(size_t rows, size_t cols, T init = T{});
	
	/**
	 * @brief Конструктор из списка инициализации (удобно для литералов).
	 * @param init Список строк, каждая строка — список чисел.
	 * @throw std::invalid_argument если строки имеют разную длину.
	 */
	Matrix(std::initializer_list<std::initializer_list<T>> init);
	
	// Копирование и перемещение по умолчанию
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) noexcept = default;
	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) noexcept = default;
	
	/**
	 * @brief Доступ к элементу (i,j) для чтения/записи.
	 * @param i Индекс строки (0-based).
	 * @param j Индекс столбца (0-based).
	 * @return Ссылка на элемент.
	 * @throw std::out_of_range при выходе за пределы.
	 */
	T& operator()(size_t i, size_t j);
	const T& operator()(size_t i, size_t j) const;
	
	size_t rows() const { return rows_; }
	size_t cols() const { return cols_; }
	bool isSquare() const { return rows_ == cols_; }
	

	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(const Matrix& other) const;
	Matrix operator*(T scalar) const;
	
	Matrix transpose() const;
	
	T determinant() const;
	
	Matrix inverse() const;
	
	/**
	 * @brief Вывод матрицы в поток.
	 * @param os Выходной поток.
	 * @param m Матрица.
	 * @return Ссылка на поток.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
		for (size_t i = 0; i < m.rows_; ++i) {
			for (size_t j = 0; j < m.cols_; ++j) {
				os << m(i, j) << " ";
			}
			os << "\n";
		}
		return os;
	}
	
private:
	size_t rows_, cols_;
	std::vector<T> data_;
};

