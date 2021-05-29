#ifndef _OPERATOREXPRESSION_H_
#define _OPERATOREXPRESSION_H_

#include "doubleexpression.h"
#include "integerexpression.h"

/*
Class for performing mathematical operations on DoubleExpressions.
*/
class DoubleOperatorExpression : public DoubleExpression {
public:
	DoubleOperatorExpression(const DoubleExpression& a, const DoubleExpression& b, char op);
	DoubleOperatorExpression(const DoubleExpression& a, char op);
	~DoubleOperatorExpression();					// delete the sub-expressions
	
	const std::string print() const;		// return the stored value
	const std::string list() const;			// printable version
	double value() const;					// value of performed operation

private:
	DoubleExpression a_;
   DoubleExpression b_;
	char op_;								// operation to perform
};

/*
Class for performing mathematical operations on IntegerExpressions.
*/
class IntegerOperatorExpression : public IntegerExpression {
public:
	IntegerOperatorExpression(const IntegerExpression& a, const IntegerExpression& b, char op);
	IntegerOperatorExpression(const IntegerExpression& a, char op);
	~IntegerOperatorExpression();					// delete the sub-expressions
	
	const std::string print() const;		// return the stored value
	const std::string list() const;			// printable version
	long value() const;					// value of performed operation

private:
	IntegerExpression a_;
   IntegerExpression b_;
	char op_;								// operation to perform
};

#endif
