#ifndef _PARENEXPRESSION_H_
#define _PARENEXPRESSION_H_

#include <string>

#include "doubleexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"

/*
This class is used to store a parenthesized expression
*/
class DoubleParenExpression : public DoubleExpression {
public:
	DoubleParenExpression(DoubleExpression* exp);
	~DoubleParenExpression();

	std::string print() const;		// return a printable value
	std::string list() const;			// print a listing version
	double value() const;					// numerical evaluation

private:
	DoubleExpression* exp_;
};

class IntegerParenExpression : public IntegerExpression {
public:
	IntegerParenExpression(IntegerExpression* exp);
	~IntegerParenExpression();

	std::string print() const;		// return a printable value
	std::string list() const;			// print a listing version
	long value() const;					// numerical evaluation

private:
	IntegerExpression* exp_;
};


class StringParenExpression : public StringExpression {
public:
	StringParenExpression(StringExpression* exp);
	~StringParenExpression();

	std::string print() const;		// return a printable value
	std::string list() const;			// print a listing version
   std::string value() const;					// numerical evaluation

private:
	StringExpression* exp_;
};

#endif
