//
// Date: Sunday, April 18, 2015
// File name: ExplicitFiniteDifference.h
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

#if !defined(EXPLICIT_FINITE_DIFFERENCE_H_ALREADY_INCLUDED)
#define EXPLICIT_FINITE_DIFFERENCE_H_ALREADY_INCLUDED

class ExplicitFiniteDifference
{
public:
	ExplicitFiniteDifference(double S, double E, double T, double r, double d, double sigma, int NAS);
	void price();
	double getPrice() const;

	double alpha(int n, double dt);
	double beta(int n, double dt);
	double gamma(int n, double dt);

private:
	double _S;
	double _E;
	double _r;
	double _d;
	double _sigma;
	double _T;
	double _t;
	double _price;
	int _NAS;
};
#endif // EXPLICIT_FINITE_DIFFERENCE_H_ALREADY_INCLUDED