#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include "../include/matrix.h"
#include "../include/decompositions.h"

using namespace std;

double readNumber() {
	double value;
	while (!(cin >> value)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Ошибка ввода. Введите число: ";
	}
	return value;
}

Matrix<double> readMatrixFromConsole(const string& prompt) {
	cout << prompt << endl;
	cout << "Введите количество строк и столбцов: ";
	int rows = static_cast<int>(readNumber());
	int cols = static_cast<int>(readNumber());
	if (rows <= 0 || cols <= 0)
		throw invalid_argument("Размеры должны быть положительными");
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	Matrix<double> mat(rows, cols);
	cout << "Введите матрицу (чисел в строке: " << cols << ")\n";
	for (int i = 0; i < rows; ++i) {
		cout << "Строка " << i + 1 << ": ";
		string line;
		getline(cin, line);
		istringstream iss(line);
		vector<double> row;
		double val;
		while (iss >> val) row.push_back(val);
		if (row.size() != static_cast<size_t>(cols))
			throw runtime_error("Неверное количество чисел в строке");
		for (int j = 0; j < cols; ++j)
			mat(i, j) = row[j];
	}
	return mat;
}

int showMenu() {
	cout << "\nДобро пожаловать в калькулятор матриц!\n";
	cout << "1. Сложение матриц\n";
	cout << "2. Вычитание матриц\n";
	cout << "3. Умножение матриц\n";
	cout << "4. Умножение матрицы на скаляр\n";
	cout << "5. Транспонирование матрицы\n";
	cout << "6. Определитель матрицы\n";
	cout << "7. Обратная матрица\n";
	cout << "8. LU-разложение (вывести L и U)\n";
	cout << "9. QR-разложение (вывести Q и R)\n";
	cout << "0. Выход\n";
	cout << "Выберите пункт: ";
	return static_cast<int>(readNumber());
}

int main() {
	try {
		int choice;
		do {
			choice = showMenu();
			switch (choice) {
				case 1: {
				auto A = readMatrixFromConsole("Первая матрица (A):");
				auto B = readMatrixFromConsole("Вторая матрица (B):");
				cout << "A + B =\n" << A + B;
				break;
			}
				case 2: {
					auto A = readMatrixFromConsole("Первая матрица (A):");
					auto B = readMatrixFromConsole("Вторая матрица (B):");
					cout << "A - B =\n" << A - B;
					break;
				}
				case 3: {
					auto A = readMatrixFromConsole("Первая матрица (A):");
					auto B = readMatrixFromConsole("Вторая матрица (B):");
					cout << "A * B =\n" << A * B;
					break;
				}
				case 4: {
					auto A = readMatrixFromConsole("Матрица:");
					cout << "Скаляр: ";
					double s = readNumber();
					cout << "A * " << s << " =\n" << A * s;
					break;
				}
				case 5: {
					auto A = readMatrixFromConsole("Матрица:");
					cout << "Транспонированная:\n" << A.transpose();
					break;
				}
				case 6: {
					auto A = readMatrixFromConsole("Квадратная матрица:");
					cout << "Определитель = " << A.determinant() << endl;
					break;
				}
				case 7: {
					auto A = readMatrixFromConsole("Квадратная матрица:");
					cout << "Обратная матрица:\n" << A.inverse();
					break;
				}
				case 8: {
					auto A = readMatrixFromConsole("Квадратная матрица:");
					auto [L, U, perm] = lu_decomposition(A);
					cout << "L (нижняя треугольная):\n" << L;
					cout << "U (верхняя треугольная):\n" << U;
					break;
				}
				case 9: {
					auto A = readMatrixFromConsole("Квадратная матрица:");
					auto [Q, R] = qr_decomposition(A);
					cout << "Q (ортогональная матрица):\n" << Q;
					cout << "R (верхняя треугольная):\n" << R;
					cout << "Проверка (Q * R):\n" << Q * R;
					break;
				}
			case 0:
				cout << "До свидания!\n";
				break;
			default:
				cout << "Неверный пункт\n";
			}
		} while (choice != 0);
	} catch (const exception& ex) {
		cerr << "Ошибка: " << ex.what() << endl;
		return 1;
	}
	return 0;
}
