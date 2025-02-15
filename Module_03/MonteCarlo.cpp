//
// Date: Sunday, April 18, 2015
// File name: MonteCarlo.cpp
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: Certificate in Quantitative Finance Module 3 Exam
//
// Description: Price a binary call option using Monte Carlo method
//				and the Milstein scheme
//
//
// Notes:
// Revision History:
//

#include "MonteCarlo.h"
#include "../Matrix/Matrix.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

MonteCarlo::MonteCarlo(double S, double E, double r, double sigma, double T, double tStep, int NAS, int NbSimu) : _S(S), _E(E), _r(r), _sigma(sigma), _T(T),
																												  _tStep(tStep), _NAS(NAS), _NbSimu(NbSimu)
{
	_price = 0;
}
//
// price a binary call option using Monte Carlo method
// and the Milstein scheme
//
void MonteCarlo::price()
{
	Matrix PathMatrix = Matrix(_NAS, _NbSimu);
	std::vector<double> AssetPriceAtExpiration(_NbSimu);

	for (int nbSimu = 0; nbSimu < _NbSimu; ++nbSimu)
	{
		double CurrentAssetPrice = _S;
		for (int tStepCounter = 0; tStepCounter < _NAS; ++tStepCounter)
		{
			double phi = rnorm();
			CurrentAssetPrice *= (1 + _r * _tStep + _sigma * phi * std::sqrt(_tStep) + 0.5 * _sigma * _sigma * (phi * phi - 1) * _tStep);
			PathMatrix(tStepCounter, nbSimu) = CurrentAssetPrice;
		}
	}

	// Calculate a Binary Call price
	std::vector<double> PayOffVect(_NbSimu);
	for (int nbSimu = 0; nbSimu < _NbSimu; ++nbSimu)
	{
		PayOffVect[nbSimu] = (PathMatrix(_NAS - 1, nbSimu) > _E) ? 1.0 : 0.0;
	}
	_price = DiscountFactor() * mean(PayOffVect);
}

//
// generate a rondom normal number
//
double MonteCarlo::rnorm(double mean, double std) const
{
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;

	if (use_last) // use value from previous call
	{
		y1 = y2;
		use_last = 0;
	}
	else
	{
		do
		{
			x1 = 2 * (double)rand() / RAND_MAX - 1; // rand in [0,1]
			x2 = 2 * (double)rand() / RAND_MAX - 1;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = (double)sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return (double)(mean + y1 * std);
}

//
// Calculate an arithmetic mean given a vector
//
double MonteCarlo::mean(std::vector<double> &v) const
{
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	return (sum / v.size());
}

//
// continuous discounting facor
//
double MonteCarlo::DiscountFactor() const
{
	return std::exp(-_r * _T);
}

double MonteCarlo::getPrice() const
{
	return _price;
}