//
// Date: Sunday, April 18, 2015
// File name: Matrix.h
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

#if !defined (MATRIX_H_ALREADY_INCLUDED)
#define MATRIX_H_ALREADY_INCLUDEDA

#include <iostream>

class Matrix 
{
	public:
		Matrix(int nrows, int ncols, double ini = 0.0);
		Matrix(const Matrix& mat);
		~Matrix();
		inline int rows() const { return r; };
		inline int columns() const { return c; };
		inline double operator()(int i, int j) const;
		inline double& operator()(int i, int j);
		friend Matrix operator+(const Matrix& A, const Matrix& B);
		friend Matrix operator+(const Matrix& A, double x);
		friend Matrix operator*(const Matrix& A, const Matrix& B);
		friend Matrix operator*(const Matrix& A, double x);

	private:
		int     r;    // number of rows
		int     c;    // number of columns
		double* d;    // array of doubles for matrix contents

};

std::ostream& operator<<(std::ostream& os, const Matrix& A);

inline double Matrix::operator()(int i, int j) const
{
	return d[i*c + j];
}

inline double& Matrix::operator()(int i, int j)
{
	return d[i*c + j];
}

#endif MATRIX_H_ALREADY_INCLUDEDA