//
// Date: Sunday, April 18, 2015
// File name: ExplicitFiniteDifference.cpp
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: Certificate in Quantitative Finance
//
// Description: Implement the Explicit Finite Difference Method using a backward scheme.
//
//
// Notes:
// Revision History:
//

#include "ExplicitFiniteDifference.h"
#include "../Matrix/Matrix.h"

ExplicitFiniteDifference::ExplicitFiniteDifference(double S, double E, double T, double r, double d, double sigma, int NAS) : _S(S), _E(E), _T(T), _r(r), _d(d), _sigma(sigma), _NAS(NAS)
{
	_price = 0.0;
}
double ExplicitFiniteDifference::alpha(int n, double dt)
{
	return (0.5 * (_sigma * _sigma) * (n * n) * dt - 0.5 * n * _r * dt);
}

double ExplicitFiniteDifference::beta(int n, double dt)
{
	return (1 - (_sigma * _sigma) * (n * n) * dt - _r * dt);
}

double ExplicitFiniteDifference::gamma(int n, double dt)
{
	return (0.5 * (_sigma * _sigma) * (n * n) * dt + 0.5 * n * _r * dt);
}
//
// Price a binary Call option unsing the Explicit Finite Difference Method
// and a backward scheme.
//
void ExplicitFiniteDifference::price()
{
	//
	// OPTION_VALUE
	//
	int NAS = _NAS;			// Number os asset steps
	double S = _S;			// Asset initial value
	double Strike = _E;		// Strike
	double Expiration = _T; // Experiy date
	double Vol = _sigma;	// Volatility
	double Int_Rate = _r;	// Interest Rate

	double dS = S / NAS;
	NAS = static_cast<int>(std::floor(Strike / dS) * 2);
	int SGridPt = static_cast<int>(S / dS);
	double dt = dS * dS / (Vol * Vol * 4 * Strike * Strike);
	int NTS = static_cast<int>(std::floor(Expiration / dt) + 1);
	dt = Expiration / NTS;

	Matrix V = Matrix(NAS + 1, NTS + 1);

	for (int n = 1; n <= NAS; n++)
	{
		V(n, NTS) = ((n * dS > Strike) ? 1.0 : 0.0);
	}
	// at S = 0;
	// V(m-1, 0) = (1 - r dt) * V(m,0)
	for (int m = NTS; m >= 2; m--)
	{
		V(1, m - 1) = (1 - Int_Rate * dt) * V(1, m);
	}
	for (int m = NTS; m >= 2; m--)
	{
		for (int n = 2; n <= NAS - 1; n++)
		{
			V(n, m - 1) = (alpha(n, dt) * V(n - 1, m) + beta(n, dt) * V(n, m) + gamma(n, dt) * V(n + 1, m));
		}
		// Satisfy boundary conditions
		V(NAS, m - 1) = (alpha(NAS, dt) - gamma(NAS, dt)) * V(NAS - 1, m) + (beta(NAS, dt) + 2 * gamma(NAS, dt)) * V(NAS, m);
	}

	_price = V(SGridPt, 1);
}
double ExplicitFiniteDifference::getPrice() const
{
	return _price;
}