#include <iostream>

#include "integerexpression.h"

// create a new IntegerExpression, storing its value
IntegerExpression::IntegerExpression(long d)
   : d_(d)
{
}

// return the text value
const std::string IntegerExpression::print() const
{
	return std::to_string(d_);
}

// return a string for printing
const std::string IntegerExpression::list() const
{
	return print();
}

// return the value
long IntegerExpression::value() const
{
	return d_;
}
