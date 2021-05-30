#ifndef _PARENEXPRESSION_H_
#define _PARENEXPRESSION_H_

#include <string>

#include "floatexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"

/*
This class is used to store a parenthesized expression
*/
class FloatParenExpression : public FloatExpression {
public:
	FloatParenExpression(FloatExpression* exp);
	~FloatParenExpression();

	std::string print() const;		// return a printable value
	std::string list() const;			// print a listing version
	float value() const;					// numerical evaluation

private:
	FloatExpression* exp_;
};

class IntegerParenExpression : public IntegerExpression {
public:
	IntegerParenExpression(IntegerExpression* exp);
	~IntegerParenExpression();

	std::string print() const;		// return a printable value
	std::string list() const;			// print a listing version
	int value() const;					// numerical evaluation

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
