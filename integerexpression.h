#ifndef _INTEGEREXPRESSION_H_
#define _INTEGEREXPRESSION_H_

#include "expression.h"
#include "types.h"

/**
 * Stores an integer value.
 */
class IntegerExpression : public Expression {
public:
	IntegerExpression(IntValue i);   // take an integer as input
	
	virtual std::string print() const;	// return the stored value
	virtual std::string list() const;		// printable version
	virtual IntValue value() const;				// numerical evaluation
	
private:
   IntValue i_; // data storage
};

#endif
