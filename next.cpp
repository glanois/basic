#include "next.h"
#include "basic.h"
#include "for.h"

std::map<const DoubleNext*, const DoubleFor*> DoubleNext::loop;
std::map<const IntegerNext*, const IntegerFor*> IntegerNext::loop;

// initialize
DoubleNext::DoubleNext(std::string var){
	this->var = var;
}

// clean up
DoubleNext::~DoubleNext(){
	loop.erase(this);
}

// run this line of the program
bool DoubleNext::execute(int /* lineNumber */, bool /* next */) const{
	loop.at(this)->doNext();
	Basic::instance()->gotoProgram(loop[this]);
   return true;
}

// list this line
void DoubleNext::list(std::ostream& os) const{
	os << "NEXT " << var;
}

// run before main program execution
void DoubleNext::preExecute() const{
	loop[this] = Basic::instance()->popDoubleFor();
	loop.at(this)->registerNext(this);
}


// initialize
IntegerNext::IntegerNext(std::string var){
	this->var = var;
}

// clean up
IntegerNext::~IntegerNext(){
	loop.erase(this);
}

// run this line of the program
bool IntegerNext::execute(int /* lineNumber */, bool /* next */) const{
	loop.at(this)->doNext();
	Basic::instance()->gotoProgram(loop[this]);
   return true;
}

// list this line
void IntegerNext::list(std::ostream& os) const{
	os << "NEXT " << var;
}

// run before main program execution
void IntegerNext::preExecute() const{
	loop[this] = Basic::instance()->popIntegerFor();
	loop.at(this)->registerNext(this);
}
