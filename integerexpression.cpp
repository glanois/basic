#include <iostream>

#include "integerexpression.h"

// create a new IntegerExpression, storing its value
IntegerExpression::IntegerExpression(int d)
   : d_(d)
{
}

// return the text value
std::string IntegerExpression::print() const
{
   std::string s = std::to_string(d_);
   return s;
}

// return a string for printing
std::string IntegerExpression::list() const
{
	return print();
}

// return the value
int IntegerExpression::value() const
{
	return d_;
}
