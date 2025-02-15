//
// Date: Sunday, April 18, 2015
// File name: ExplicitFiniteDifferenceMethodTest.cpp
// Version: 1
// Author: Abderrazak DERDOURI
// Subject: CQF Exam module 3
//
// Description: Explicit Finite Difference Method Backward Scheme Test
//
//
// Notes:
// Revision History:
//

#include "../CppUnitTest/TestHarness.h"
#include "BlackScholes.h"
#include "MonteCarlo.h"
#include "../Matrix/Matrix.h"
#include "ExplicitFiniteDifference.h"
#include <iostream>
#include <fstream>
#include <memory>

namespace
{
	void printHeaderBinaryOptionPriceFile(const char *fileName)
	{
		std::ofstream ofs;
		ofs.open(fileName);
		ofs << "Asset, Strike, IntRate, Vol, Expiration";
		ofs << ", NAS, BS Price, FDM Price, ErrWithBS, ErrWithBSPer" << "\n";
		ofs.close();
	}

	void printBinaryOptionPriceFile(const char *fileName, double Asset, double Strike, double InterestRate, double Volatility, double Expiration, int NumberAssetStep, double BSPrice, double FDMPrice, double ErrorWithBS, double ErrorWithBSPercentage)
	{
		std::ofstream ofs;
		ofs.open(fileName, std::ios::app);

		ofs << Asset << ",";
		ofs << Strike << ",";
		ofs << InterestRate << ",";
		ofs << Volatility << ",";
		ofs << Expiration << ",";
		ofs << NumberAssetStep << ",";
		ofs << BSPrice << ",";
		ofs << FDMPrice << ",";
		ofs << ErrorWithBS << ",";
		ofs << ErrorWithBSPercentage << "," << "\n";

		ofs.close();
	}
}

//
// Varying the nummber of asset step and Expiration
//
TEST(BinaryOptionPricing, ExplicitFiniteDifferenceBackwardSchemeTest1)
{
	double Asset = 110;
	double Strike = 100.0;
	double InterestRate = 0.05;
	double Volatility = 0.2;
	double Expiration = 1.0;
	double Dividend = 0.0;

	int NumberAssetStep = 80;

	printHeaderBinaryOptionPriceFile("binaryCallFDMPrice.csv");

	for (int Asset = 60; Asset <= 110; Asset += 10)
	{
		for (double Expiration = 0.2; Expiration <= 1.0; Expiration += 0.2)
		{
			// Price with Black and Scholes
			std::shared_ptr<BlackScholes> BS(new BlackScholes(Asset, Strike, InterestRate, Volatility, Expiration));
			BS->price();

			// Price with a Backward Scheme Explicit Finite Difference
			std::shared_ptr<ExplicitFiniteDifference> FDM(new ExplicitFiniteDifference(Asset, Strike, Expiration, InterestRate, Dividend, Volatility, NumberAssetStep));
			FDM->price();

			double err = BS->getPrice() - FDM->getPrice();
			double BSFormula = (BS->getPrice() > 0.0 ? BS->getPrice() : 1); // to avoid the the divding by zero case
			printBinaryOptionPriceFile("binaryCallFDMPrice.csv", Asset, Strike, InterestRate, Volatility, Expiration, NumberAssetStep, BS->getPrice(), FDM->getPrice(), err, std::abs(err / BSFormula));
		}
	}
}

//
// Print prices using both BS and FDM
//
TEST(BinaryOptionPricing, ExplicitFiniteDifferenceBackwardSchemeTest2)
{
	double Asset = 100;
	double Strike = 100.0;
	double InterestRate = 0.05;
	double Volatility = 0.2;
	double Expiration = 1.0;
	double Dividend = 0.0;

	int NumberAssetStep = 80;

	// Price with Black and Scholes
	std::shared_ptr<BlackScholes> BS(new BlackScholes(Asset, Strike, InterestRate, Volatility, Expiration));
	BS->price();

	std::cout << "============================================" << std::endl;
	std::cout << "Black and Scholes Call Price: " << BS->getPrice() << std::endl;

	// Price with a Backward Scheme Explicit Finite Difference
	std::shared_ptr<ExplicitFiniteDifference> FDM(new ExplicitFiniteDifference(Asset, Strike, Expiration, InterestRate, Dividend, Volatility, NumberAssetStep));
	FDM->price();

	std::cout << "============================================" << std::endl;
	std::cout << "Finite Differnce Method Call Price: " << FDM->getPrice() << std::endl;
	std::cout << "============================================" << std::endl;
}
