#ifndef _OPERATOREXPRESSION_H_
#define _OPERATOREXPRESSION_H_

#include "doubleexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"

/*
Class for performing mathematical operations on DoubleExpressions.
*/
class DoubleOperatorExpression : public DoubleExpression {
public:
	DoubleOperatorExpression(DoubleExpression* a, DoubleExpression* b, char op);
	DoubleOperatorExpression(DoubleExpression* a, char op);
	~DoubleOperatorExpression();					// delete the sub-expressions
	
	std::string print() const;		// return the stored value
	std::string list() const;			// printable version
	double value() const;					// value of performed operation

private:
	DoubleExpression* a_;
   DoubleExpression* b_;
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
	long value() const;					// value of performed operation

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
