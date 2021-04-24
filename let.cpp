#include "let.h"

Let::Let(char *var, const DoubleExpression *expression){
	this->var = var;
	this->expression = expression;
}

// clean up the pointer
Let::~Let(){
	delete expression;
}

// store the value of the Expression in the Basic vars map
bool Let::execute(bool next) const{
	Basic::instance()->assign(var, expression->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void Let::list(std::ostream& os) const{
	os << "LET " << var << " = " << expression->list();
}
