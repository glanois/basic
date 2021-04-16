#include "goto.h"
#include "basic.h"

// instantiate goto statement
Goto::Goto(int line){
	this->line = line;
}

// run this line of the program
bool Goto::execute(bool /* next*/) const{
   // Don't go to the next line, go to the specified line.
	Basic::instance()->gotoLine(line);
   return true;
}

// list this line
void Goto::list(std::ostream& os) const{
	os << "GOTO " << line;
}
