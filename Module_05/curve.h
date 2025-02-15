//
// Date: Wednsday, Jun 17, 2015
// File name: Curve.h
// Version: 1 
// Author: Abderrazak DERDOURI
// Subject: CQF Exam module 5
//
// Description: Curve class
//	
//
// Notes:
// Revision History:
//

#if !defined (CURVE_H_ALREADY_INCLUDED)
#define CURVE_H_ALREADY_INCLUDED


class Curve
{
	public:
		Curve(int term, double value);
	private:
		int myTerm;
		double myValue;
};

#endif CURVE_H_ALREADY_INCLUDED