#include <cstring>

#include "ifthen.h"
#include "basic.h"

// create a new statement instance
DoubleIfThen::DoubleIfThen(DoubleExpression *a, DoubleExpression *b, char *op, int line){
	this->a = a;
	this->b = b;
	this->op = op;
	this->line = line;
}

// clean up the expression pointers
DoubleIfThen::~DoubleIfThen(){
	delete a;
	delete b;
}

// run this line of the program
bool DoubleIfThen::execute(int /* lineNumber */, bool next) const{
	double aVal = a->value();
	double bVal = b->value();
	bool result = false;
	
	if( strcmp(op, "=") == 0 )
		result = aVal == bVal;
	else if( strcmp(op, "<") == 0 )
		result = aVal < bVal;
	else if( strcmp(op, ">") == 0 )
		result = aVal > bVal;
	else if( strcmp(op, "<=") == 0 )
		result = aVal <= bVal;
	else if( strcmp(op, ">=") == 0 )
		result = aVal >= bVal;
	else if( strcmp(op, "<>") == 0 )
		result = aVal != bVal;
	
	if( result )
		Basic::instance()->gotoLine(line);
	else
   {
      if (next)
      {
         Basic::instance()->nextLine();
      }
   }

   // When result == true, then the rest of the multi-statement
   // needs to be skipped (and control passes to the line number
   // specified by the THEN).  When result == false, execute the next
   // sub-statement in the multi-statement.
   return !result;
}

// list this line
void DoubleIfThen::list(std::ostream& os) const{
	os << "IF " << a->list() << ' ' << op << ' ';
	os << b->list() << " THEN " << line;
}


// create a new statement instance
IntegerIfThen::IntegerIfThen(IntegerExpression *a, IntegerExpression *b, char *op, int line){
	this->a = a;
	this->b = b;
	this->op = op;
	this->line = line;
}

// clean up the expression pointers
IntegerIfThen::~IntegerIfThen(){
	delete a;
	delete b;
}

// run this line of the program
bool IntegerIfThen::execute(int /* lineNumber */, bool next) const{
	long aVal = a->value();
	long bVal = b->value();
	bool result = false;
	
	if( strcmp(op, "=") == 0 )
		result = aVal == bVal;
	else if( strcmp(op, "<") == 0 )
		result = aVal < bVal;
	else if( strcmp(op, ">") == 0 )
		result = aVal > bVal;
	else if( strcmp(op, "<=") == 0 )
		result = aVal <= bVal;
	else if( strcmp(op, ">=") == 0 )
		result = aVal >= bVal;
	else if( strcmp(op, "<>") == 0 )
		result = aVal != bVal;
	
	if( result )
		Basic::instance()->gotoLine(line);
	else
   {
      if (next)
      {
         Basic::instance()->nextLine();
      }
   }

   // When result == true, then the rest of the multi-statement
   // needs to be skipped (and control passes to the line number
   // specified by the THEN).  When result == false, execute the next
   // sub-statement in the multi-statement.
   return !result;
}

// list this line
void IntegerIfThen::list(std::ostream& os) const{
	os << "IF " << a->list() << ' ' << op << ' ';
	os << b->list() << " THEN " << line;
}
