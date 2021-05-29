#ifndef _PARENEXPRESSION_H_
#define _PARENEXPRESSION_H_

#include <string>

#include "doubleexpression.h"
#include "integerexpression.h"

/*
This class is used to store a parenthesized expression
*/
class DoubleParenExpression : public DoubleExpression {
public:
	DoubleParenExpression(const DoubleExpression& exp);
	~DoubleParenExpression();

	const std::string print() const;		// return a printable value
	const std::string list() const;			// print a listing version
	double value() const;					// numerical evaluation

private:
	DoubleExpression exp_;
};

class IntegerParenExpression : public IntegerExpression {
public:
	IntegerParenExpression(const IntegerExpression& exp);
	~IntegerParenExpression();

	const std::string print() const;		// return a printable value
	const std::string list() const;			// print a listing version
	long value() const;					// numerical evaluation

private:
	IntegerExpression exp_;
};

#endif
