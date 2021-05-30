#ifndef _INTEGEREXPRESSION_H_
#define _INTEGEREXPRESSION_H_

#include "expression.h"

/**
 * Stores an integer value.
 */
class IntegerExpression : public Expression {
public:
	IntegerExpression(int d);				// take an integer as input
	
	virtual std::string print() const;	// return the stored value
	virtual std::string list() const;		// printable version
	virtual int value() const;				// numerical evaluation
	
private:
	int d_;								// data storage
};

#endif
