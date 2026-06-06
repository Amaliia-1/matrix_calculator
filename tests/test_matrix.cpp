#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/matrix.h"

TEST_CASE("Matrix addition") {
	Matrix<double> A = {{1,2},{3,4}};
	Matrix<double> B = {{5,6},{7,8}};
	Matrix<double> C = A + B;
	CHECK(C(0,0) == 6);
	CHECK(C(0,1) == 8);
	CHECK(C(1,0) == 10);
	CHECK(C(1,1) == 12);
}

TEST_CASE("Determinant") {
	Matrix<double> A = {{1,2},{3,4}};
	CHECK(A.determinant() == -2.0);
}

TEST_CASE("Inverse") {
	Matrix<double> A = {{4,7},{2,6}};
	Matrix<double> inv = A.inverse();
	Matrix<double> I = A * inv;
	CHECK(I(0,0) == doctest::Approx(1.0));
	CHECK(I(0,1) == doctest::Approx(0.0));
	CHECK(I(1,0) == doctest::Approx(0.0));
	CHECK(I(1,1) == doctest::Approx(1.0));
}


TEST_CASE("Addition mismatch") {
	Matrix<double> A(2,3);
	Matrix<double> B(3,2);
	CHECK_THROWS_AS(A + B, std::invalid_argument);
}

TEST_CASE("Singular matrix") {
	Matrix<double> A = {{1,2},{2,4}};
	CHECK(A.determinant() == doctest::Approx(0.0));
}
