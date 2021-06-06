#include <cmath>
#include <iostream>

#include "floatexpression.h"

// create a new FloatExpression, storing its value
FloatExpression::FloatExpression(float f, bool isInt)
   : f_(f), isInt_(isInt)
{
}

// return the text value
std::string FloatExpression::print() const
{
   std::string result;
   if (isInt_) {
      result = std::to_string(static_cast<int>(std::round(f_)));
   }
   else {
      result = std::to_string(f_);
   }
	return result;
}

// return a string for printing
std::string FloatExpression::list() const
{
	return print();
}

// return the value
float FloatExpression::value() const
{
	return f_;
}

// return if it was originally an integer
bool FloatExpression::isInt() const
{
   return isInt_;
}
