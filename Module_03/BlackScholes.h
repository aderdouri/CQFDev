//
// Date: Sunday, April 18, 2015
// File name: BlackScholes.h
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

#if !defined (BLACK_SCHOLES_H_ALREADY_INCLUDED)
#define BLACK_SCHOLES_H_ALREADY_INCLUDED

class BlackScholes
{
public:
	BlackScholes(double S, double E, double r, double sigma, double T, double t=0.0);
	void price();
	double getPrice() const;
	double normcdf(const double& x) const;
	double d1() const;
	double d2() const;
	double DiscountFactor() const;

private:

	double _S;
	double _E;
	double _r;
	double _sigma;
	double _T;
	double _t;
	double _price;
};
#endif BLACK_SCHOLES_H_ALREADY_INCLUDED