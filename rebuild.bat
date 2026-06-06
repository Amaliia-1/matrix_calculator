@echo off
echo Очистка...
del *.o *.a 2>nul
echo Компиляция...
g++ -std=c++17 -Iinclude -c src/matrix.cpp -o matrix.o
g++ -std=c++17 -Iinclude -c src/decompositions.cpp -o decompositions.o
g++ -std=c++17 -Iinclude -c src/solvers.cpp -o solvers.o
g++ -std=c++17 -Iinclude -c tests/test_matrix.cpp -o test_matrix.o
g++ -std=c++17 -Iinclude -c app/main.cpp -o main.o
echo Создание библиотеки...
ar rcs libmatrix.a matrix.o decompositions.o solvers.o
echo Линковка...
g++ test_matrix.o libmatrix.a -o matrix_tests.exe
g++ main.o libmatrix.a -o matrix_app.exe
echo Готово.