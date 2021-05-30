#include <iostream>

#include "floatexpression.h"

// create a new FloatExpression, storing its value
FloatExpression::FloatExpression(float d)
   : d_(d)
{
}

// return the text value
std::string FloatExpression::print() const
{
	return std::to_string(d_);
}

// return a string for printing
std::string FloatExpression::list() const
{
	return print();
}

// return the value
float FloatExpression::value() const
{
	return d_;
}
