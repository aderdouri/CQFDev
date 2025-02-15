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


#include "..\CppUnitTest\TestHarness.h"
#include "HJM.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <memory>
#include <iomanip>
#include <chrono>
#include <ctime>


namespace
{
	//
	// Returns a vector whose elements are the cumulative sums of the elements of the argument.
	//
	void cumsum(std::vector<double> const& ZCBPriceVect, std::vector<double>& cumsumVect) 
	{
		double csum = 0.0;
		for (unsigned int i = 0; i < ZCBPriceVect.size(); ++i)
		{
			csum += ZCBPriceVect[i];
			cumsumVect.push_back(csum);
		}
	}

	//
	// Calculate an arithmetic mean given a vector
	// 
	double mean(std::vector<double> const& v)
	{
		double sum = std::accumulate(v.begin(), v.end(), 0.0);
		return(sum / v.size());
	}


}

TEST(HJM_Model, ZeroCouponBondPricing)
{
	std::cout <<"Zero Coupon Bond Pricing using HJM"<< std::endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	std::cout << "Started computation at: " << std::ctime(&start_time) << std::endl;

	std::vector<double> ZCBPriceVect;

	int NBSimu = 1000;
	double dt = 0.01;
	double tenor = 5.0;
	int maturity = 2;

	// use defaut setting for the HJM model
	for (int simu = 0; simu < NBSimu; ++simu)
	{
		std::shared_ptr<HJM> hjm(new HJM(dt, maturity, tenor));
		hjm->price();
		ZCBPriceVect.push_back(hjm->getPrice());
	}
	std::cout << "Z(0," << maturity << ") : " << mean(ZCBPriceVect) << std::endl;

	std::vector<double> cumsumZCBPriceVect;
	cumsum(ZCBPriceVect, cumsumZCBPriceVect);
	
	// generate a convergence diagram to plot
	std::ofstream ofs;
	ofs.open("HJM_MC_convergence_diagram.csv");
	int n = 1;
	for (auto& elem : cumsumZCBPriceVect)
	{
		ofs << (elem / n) << ";";
		n++;
	}

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "finished computation at: " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";

}