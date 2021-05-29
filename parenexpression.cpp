#include "parenexpression.h"

DoubleParenExpression::DoubleParenExpression(const DoubleExpression& exp) 
   : DoubleExpression(0)
   , exp_(exp)
{
}

DoubleParenExpression::~DoubleParenExpression()
{
}

// return a printable value
const std::string DoubleParenExpression::print() const{
	return std::to_string(value());
}

// print a listing version
const std::string DoubleParenExpression::list() const{
	return "(" + exp_.list() + ")";
}

// numerical evaluation
double DoubleParenExpression::value() const{
	return exp_.value();
}


IntegerParenExpression::IntegerParenExpression(const IntegerExpression& exp) 
   : IntegerExpression(0)
   , exp_(exp)
{
}

IntegerParenExpression::~IntegerParenExpression()
{
}

// return a printable value
const std::string IntegerParenExpression::print() const{
	return std::to_string(value());
}

// print a listing version
const std::string IntegerParenExpression::list() const{
	return "(" + exp_.list() + ")";
}

// numerical evaluation
long IntegerParenExpression::value() const{
	return exp_.value();
}
