#include "program.h"
#include "basic.h"

Program::~Program()
{
}

// if you ever see this, something is wrong
void Program::list(std::ostream& os) const{
	os << "GENERIC PROGRAM (SHOULDN'T SEE THIS)";
}

// nothing to do here...
void Program::preExecute() const{
}
