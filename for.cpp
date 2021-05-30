#include "for.h"
#include "basic.h"
#include "next.h"

std::map<const FloatFor*, const FloatNext*> FloatFor::nextLine;
std::map<const FloatFor*, bool> FloatFor::initial;

std::map<const IntegerFor*, const IntegerNext*> IntegerFor::nextLine;
std::map<const IntegerFor*, bool> IntegerFor::initial;

// initialize with all necessary information
FloatFor::FloatFor(FloatExpression *start, FloatExpression *stop, FloatExpression *step, std::string var){
	this->start = start;
	this->stop = stop;
	this->step = step;
	this->var = var;
	initial[this] = true;
}

// clean up pointers
FloatFor::~FloatFor(){
	delete start;
	delete stop;
	delete step;
	initial.erase(this);
	nextLine.erase(this);
}

// run this line of the program
bool FloatFor::execute(int /* lineNumber */, bool next) const{
	float s = 1.0;						// default step size
	float val;
	
	if( step != NULL )
		s = step->value();				// evaluate the step every time
	
	if( initial[this] ){						// start the loop
		val = start->value();
	} else {							// increment the loop
		val = Basic::instance()->resolveFloat(var) + s;
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
void FloatFor::list(std::ostream& os) const{
	os << "FOR " << var << " = " << start->list() << " TO " << stop->list();
	if( step != NULL )
		os << " STEP " << step->list();
}

// run before main program execution
void FloatFor::preExecute() const{
	Basic::instance()->pushFloatFor(this);
}

// register NEXT statement
void FloatFor::registerNext(const FloatNext *next) const{
	nextLine[this] = next;
}

// called from NEXT statement
void FloatFor::doNext() const{
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
	int s = 1;						// default step size
	int val;
	
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
