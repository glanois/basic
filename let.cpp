#include "let.h"

DoubleLet::DoubleLet(char *var, const DoubleExpression *expression){
	this->var = var;
	this->expression = expression;
}

// clean up the pointer
DoubleLet::~DoubleLet(){
	delete expression;
}

// store the value of the Expression in the Basic vars map
bool DoubleLet::execute(int /* lineNumber */, bool next) const{
	Basic::instance()->assign(var, expression->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void DoubleLet::list(std::ostream& os) const{
	os << "LET " << var << " = " << expression->list();
}


IntegerLet::IntegerLet(char *var, const IntegerExpression *expression){
	this->var = var;
	this->expression = expression;
}

// clean up the pointer
IntegerLet::~IntegerLet(){
	delete expression;
}

// store the value of the Expression in the Basic vars map
bool IntegerLet::execute(int /* lineNumber */, bool next) const{
	Basic::instance()->assign(var, expression->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void IntegerLet::list(std::ostream& os) const{
	os << "LET " << var << " = " << expression->list();
}


StringLet::StringLet(char *var, const StringExpression *expression){
	this->var = var;
	this->expression = expression;
}

// clean up the pointer
StringLet::~StringLet(){
	delete expression;
}

// store the value of the Expression in the Basic vars map
bool StringLet::execute(int /* lineNumber */, bool next) const{
	Basic::instance()->assign(var, expression->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void StringLet::list(std::ostream& os) const{
	os << "LET " << var << " = " << expression->list();
}

