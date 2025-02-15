//
// Date: Sunday, April 18, 2015
// File name: HJM.cpp
// Version: 1 
// Author: Abderrazak DERDOURI
//
// Subject: Certificate in Quantitative Finance Module 4 Exam
//
// Description: Generate a whole forward rate for the HJM model
//				
//	
//
// Notes:
// Revision History:
//

#include "HJM.h"
#include "Matrix.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <random>


HJM::HJM(double tStep, int maturity, int NbTenor) :_tStep(tStep), _maturity(maturity), _tenor(NbTenor), _price(0.0)
{
	//
	//First row is the last observed forward curve
	//from last row in the priveded HJM PCA file / BOE data
	//
	_observedFwdCurve = {
		0.046138361, 0.045251174, 0.042915805, 0.04283311, 0.043497719, 0.044053792
		, 0.044439518, 0.044708496, 0.04490347, 0.045056615, 0.045184474, 0.045294052
		, 0.045386152, 0.045458337, 0.045507803, 0.045534188, 0.045541867, 0.045534237
		, 0.045513128, 0.045477583, 0.04542292, 0.045344477, 0.04523777, 0.045097856
		, 0.044925591, 0.04472353, 0.044494505, 0.044242804, 0.043973184, 0.043690404
		, 0.043399223, 0.043104398, 0.042810688, 0.042522852, 0.042244909, 0.041978295
		, 0.041723875, 0.041482518, 0.04125509, 0.041042459, 0.040845492, 0.040665047
		, 0.040501255, 0.040353009, 0.040219084, 0.040098253, 0.039989288
		, 0.039890964, 0.039802053, 0.039721437, 0.03964844
	};

	int maxTenor = static_cast<int>(std::floor(_tenor / 2));
	double tenor = 0.0;
	while (tenor <= maxTenor)
	{
		_tenorVect.push_back(tenor);
		tenor += 0.5;
	}

}
double HJM::Vol_1(double Tau)
{
	return 0.0064306548; //first vol factor simplified to flat
}
double HJM::Vol_2(double Tau)
{
	return (-0.0035565431 + Tau * (-0.0005683999) + std::pow(Tau, 2) * 0.0001181915 + std::pow(Tau, 3) * (-0.0000035939));
}
double HJM::Vol_3(double Tau)
{
	return (-0.0047506715 + Tau * 0.0017541783 + std::pow(Tau, 2) * (-0.0001415249) + std::pow(Tau, 3) * 0.0000031274);
}

//
//This funciton carries out integration for all principal factors. 
//It uses the fact that volatility is function of time in HJM model
//
double HJM::m(double Tau)
{
	if (Tau == 0.0)
	{
		return 0.0;
	}

	double dTau = 0.01;     //initial step
	int N = static_cast<int>(std::floor(Tau / dTau));
	dTau = Tau / N;         //step for Tau

	// using trapezium rule to compute M1
	double M1 = 0.5 * Vol_1(0);
	for (int i = 1; i <= N - 1; i++)
	{
		M1 = M1 + Vol_1(i * dTau);  // not adjusted by *0.5 because of repeating terms x1...xn-1 - see trapezoidal rule
	}

	M1 = M1 + 0.5 * Vol_1(Tau);
	M1 = M1 * dTau;
	M1 = Vol_1(Tau) * M1; // Vol_1 represents v_i(t,T) and M1 represents the result of numerical integration

	// using trapezium rule to compute M2
	double M2 = 0.5 * Vol_2(0);
	for (int i = 1; i <= N - 1; i++)
	{
		M2 = M2 + Vol_2(i * dTau);
	}

	M2 = M2 + 0.5 * Vol_2(Tau);
	M2 = M2 * dTau;
	M2 = Vol_2(Tau) * M2;

	// using trapezium rule to compute M3
	double M3 = 0.5 * Vol_3(0);
	for (int i = 1; i <= N - 1; i++)
	{
		M3 = M3 + Vol_3(i * dTau);
	}

	M3 = M3 + 0.5 * Vol_3(Tau);
	M3 = M3 * dTau;
	M3 = Vol_3(Tau) * M3;

	return (M1 + M2 + M3); // sum for multi-factor
}

//
// generate a rondom normal number
//
double HJM::rnorm(double mean, double std) const
{
	double x1, x2, w, y1;
	static double y2;
	static int use_last = 0;

	if (use_last)  // use value from previous call
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
// price a ZCB using the HJM model
//
void HJM::price()
{
	int nbSimu = static_cast<int>(std::floor(_maturity / _tStep));
	Matrix PathMatrix = Matrix(nbSimu, _tenor);

	//
	// We simulate by f(t+dt)=f(t) + dfbar where Musiela HJM SDE is dfbar =  m(t)*dt+SUM(Vol_i*phi)*SQRT(dt)+dF/dtau*dt
	//

	double dt = _tStep;
	// first row
	for (int tenor = 0; tenor < _tenor; ++tenor)
		PathMatrix(0, tenor) = _observedFwdCurve[tenor];

	for (int simu = 1; simu < nbSimu; ++simu)
	{
		for (int tenor = 0; tenor < _tenor - 1; ++tenor)
		{
			double dF = PathMatrix(simu - 1, tenor + 1) - PathMatrix(simu - 1, tenor);
			double dtau = _tenorVect[tenor + 1] - _tenorVect[tenor];
			double t = _tenorVect[tenor];
			double x = (dF / dtau)*dt;
			double df = PathMatrix(simu - 1, tenor) + m(t)*dt + (Vol_1(t)*rnorm() + Vol_2(t)*rnorm() + Vol_3(t)*rnorm())*std::sqrt(dt) + (dF / dtau)*dt;
			PathMatrix(simu, tenor) = df;
		}
		// case tenor == NbTenor==25years
		double dF = PathMatrix(simu - 1, _tenor - 1) - PathMatrix(simu - 1, _tenor - 2);
		double dtau = _tenorVect[_tenor - 1] - _tenorVect[_tenor - 2];
		double t = _tenorVect[_tenor - 1];
		double x = (dF / dtau)*dt;
		double df = PathMatrix(simu - 1, _tenor - 1) + m(t)*dt + (Vol_1(t)*rnorm() + Vol_2(t)*rnorm() + Vol_3(t)*rnorm())*std::sqrt(dt) + (dF / dtau)*dt;
		PathMatrix(simu, _tenor - 1) = df;
	}

	/*std::ofstream ofs;
	ofs.open("HJM_MC.csv");
	for (int simu = 0; simu < _NbSimu; ++simu)
	{
		for (int tenor = 0; tenor < _NbTenor; ++tenor)
		{
			ofs << PathMatrix(simu, tenor) << ",";
		}
		ofs << "\n";
	}
	ofs.close();*/

	std::vector<double> ZCBPrice;
	for (int t = 0; t < _maturity; ++t)
	{
		ZCBPrice.push_back(PathMatrix(t, 0));
	}
	_price = std::exp(-(std::accumulate(ZCBPrice.begin(), ZCBPrice.end(), 0.0))*dt);
}

double HJM::getPrice() const
{
	return _price;
}