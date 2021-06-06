#include <iostream>
#include <cmath>

#include "operatorexpression.h"

FloatOperatorExpression::FloatOperatorExpression(
   FloatExpression* a, 
   FloatExpression* b, 
   char op) 
   : FloatExpression(0)
   , a_(a)
   , b_(b)
   , op_(op)
{
}

FloatOperatorExpression::FloatOperatorExpression(
   FloatExpression* a, 
   char op) 
   : FloatExpression(0)
   , a_(a)
   , b_(0)
   , op_(op)
{
}

FloatOperatorExpression::~FloatOperatorExpression()
{
   delete a_;
   a_ = 0;
   delete b_; 
   b_ = 0;
   op_ = '\0';
}

std::string FloatOperatorExpression::print() const{
   std::string result;
   if (a_->isInt() && b_->isInt()) {
      // xxx - round() or trunc()?
      result = std::to_string(static_cast<int>(std::round(value())));
   }
   else {
      result = std::to_string(value());
   }

	return result;
}

std::string FloatOperatorExpression::list() const{
	if( op_ != 'n' )
		return a_->list() + " " + op_ + " " + b_->list();
	else
		return "-" + a_->list();
}

float FloatOperatorExpression::value() const
{
   float result = 0.0;
	switch (op_)
   {
		case '+':
			result = a_->value() + b_->value();
         break;
		case '-':
			result = a_->value() - b_->value();
         break;
		case '*':
			result = a_->value() * b_->value();
         break;
		case '/':
         result = a_->value() / b_->value();
         break; 
		case '^':
			result = pow(a_->value(), b_->value());
         break;
		case 'n':
			result = -a_->value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op_);
	}
   return result;
}


IntegerOperatorExpression::IntegerOperatorExpression(
   IntegerExpression* a, 
   IntegerExpression* b, 
   char op) 
   : IntegerExpression(0)
   , a_(a)
   , b_(b)
   , op_(op)
{
}

IntegerOperatorExpression::IntegerOperatorExpression(
   IntegerExpression* a, 
   char op) 
   : IntegerExpression(0)
   , a_(a)
   , b_(0)
   , op_(op)
{
}

IntegerOperatorExpression::~IntegerOperatorExpression()
{
   delete a_;
   a_ = 0;
   delete b_; 
   b_ = 0;
   op_ = '\0';
}

std::string IntegerOperatorExpression::print() const{
	return std::to_string(value());
}

std::string IntegerOperatorExpression::list() const{
	if( op_ != 'n' )
		return a_->list() + " " + op_ + " " + b_->list();
	else
		return "-" + a_->list();
}

int IntegerOperatorExpression::value() const
{
   int result = 0.0;
	switch (op_)
   {
		case '+':
			result = a_->value() + b_->value();
         break;
		case '-':
			result = a_->value() - b_->value();
         break;
		case '*':
			result = a_->value() * b_->value();
         break;
		case '/':
         result = a_->value() / b_->value();
         break; 
		case '^':
			result = pow(a_->value(), b_->value());
         break;
		case 'n':
			result = -a_->value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op_);
	}
   return result;
}


StringOperatorExpression::StringOperatorExpression(
   StringExpression* a, 
   StringExpression* b, 
   char op) 
   : StringExpression("")
   , a_(a)
   , b_(b)
   , op_(op)
{
}

StringOperatorExpression::~StringOperatorExpression()
{
   delete a_;
   a_ = 0;
   delete b_; 
   b_ = 0;
   op_ = '\0';
}

std::string StringOperatorExpression::print() const{
	return value();
}

std::string StringOperatorExpression::list() const{
   return a_->list() + " " + op_ + " " + b_->list();
}

std::string StringOperatorExpression::value() const
{
   std::string result;
	switch (op_)
   {
		case '+':
			result = a_->value() + b_->value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op_);
	}
   return result;
}
