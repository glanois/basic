#include <cmath>

#include "operatorexpression.h"

OperatorExpression::OperatorExpression(DoubleExpression *a, DoubleExpression *b, char op) : DoubleExpression(0) {
	this->a = a;
	this->b = b;
	this->op = op;
}

OperatorExpression::~OperatorExpression(){
	delete a;
	if( b != NULL )
		delete b;
}

const std::string OperatorExpression::print() const{
	return std::to_string(value());
}

const std::string OperatorExpression::list() const{
	if( op != 'n' )
		return a->list() + op + b->list();
	else
		return "-" + a->list();
}

double OperatorExpression::value() const
{
   double result = 0.0;
	switch( op ){
		case '+':
			result = a->value() + b->value();
         break;
		case '-':
			result = a->value() - b->value();
         break;
		case '*':
			result = a->value() * b->value();
         break;
		case '/':
         result = a->value() / b->value();
         break; 
		case '^':
			result = exp(log(a->value()) * b->value());
         break;
		case 'n':
			result = -a->value();
         break;
   default:
      printf("ERROR: operation '%c' not supported.\n", op);
	}
   return result;
}
