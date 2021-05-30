#ifndef _VARIABLEXPRESSION_H_
#define _VARIABLEXPRESSION_H_

#include <string>

#include "doubleexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"
#include "basic.h"

/*
This class is used to access variable inside an expression
*/
class DoubleVariableExpression : public DoubleExpression {
public:
	DoubleVariableExpression(const std::string& name);

	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
	double value() const;					// numerical evaluation

private:
	std::string name_;
};

class IntegerVariableExpression : public IntegerExpression {
public:
	IntegerVariableExpression(const std::string& name);

	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
	long value() const;					// numerical evaluation

private:
	std::string name_;
};

class StringVariableExpression : public StringExpression {
public:
	StringVariableExpression(const std::string& name);

	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
   std::string value() const;					// numerical evaluation

private:
	std::string name_;
};

#endif
