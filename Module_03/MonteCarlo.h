//
// Date: Sunday, April 18, 2015
// File name: MonteCarlo.h
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: Certificate in Quantitative Finance Module 3 Exam
//
// Description: Class MonteCarlo
//
//
// Notes:
// Revision History:
//

#if !defined(MONTE_CARLO_H_ALREADY_INCLUDED)
#define MONTE_CARLO_H_ALREADY_INCLUDED

#include <vector>

class MonteCarlo
{
public:
	MonteCarlo(double S, double E, double r, double sigma, double T, double tStep = 0.01, int NAS = 1000, int NbSimu = 10000);

	void price();
	double getPrice() const;
	double rnorm(double mean = 0.0, double std = 1.0) const;
	double mean(std::vector<double> &) const;
	double DiscountFactor() const;

private:
	double _S;
	double _E;
	double _r;
	double _sigma;
	double _T;

	double _tStep;
	int _NAS;
	int _NbSimu;
	double _price;
};
#endif // MONTE_CARLO_H_ALREADY_INCLUDED