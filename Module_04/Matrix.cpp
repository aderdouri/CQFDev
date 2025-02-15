//
// Date: Sunday, April 18, 2015
// File name: Matrix.cpp
// Version: 1 
// Author: Abderrazak DERDOURI
// Subject: Certificate in Quantitative Finance 
//
// Description: class Matrix
//	
//
// Notes:
// Revision History:
//

#include "Matrix.h"

Matrix::Matrix(int nrows, int ncols, double ini)
{
	int i;
	r = nrows;
	c = ncols;
	d = new double[nrows*ncols];
	double* p = d;
	for (i = 0; i<nrows*ncols; i++) *p++ = ini;
}

Matrix::Matrix(const Matrix& mat)
{
	int i;
	r = mat.r;
	c = mat.c;
	d = new double[r*c];
	double* p = d;
	double* pm = mat.d;
	for (i = 0; i<r*c; i++) *p++ = *pm++;
}

Matrix::~Matrix()
{
	delete[] d;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
	int i;
	Matrix result(A);
	double* p = result.d;
	double* pB = B.d;
	for (i = 0; i<A.r*A.c; i++) *p++ += *pB++;
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& A)
{
	int i, j;
	for (i = 0; i<A.rows(); i++) {
		for (j = 0; j<A.columns() - 1; j++) os << A(i, j) << ',';
		os << A(i, j) << std::endl;
	}
	return os;
}
