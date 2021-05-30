#include <iostream>

#include "variableexpression.h"

DoubleVariableExpression::DoubleVariableExpression(const std::string& name) 
   : DoubleExpression(0)
   , name_(name)
{
}

// return the stored value
std::string DoubleVariableExpression::print() const
{
   double v = value();
	return std::to_string(v);
}

// printable version
std::string DoubleVariableExpression:: list() const
{
	return name_;
}

// numerical evaluation
double DoubleVariableExpression::value() const
{
   double v = Basic::instance()->resolveDouble(name_);
	return v;
}


IntegerVariableExpression::IntegerVariableExpression(const std::string& name) 
   : IntegerExpression(0)
   , name_(name)
{
}

// return the stored value
std::string IntegerVariableExpression::print() const
{
   long v = value();
	return std::to_string(v);
}

// printable version
std::string IntegerVariableExpression:: list() const
{
	return name_;
}

// numerical evaluation
long IntegerVariableExpression::value() const
{
   long v = Basic::instance()->resolveInteger(name_);
	return v;
}


StringVariableExpression::StringVariableExpression(const std::string& name) 
   : StringExpression("")
   , name_(name)
{
}

// return the stored value
std::string StringVariableExpression::print() const
{
   std::string v = value();
	return v;
}

// printable version
std::string StringVariableExpression:: list() const
{
	return name_;
}

// value
std::string StringVariableExpression::value() const
{
   std::string v = Basic::instance()->resolveString(name_);
	return v;
}
