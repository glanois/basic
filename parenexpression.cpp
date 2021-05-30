#include "parenexpression.h"

DoubleParenExpression::DoubleParenExpression(DoubleExpression* exp) 
   : DoubleExpression(0)
   , exp_(exp)
{
}

DoubleParenExpression::~DoubleParenExpression()
{
   delete exp_;
   exp_ = 0;
}

// return a printable value
std::string DoubleParenExpression::print() const{
	return std::to_string(value());
}

// print a listing version
std::string DoubleParenExpression::list() const{
	return "(" + exp_->list() + ")";
}

// numerical evaluation
double DoubleParenExpression::value() const{
	return exp_->value();
}


IntegerParenExpression::IntegerParenExpression(IntegerExpression* exp) 
   : IntegerExpression(0)
   , exp_(exp)
{
}

IntegerParenExpression::~IntegerParenExpression()
{
}

// return a printable value
std::string IntegerParenExpression::print() const{
	return std::to_string(value());
}

// print a listing version
std::string IntegerParenExpression::list() const{
	return "(" + exp_->list() + ")";
}

// numerical evaluation
long IntegerParenExpression::value() const{
	return exp_->value();
}


StringParenExpression::StringParenExpression(StringExpression* exp) 
   : StringExpression(0)
   , exp_(exp)
{
}

StringParenExpression::~StringParenExpression()
{
}

// return a printable value
std::string StringParenExpression::print() const{
	return value();
}

// print a listing version
std::string StringParenExpression::list() const{
	return "(" + exp_->list() + ")";
}

// value
std::string StringParenExpression::value() const{
	return exp_->value();
}
