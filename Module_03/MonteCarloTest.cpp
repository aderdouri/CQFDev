//
// Date: Sunday, April 18, 2015
// File name: MonteCarloTest.cpp
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: CQF Exam module 3
//
// Description: Monte Carlo Method Milstein scheme Test
//
//
// Notes:
// Revision History:
//

#include "../CppUnitTest/TestHarness.h"
#include "BlackScholes.h"
#include "MonteCarlo.h"
#include "../Matrix/Matrix.h"
#include <iostream>
#include <fstream>
#include <memory>

namespace
{
	void printHeaderBinaryOptionPriceFile(const char *fileName)
	{
		std::ofstream ofs;
		ofs.open(fileName);
		ofs << "Asset, Strike, InterestRate, Volatility, Expiration, TimeStep";
		ofs << ", NumberAssetStep, NumbreOfSimulation, BS Price, MC Price, ErrorWithBS, ErrorWithBSPercentage " << "\n";
		ofs.close();
	}

	void printBinaryOptionPriceFile(const char *fileName, double Asset, double Strike, double InterestRate, double Volatility, double Expiration, double TimeStep, int NumberAssetStep, int NumbreOfSimulation, double BSPrice, double MCPrice, double ErrorWithBS, double ErrorWithBSPercentage)
	{
		std::ofstream ofs;
		ofs.open(fileName, std::ios::app);

		ofs << Asset << ",";
		ofs << Strike << ",";
		ofs << InterestRate << ",";
		ofs << Volatility << ",";
		ofs << Expiration << ",";
		ofs << TimeStep << ",";
		ofs << NumberAssetStep << ",";
		ofs << NumbreOfSimulation << ",";
		ofs << BSPrice << ",";
		ofs << MCPrice << ",";
		ofs << ErrorWithBS << ",";
		ofs << ErrorWithBSPercentage << "," << "\n";

		ofs.close();
	}
}

//
// Varying the number of simulations
//
TEST(BinaryOptionPricing, MonteCarloTest1)
{
	double Asset = 100.0;
	double Strike = 100.0;
	double InterestRate = 0.05;
	double Volatility = 0.2;
	double Expiration = 1.0;

	int NumberAssetStep = 100;
	double TimeStep = Expiration / NumberAssetStep;
	int NumbreOfSimulation = 1000;

	printHeaderBinaryOptionPriceFile("binaryCallMCPriceTest1.csv");

	for (int i = 1; i <= 10; ++i)
	{
		// Price with Black and Scholes
		std::shared_ptr<BlackScholes> BS(new BlackScholes(Asset, Strike, InterestRate, Volatility, Expiration));
		BS->price();

		// Price with Monte Carlo
		std::shared_ptr<MonteCarlo> MC(new MonteCarlo(Asset, Strike, InterestRate, Volatility, Expiration, TimeStep, NumberAssetStep, NumbreOfSimulation));
		MC->price();

		double err = BS->getPrice() - MC->getPrice();
		double BSFormula = (BS->getPrice() > 0.0 ? BS->getPrice() : 1); // to avoid the the divding by zero case

		printBinaryOptionPriceFile("binaryCallMCPriceTest1.csv", Asset, Strike, InterestRate, Volatility, Expiration, TimeStep, NumberAssetStep, NumbreOfSimulation, BS->getPrice(), MC->getPrice(), err, std::abs(err / BSFormula));

		NumbreOfSimulation += 1000;
	}
}

//
// Varying the time step size
//

TEST(BinaryOptionPricing, MonteCarloTest2)
{
	double Asset = 100.0;
	double Strike = 100.0;
	double InterestRate = 0.05;
	double Volatility = 0.2;
	double Expiration = 1.0;

	int NumberAssetStep = 100;
	double TimeStep = Expiration / NumberAssetStep;
	int NumbreOfSimulation = 10000;

	printHeaderBinaryOptionPriceFile("binaryCallMCPriceTest2.csv");

	for (int i = 1; i <= 10; ++i)
	{
		// Price with Black and Scholes
		std::shared_ptr<BlackScholes> BS(new BlackScholes(Asset, Strike, InterestRate, Volatility, Expiration));
		BS->price();

		// Price with Monte Carlo
		std::shared_ptr<MonteCarlo> MC(new MonteCarlo(Asset, Strike, InterestRate, Volatility, Expiration, TimeStep, NumberAssetStep, NumbreOfSimulation));
		MC->price();

		double err = BS->getPrice() - MC->getPrice();
		double BSFormula = (BS->getPrice() > 0.0 ? BS->getPrice() : 1); // to avoid the the divding by zero case

		printBinaryOptionPriceFile("binaryCallMCPriceTest2.csv", Asset, Strike, InterestRate, Volatility, Expiration, TimeStep, NumberAssetStep, NumbreOfSimulation, BS->getPrice(), MC->getPrice(), err, std::abs(err / BSFormula));

		NumberAssetStep += 100;
		TimeStep = Expiration / NumberAssetStep;
	}
}

//
// Print prices using both BS and MC
//
TEST(BinaryOptionPricing, MonteCarloTest3)
{
	double Asset = 100.0;
	double Strike = 100.0;
	double InterestRate = 0.05;
	double Volatility = 0.2;
	double Expiration = 1.0;

	int NumberAssetStep = 100;
	double TimeStep = Expiration / NumberAssetStep;
	int NumbreOfSimulation = 10000;

	// Price with Black and Scholes
	std::shared_ptr<BlackScholes> BS(new BlackScholes(Asset, Strike, InterestRate, Volatility, Expiration));
	BS->price();

	std::cout << "============================================" << std::endl;
	std::cout << "Black and Scholes Call Price: " << BS->getPrice() << std::endl;

	// Price with Monte Carlo
	std::shared_ptr<MonteCarlo> MC(new MonteCarlo(Asset, Strike, InterestRate, Volatility, Expiration, TimeStep, NumberAssetStep, NumbreOfSimulation));
	MC->price();

	std::cout << "============================================" << std::endl;
	std::cout << "Monte Carlo Call Price: " << MC->getPrice() << std::endl;
	std::cout << "============================================" << std::endl;
}
