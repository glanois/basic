#ifndef _OPERATOREXPRESSION_H_
#define _OPERATOREXPRESSION_H_

#include "floatexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"

/*
Class for performing mathematical operations on FloatExpressions.
*/
class FloatOperatorExpression : public FloatExpression {
public:
	FloatOperatorExpression(FloatExpression* a, FloatExpression* b, char op);
	FloatOperatorExpression(FloatExpression* a, char op);
	~FloatOperatorExpression();					// delete the sub-expressions
	
	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
	float value() const;					// value of performed operation

private:
	FloatExpression* a_;
   FloatExpression* b_;
	char op_;								// operation to perform
};


/*
Class for performing mathematical operations on IntegerExpressions.
*/
class IntegerOperatorExpression : public IntegerExpression {
public:
	IntegerOperatorExpression(IntegerExpression* a, IntegerExpression* b, char op);
	IntegerOperatorExpression(IntegerExpression* a, char op);
	~IntegerOperatorExpression();					// delete the sub-expressions
	
	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
	IntValue value() const;					// value of performed operation

private:
	IntegerExpression* a_;
   IntegerExpression* b_;
	char op_;								// operation to perform
};

/*
Class for performing string operation (concatenation).
*/
class StringOperatorExpression : public StringExpression {
public:
	StringOperatorExpression(StringExpression* a, StringExpression* b, char op);
	~StringOperatorExpression();					// delete the sub-expressions
	
	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
   std::string value() const;					// value of performed operation

private:
	StringExpression* a_;
   StringExpression* b_;
	char op_;								// operation to perform
};

#endif
