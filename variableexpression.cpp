#include <iostream>

#include "variableexpression.h"

FloatVariableExpression::FloatVariableExpression(const std::string& name) 
   : FloatExpression(0)
   , name_(name)
{
}

// return the stored value
std::string FloatVariableExpression::print() const
{
   float v = value();
	return std::to_string(v);
}

// printable version
std::string FloatVariableExpression:: list() const
{
	return name_;
}

// numerical evaluation
float FloatVariableExpression::value() const
{
   float v = Basic::instance()->resolveFloat(name_);
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
   int v = value();
	return std::to_string(v);
}

// printable version
std::string IntegerVariableExpression:: list() const
{
	return name_;
}

// numerical evaluation
int IntegerVariableExpression::value() const
{
   int v = Basic::instance()->resolveInteger(name_);
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
