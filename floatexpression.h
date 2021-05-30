#ifndef _FLOATEXPRESSION_H_
#define _FLOATEXPRESSION_H_

#include "expression.h"

/*
Class used for storing a numerical value
*/
class FloatExpression : public Expression {
public:
	FloatExpression(float d);				// take a float as input
	
	virtual std::string print() const;	// return the stored value
	virtual std::string list() const;		// printable version
	virtual float value() const;				// numerical evaluation
	
private:
	float d_;								// data storage
};

#endif
