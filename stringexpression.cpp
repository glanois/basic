#include "stringexpression.h"

// create a new StringExpression, storing its text
StringExpression::StringExpression(const std::string& text) 
   : text_(text)
{
}

// return the text value
const std::string StringExpression::print() const
{
	return text_;
}

// return a string for printing
const std::string StringExpression::list() const
{
	return '"' + text_ + '"';
}

// return the value
std::string StringExpression::value() const
{
	return text_;
}
