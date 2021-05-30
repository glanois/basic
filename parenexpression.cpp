#include "parenexpression.h"

FloatParenExpression::FloatParenExpression(FloatExpression* exp) 
   : FloatExpression(0)
   , exp_(exp)
{
}

FloatParenExpression::~FloatParenExpression()
{
   delete exp_;
   exp_ = 0;
}

// return a printable value
std::string FloatParenExpression::print() const{
	return std::to_string(value());
}

// print a listing version
std::string FloatParenExpression::list() const{
	return "(" + exp_->list() + ")";
}

// numerical evaluation
float FloatParenExpression::value() const{
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
int IntegerParenExpression::value() const{
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
