#ifndef _VARIABLEXPRESSION_H_
#define _VARIABLEXPRESSION_H_

#include <string>

#include "doubleexpression.h"
#include "integerexpression.h"
#include "basic.h"

/*
This class is used to access variable inside an expression
*/
class DoubleVariableExpression : public DoubleExpression {
public:
	DoubleVariableExpression(const std::string& name);

	const std::string print() const;		// return the stored value
	const std::string list() const;			// printable version
	double value() const;					// numerical evaluation

private:
	std::string name_;
};

class IntegerVariableExpression : public IntegerExpression {
public:
	IntegerVariableExpression(const std::string& name);

	const std::string print() const;		// return the stored value
	const std::string list() const;			// printable version
	long value() const;					// numerical evaluation

private:
	std::string name_;
};

#endif
