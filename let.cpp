#include "let.h"

DoubleLet::DoubleLet(
   const std::string& var, 
   const DoubleExpression* expression) :
   var_(var),
   expression_(expression)
{
}

DoubleLet::~DoubleLet(){
}

// store the value of the Expression in the Basic vars map
bool DoubleLet::execute(int /* lineNumber */, bool next) const
{
	Basic::instance()->assign(var_, expression_->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void DoubleLet::list(std::ostream& os) const
{
	os << "LET " << var_ << " = " << expression_->list();
}


IntegerLet::IntegerLet(
   const std::string& var, 
   const IntegerExpression* expression) :
   var_(var),
   expression_(expression)
{
   std::cout << "DEBUG: IntegerLet::IntegerLet() - var_ = " << var_ << ", expression_ = " << expression_->list() << std::endl;
}

IntegerLet::~IntegerLet(){
}

// store the value of the Expression in the Basic vars map
bool IntegerLet::execute(int /* lineNumber */, bool next) const
{
	Basic::instance()->assign(var_, expression_->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void IntegerLet::list(std::ostream& os) const
{
	os << "LET " << var_ << " = " << expression_->list();
}


StringLet::StringLet(
   const std::string& var, 
   const StringExpression* expression) :
   var_(var),
   expression_(expression)
{
}

StringLet::~StringLet(){
}

// store the value of the Expression in the Basic vars map
bool StringLet::execute(int /* lineNumber */, bool next) const
{
	Basic::instance()->assign(var_, expression_->value());
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this LET statement
void StringLet::list(std::ostream& os) const
{
	os << "LET " << var_ << " = " << expression_->list();
}
