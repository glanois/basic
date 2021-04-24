#include "end.h"
#include "basic.h"

// run this line of the program
bool End::execute(bool /* next */) const{
   // Don't advance the counter; set it to lines.end().
	Basic::instance()->endProgram();
   return false;
}

// list this line
void End::list(std::ostream& os) const{
	os << "END";
}
