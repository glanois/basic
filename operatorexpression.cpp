#include <iostream>
#include <cmath>

#include "operatorexpression.h"

DoubleOperatorExpression::DoubleOperatorExpression(
   DoubleExpression* a, 
   DoubleExpression* b, 
   char op) 
   : DoubleExpression(0)
   , a_(a)
   , b_(b)
   , op_(op)
{
}

DoubleOperatorExpression::DoubleOperatorExpression(
   DoubleExpression* a, 
   char op) 
   : DoubleExpression(0)
   , a_(a)
   , b_(0)
   , op_(op)
{
}

DoubleOperatorExpression::~DoubleOperatorExpression()
{
   delete a_;
   a_ = 0;
   delete b_; 
   b_ = 0;
   op_ = '\0';
}

std::string DoubleOperatorExpression::print() const{
	return std::to_string(value());
}

std::string DoubleOperatorExpression::list() const{
	if( op_ != 'n' )
		return a_->list() + " " + op_ + " " + b_->list();
	else
		return "-" + a_->list();
}

double DoubleOperatorExpression::value() const
{
   double result = 0.0;
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
   std::cout << "DEBUG: IntegerOperatorExpression::IntegerOperatorExpression() - a = " << a_->print();
   std::cout << " b = " << b_->print() << " op = " << op_ << std::endl;
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

long IntegerOperatorExpression::value() const
{
   long result = 0.0;
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
   std::cout << "DEBUG: IntegerOperatorExpression::value() - result = " << result << std::endl;
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
   std::cout << "DEBUG: StringOperatorExpression::StringOperatorExpression() - a = " << a_->print();
   std::cout << " b = " << b_->print() << " op = " << op_ << std::endl;
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
   std::cout << "DEBUG: StringOperatorExpression::value() - result = " << result << std::endl;
   return result;
}
