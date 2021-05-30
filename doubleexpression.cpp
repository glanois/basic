#include <iostream>

#include "doubleexpression.h"

// create a new DoubleExpression, storing its value
DoubleExpression::DoubleExpression(double d)
   : d_(d)
{
}

// return the text value
std::string DoubleExpression::print() const
{
	return std::to_string(d_);
}

// return a string for printing
std::string DoubleExpression::list() const
{
	return print();
}

// return the value
double DoubleExpression::value() const
{
	return d_;
}
