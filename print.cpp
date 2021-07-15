#include <iostream>

#include "print.h"
#include "basic.h"

using std::endl;
using std::cout;

// constructor for Print class
Print::Print(const std::vector<Expression*> *exprList)
{
   if (!exprList)
   {
      std::cout << "ERROR: Print::Print() - exprList is 0" << std::endl;
   }
	this->exprList = exprList;
}

// prints out each expression to std::cout
bool Print::execute(int lineNumber, bool next) const{
   if (exprList->size() == 0)
   {
      // xxx - This might not actually be an error in the long term,
      // since PRINT by itself can be used to print a blank line.
      // But for now guard against it until we implement handling it.
      std::cout << "ERROR at line number " << lineNumber;
      std::cout << ": Print::execute() - PRINT expression list is empty." << std::endl;
   }
   else
   {
      for (int i = 0; i < exprList->size(); i++ )
      {
         Expression* e = exprList->at(i);
         if (!e)
         {
            std::cout << "ERROR: Print::execute() - bad expression pointer for expression ";
            std::cout << i << std::endl;
         }
         else
         {
            cout << e->print() << ' ';

            // If it is the last expression, follow it with a newline.
            if (i == exprList->size()-1)
            {
               std::cout << std::endl;
            }
         }
      }

      if (next)
      {
         Basic::instance()->nextLine();
      }
   }
   return true;
}

// lists the expressions, as they were originally given
void Print::list(ostream& os) const{
	os << "PRINT ";
	for( int i = 0; i < exprList->size()-1; i++) {
		os << exprList->at(i)->list() << ",";
	}
	os << exprList->at(exprList->size()-1)->list();
}
