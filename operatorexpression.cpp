#include <cmath>

#include "operatorexpression.h"

DoubleOperatorExpression::DoubleOperatorExpression(
   const DoubleExpression& a, 
   const DoubleExpression& b, 
   char op) 
   : DoubleExpression(0)
   , a_(a)
   , b_(b)
   , op_(op)
{
}

DoubleOperatorExpression::DoubleOperatorExpression(
   const DoubleExpression& a, 
   char op) 
   : DoubleExpression(0)
   , a_(a)
   , b_(0)
   , op_(op)
{
}

DoubleOperatorExpression::~DoubleOperatorExpression()
{
}

const std::string DoubleOperatorExpression::print() const{
	return std::to_string(value());
}

const std::string DoubleOperatorExpression::list() const{
	if( op_ != 'n' )
		return a_.list() + op_ + b_.list();
	else
		return "-" + a_.list();
}

double DoubleOperatorExpression::value() const
{
   double result = 0.0;
	switch (op_)
   {
		case '+':
			result = a_.value() + b_.value();
         break;
		case '-':
			result = a_.value() - b_.value();
         break;
		case '*':
			result = a_.value() * b_.value();
         break;
		case '/':
         result = a_.value() / b_.value();
         break; 
		case '^':
			result = pow(a_.value(), b_.value());
         break;
		case 'n':
			result = -a_.value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op_);
	}
   return result;
}


IntegerOperatorExpression::IntegerOperatorExpression(
   const IntegerExpression& a, 
   const IntegerExpression& b, 
   char op) 
   : IntegerExpression(0)
   , a_(a)
   , b_(b)
   , op_(op)
{
}

IntegerOperatorExpression::IntegerOperatorExpression(
   const IntegerExpression& a, 
   char op) 
   : IntegerExpression(0)
   , a_(a)
   , b_(0)
   , op_(op)
{
}

IntegerOperatorExpression::~IntegerOperatorExpression()
{
}

const std::string IntegerOperatorExpression::print() const{
	return std::to_string(value());
}

const std::string IntegerOperatorExpression::list() const{
	if( op_ != 'n' )
		return a_.list() + op_ + b_.list();
	else
		return "-" + a_.list();
}

long IntegerOperatorExpression::value() const
{
   long result = 0.0;
	switch (op_)
   {
		case '+':
			result = a_.value() + b_.value();
         break;
		case '-':
			result = a_.value() - b_.value();
         break;
		case '*':
			result = a_.value() * b_.value();
         break;
		case '/':
         result = a_.value() / b_.value();
         break; 
		case '^':
			result = pow(a_.value(), b_.value());
         break;
		case 'n':
			result = -a_.value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op_);
	}
   return result;
}
