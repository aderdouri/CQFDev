//
// Date: Sunday, Mai 21, 2015
// File name: HJMTest.cpp
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: CQF Exam module 4
//
// Description: HJM Test
//
//
// Notes:
// Revision History:
//

#include "../CppUnitTest/TestHarness.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace
{

	// P: survival probabiliy vector
	// LP : Leg premium vector
	// D: discount factor vector
	// Dt: time step decomposition vector
	// S: spreads vector
	// RR: recovery rate

	void survivalProbabilty(std::vector<double> &P, std::vector<double> const &D, std::vector<int> const &Dt, std::vector<double> const &S, double RR, int NPeriod)
	{
		double L = (1 - RR);
		std::vector<double> LP; // Leg premium
		LP.resize(NPeriod);

		P[0] = 1.0; // survival probability at time zero
		P[1] = L / (L + Dt[1] * S[1]);
		LP[0] = S[0];

		// std::cout << "Survival Probability 1 : " << P[1] << std::endl;

		for (int N = 2; N <= NPeriod; ++N)
		{
			double sum = 0.0;
			for (int n = 1; n < N; ++n)
			{
				sum += (D[n] * (L * P[n - 1] - (L + Dt[n] * S[N]) * P[n])) / (D[N] * (L + Dt[N] * S[N]));
			}
			sum += (P[N - 1] * L) / (L + Dt[N] * S[N]);
			P[N] = sum;
			// std::cout << "Survival Probability: " << sum << std::endl;
		}
	}

	void discreteHazardRates(std::vector<double> const &P, std::vector<double> &lamda, int NPeriod)
	{
		for (int m = 1; m <= NPeriod; ++m)
		{
			std::cout << P[m] << "," << P[m - 1] << std::endl;
			lamda[m] = -std::log(P[m] / P[m - 1]);
		}
	}

	//
	// interpolation between two years
	//
	double interpolateDiscountCurve(double d1, double d2, double tau, double tau1, double tau2)
	{
		return (std::pow(d2, (tau - tau1) / (tau2 - tau1)) * std::pow(d1, (tau2 - tau) / (tau2 - tau1)));
	}

	//
	// interpolation between two years
	//
	double interpolateCreditCurve(double cds1, double cds2, double tau, double tau1, double tau2)
	{
		return (((tau - tau1) / (tau2 - tau1)) * cds2 + ((tau2 - tau) / (tau2 - tau1)) * cds1);
	}

}

/*TEST(ABC, Boostrapping)
{
	std::cout << "Survival Probability bootstrapping" << std::endl;

	double RR = 0.5; // recovery rate
	std::vector<double> P = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // survival probabiliy
	std::vector<double> D = { 0, 0.9803, 0.9514, 0.9159, 0.8756, 0.8328 }; // discount factor
	std::vector<int> Dt = { 0, 1, 1, 1, 1, 1 }; // time step decomposition
	std::vector<double> S = { 0, 0.0029, 0.0039, 0.0046, 0.0052, 0.0057 }; // spread.

	survivalProbabilty(P, D, Dt, S, RR);
}*/

/*TEST(XYZ, Boostrapping)
{
	std::cout << "Survival Probability bootstrapping" << std::endl;

	double RR = 0.1; // recovery rate
	std::vector<double> P = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // survival probabiliy
	std::vector<double> D = { 0, 0.9803, 0.9514, 0.9159, 0.8756, 0.8328 }; // discount factor
	std::vector<int> Dt = { 0, 1, 1, 1, 1, 1 }; // time step decomposition
	std::vector<double> S = { 0, 0.91, 0.78, 0.74, 0.69, 0.65 }; // spread.

	survivalProbabilty(P, D, Dt, S, RR);
}*/

