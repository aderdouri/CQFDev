//
// Date: Sunday, Mai 21, 2015
// File name: HJM.h
// Version: 1
// Author: Abderrazak DERDOURI
//
// Subject: Certificate in Quantitative Finance Module 4 Exam
//
// Description: Class HJM
//
//
// Notes:
// Revision History:
//

#if !defined(HJM_H_ALREADY_INCLUDED)
#define HJM_H_ALREADY_INCLUDED

#include <vector>

class HJM
{
public:
	HJM(double tStep = 0.01, int maturity = 10, int _tenor = 51);
	double Vol_1(double Tau);
	double Vol_2(double Tau);
	double Vol_3(double Tau);
	double m(double Tau);
	double rnorm(double mean = 0.0, double std = 1.0) const;
	void price();
	double getPrice() const;

private:
	double _tStep;
	int _maturity;
	int _tenor;
	double _price;
	std::vector<double> _tenorVect;
	std::vector<double> _observedFwdCurve;
};
#endif // HJM_H_ALREADY_INCLUDED