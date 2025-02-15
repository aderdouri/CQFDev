//
// Date: Sunday, April 18, 2015
// File name: BlackScholes.cpp
// Version: 1 
// Author: Abderrazak DERDOURI
// Subject: Certificate in Quantitative Finance Module 3 Exam
//
// Description: class BlackScholes
//	
//
// Notes:
// Revision History:
//

#define _USE_MATH_DEFINES
#include "BlackSCholes.h"
#include <cmath>


BlackScholes::BlackScholes(double S, double E, double r, double sigma, double T, double t) :
_S(S), _E(E), _r(r), _sigma(sigma), _T(T), _t(t)
{
	_price = 0;
}
void BlackScholes::price()
{
	_price = (DiscountFactor()*normcdf(d2()));
}


double BlackScholes::d1() const
{
	return ( (log(_S / _E) + (_r + 0.5 * _sigma*_sigma) * (_T - _t)) / (_sigma * std::sqrt(_T - _t)) );
}

double BlackScholes::d2() const
{
	return ( d1() - std::sqrt(_T - _t)*_sigma );
}

double BlackScholes::DiscountFactor() const
{
	return std::exp(-_r*_T);
}

double BlackScholes::getPrice() const
{
	return _price;
}

// Cumulative density function
double BlackScholes::normcdf(const double& x) const 
{
	double k = 1.0 / (1.0 + 0.2316419*x);
	double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

	if (x >= 0.0) 
	{
		return (1.0 - (1.0 / (std::pow(2 * M_PI, 0.5)))*exp(-0.5*x*x) * k_sum);
	}
	else 
	{
		return 1.0 - normcdf(-x);
	}
}