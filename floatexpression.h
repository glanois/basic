#ifndef _FLOATEXPRESSION_H_
#define _FLOATEXPRESSION_H_

#include "expression.h"

/*
Class used for storing a numerical value
*/
class FloatExpression : public Expression {
public:
	FloatExpression(float f, bool isInt = false); // take a float as input
	
	virtual std::string print() const;	// return the stored value
	virtual std::string list() const;		// printable version
	virtual float value() const;				// numerical evaluation
   bool isInt() const;

private:
	float f_; // data storage
   bool isInt_; // Was originally an int.
};

#endif
