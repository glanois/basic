#include "for.h"
#include "basic.h"
#include "next.h"

std::map<const DoubleFor*, const DoubleNext*> DoubleFor::nextLine;
std::map<const DoubleFor*, bool> DoubleFor::initial;

std::map<const IntegerFor*, const IntegerNext*> IntegerFor::nextLine;
std::map<const IntegerFor*, bool> IntegerFor::initial;

// initialize with all necessary information
DoubleFor::DoubleFor(DoubleExpression *start, DoubleExpression *stop, DoubleExpression *step, std::string var){
	this->start = start;
	this->stop = stop;
	this->step = step;
	this->var = var;
	initial[this] = true;
}

// clean up pointers
DoubleFor::~DoubleFor(){
	delete start;
	delete stop;
	delete step;
	initial.erase(this);
	nextLine.erase(this);
}

// run this line of the program
bool DoubleFor::execute(int /* lineNumber */, bool next) const{
	double s = 1.0;						// default step size
	double val;
	
	if( step != NULL )
		s = step->value();				// evaluate the step every time
	
	if( initial[this] ){						// start the loop
		val = start->value();
	} else {							// increment the loop
		val = Basic::instance()->resolveDouble(var) + s;
	}
	
	initial[this] = true;						// reset
	
	Basic::instance()->assign(var, val);	// store the value
	
	// check for loop termination
	if( (s > 0 && val > stop->value()) || (s < 0 && val < stop->value()) ){
		Basic::instance()->gotoProgram(nextLine[this]);
	}
	
   if (next)
   {
      Basic::instance()->nextLine();	// continue to next line
   }
   return true;
}

// list this line
void DoubleFor::list(std::ostream& os) const{
	os << "FOR " << var << " = " << start->list() << " TO " << stop->list();
	if( step != NULL )
		os << " STEP " << step->list();
}

// run before main program execution
void DoubleFor::preExecute() const{
	Basic::instance()->pushDoubleFor(this);
}

// register NEXT statement
void DoubleFor::registerNext(const DoubleNext *next) const{
	nextLine[this] = next;
}

// called from NEXT statement
void DoubleFor::doNext() const{
	initial[this] = false;
}


// initialize with all necessary information
IntegerFor::IntegerFor(IntegerExpression *start, IntegerExpression *stop, IntegerExpression *step, std::string var){
	this->start = start;
	this->stop = stop;
	this->step = step;
	this->var = var;
	initial[this] = true;
}

// clean up pointers
IntegerFor::~IntegerFor(){
	delete start;
	delete stop;
	delete step;
	initial.erase(this);
	nextLine.erase(this);
}

// run this line of the program
bool IntegerFor::execute(int /* lineNumber */, bool next) const{
	long s = 1.0;						// default step size
	long val;
	
	if( step != NULL )
		s = step->value();				// evaluate the step every time
	
	if( initial[this] ){						// start the loop
		val = start->value();
	} else {							// increment the loop
		val = Basic::instance()->resolveInteger(var) + s;
	}
	
	initial[this] = true;						// reset
	
	Basic::instance()->assign(var, val);	// store the value
	
	// check for loop termination
	if( (s > 0 && val > stop->value()) || (s < 0 && val < stop->value()) ){
		Basic::instance()->gotoProgram(nextLine[this]);
	}
	
   if (next)
   {
      Basic::instance()->nextLine();	// continue to next line
   }
   return true;
}

// list this line
void IntegerFor::list(std::ostream& os) const{
	os << "FOR " << var << " = " << start->list() << " TO " << stop->list();
	if( step != NULL )
		os << " STEP " << step->list();
}

// run before main program execution
void IntegerFor::preExecute() const{
	Basic::instance()->pushIntegerFor(this);
}

// register NEXT statement
void IntegerFor::registerNext(const IntegerNext *next) const{
	nextLine[this] = next;
}

// called from NEXT statement
void IntegerFor::doNext() const{
	initial[this] = false;
}