TEST(WFC, Boostrapping)
{
	std::cout << "Survival Probability bootstrapping" << std::endl;
	const int NPeriod = 8;

	double RR = 0.5;				// recovery rate
	std::vector<double> P(NPeriod); // survival probabiliy
	std::vector<double> D(NPeriod); // discount factor
	D[0] = 0.0;						// year 0
	D[1] = 0.97;					// year 1
	D[2] = 0.94;					// year 2
	D[3] = 0.92;					// year 3
	D[5] = 0.86;					// year 5
	D[7] = 0.81;					// year 7

	// interpolate between year 3 and year 5 to obtain year 4 discount factor
	double d4 = interpolateDiscountCurve(D[3], D[5], 4, 3, 5);
	D[4] = d4; // year 4
	// interpolate between year 5 and year 7 to obtain year 6 discount factor
	double d6 = interpolateDiscountCurve(D[5], D[7], 6, 5, 7);
	D[6] = d6; // year 6

	std::vector<int> Dt = {0, 1, 1, 1, 1, 1, 1, 1}; // time step decomposition
	std::vector<double> S(8);						// spread.
	S[0] = 0.0;										// year 0
	S[1] = 0.0050;									// year 1
	S[2] = 0.0077;									// year 2
	S[3] = 0.0094;									// year 3
	S[5] = 0.0125;									// year 5
	S[7] = 0.0133;									// year 7

	// interpolate between year 3 and year 5 to obtain year 4 spread
	double S4 = interpolateCreditCurve(S[3], S[5], 4, 3, 5);
	S[4] = S4; // year 4
	// interpolate between year 5 and year 7 to obtain year 6 spread
	double S6 = interpolateCreditCurve(S[5], S[7], 6, 5, 7);
	S[6] = S6; // year 6

	survivalProbabilty(P, D, Dt, S, RR, NPeriod);

	/*std::cout << "--------------Begin Survival---------" << std::endl;
	for (auto elem : P)
		std::cout << elem << std::endl;
	std::cout << "--------------end Survival---------" << std::endl;*/

	std::vector<double> lamda(NPeriod);
	discreteHazardRates(P, lamda, NPeriod);

	std::cout << "--------------Begin lamda---------" << std::endl;
	for (auto elem : lamda)
		std::cout << elem << std::endl;
	std::cout << "--------------End lamda---------" << std::endl;
}

TEST(CCMO, Boostrapping)
{
	std::cout << "Survival Probability bootstrapping" << std::endl;
	const int NPeriod = 8;

	double RR = 0.1;				// recovery rate
	std::vector<double> P(NPeriod); // survival probabiliy
	std::vector<double> D(NPeriod); // discount factor
	D[0] = 0.0;						// year 0
	D[1] = 0.97;					// year 1
	D[2] = 0.94;					// year 2
	D[3] = 0.92;					// year 3
	D[5] = 0.86;					// year 5
	D[7] = 0.81;					// year 7

	// interpolate between year 3 and year 5 to obtain year 4 discount factor
	double d4 = interpolateDiscountCurve(D[3], D[5], 4, 3, 5);
	D[4] = d4; // year 4
	// interpolate between year 5 and year 7 to obtain year 6 discount factor
	double d6 = interpolateDiscountCurve(D[5], D[7], 6, 5, 7);
	D[6] = d6; // year 6

	std::vector<int> Dt = {0, 1, 1, 1, 1, 1, 1, 1}; // time step decomposition
	std::vector<double> S(NPeriod);					// spread.
	S[0] = 0.0;										// year 0
	S[1] = 0.0751;									// year 1
	S[2] = 0.1164;									// year 2
	S[3] = 0.1874;									// year 3
	S[5] = 0.4156;									// year 5
	S[7] = 0.6083;									// year 7

	// interpolate between year 3 and year 5 to obtain year 4 spread
	double S4 = interpolateCreditCurve(S[3], S[5], 4, 3, 5);
	S[4] = S4; // year 4
	// interpolate between year 5 and year 7 to obtain year 6 spread
	double S6 = interpolateCreditCurve(S[5], S[7], 6, 5, 7);
	S[6] = S6; // year 6

	survivalProbabilty(P, D, Dt, S, RR, NPeriod);
	/*std::cout << "--------------Begin Survival---------" << std::endl;
	for (auto elem : P)
		std::cout << elem << std::endl;
	std::cout << "--------------end Survival---------" << std::endl;*/

	std::vector<double> lamda(NPeriod);
	discreteHazardRates(P, lamda, NPeriod);
	std::cout << "--------------Begin lamda---------" << std::endl;
	for (auto elem : lamda)
		std::cout << elem << std::endl;
	std::cout << "--------------End lamda---------" << std::endl;
}