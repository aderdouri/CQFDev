//
// Date: Sunday, Mai 21, 2015
// File name: bondTest.cpp
// Version: 1 
// Author: Abderrazak DERDOURI
// Subject: CQF Exam module 4
//
// Description: bonds calculation Test
//	
//
// Notes:
// Revision History:
//


#include "..\CppUnitTest\TestHarness.h"
#include <iostream>

namespace
{
	double V(double x)
	{
		return (3 * (exp(-x) + exp(-2 * x) + exp(-3 * x) + exp(-4 * x) + exp(-5 * x)) + 100 * exp(-5 * x) - 90);
	}

	double dV(double x)
	{
		return (3 * (-exp(-x) - 2 * exp(-2 * x) - 3 * exp(-3 * x) - 4 * exp(-4 * x) - 5 * exp(-5 * x)) - 5 * 100 * exp(-5 * x));
	}

	double d2V(double x)
	{
		return (3 * (exp(-x) + 4 * exp(-2 * x) + 9 * exp(-3 * x) + 16 * exp(-4 * x) + 25 * exp(-5 * x)) + 25 * 100 * exp(-5 * x));
	}

	double newtonRaphson()
	{
		// These choices depend on the problem being solved
		double x0 = 0.01; // The initial value
		double x1 = 0.0;

		double tolerance = std::pow(10, -7);   // 7 digit accuracy is desired
		double epsilon = std::pow(10, -14); 	// Don't want to divide by a number smaller than this

		int maxIterations = 20;				// Don't allow the iterations to continue indefinitely
		bool haveWeFoundSolution = false;	// % Have not converged to a solution yet

		for (int i = 0; i < maxIterations; ++i)
		{
			double y = V(x0);
			double yprime = dV(x0);

			if (abs(yprime) < epsilon)			// Don't want to divide by too small of a number
				break;							// denominator is too small
			// Leave the loop

			x1 = x0 - (y / yprime);                       // Do Newton's computation

			if (abs(x1 - x0) / abs(x1) < tolerance) // If the result is within the desired tolerance
			{
				haveWeFoundSolution = true;
				break;                                         // Done, so leave the loop
			}
			x0 = x1;                                            // Update x0 to start the process again
		}

		if (haveWeFoundSolution)
		{
			// x1 is a solution within tolerance and maximum number of iterations
			std::cout << "solution within tolerance and maximum number of iterations: " << std::endl;
		}
		else
		{
			std::cout << " did not converge" << std::endl;
		}
		return x1;
	}

}


TEST(bondTest, ZCBond)
{
	// 1.a
	double y = newtonRaphson();
	std::cout << "yield: " << y << std::endl;

	// 1.b
	double V = 90;
	std::cout <<"Duration: "<< (-1 / V)*dV(y) << std::endl;
	std::cout << "Convexity: " << (1 / V)*d2V(y) << std::endl;
	double C = (1 / V)*d2V(y);
}