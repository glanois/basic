#include "for.h"
#include "basic.h"
#include "next.h"

std::map<const FloatFor*, const FloatNext*> FloatFor::m_nextLine;
std::map<const FloatFor*, bool> FloatFor::m_initial;

std::map<const IntegerFor*, const IntegerNext*> IntegerFor::m_nextLine;
std::map<const IntegerFor*, bool> IntegerFor::m_initial;

// initialize with all necessary information
FloatFor::FloatFor(
   FloatExpression* start,
   FloatExpression* stop,
   FloatExpression* step,
   const std::string& var) :
   m_start(start),
   m_stop(stop),
   m_step(step),
   m_var(var)
{
   m_initial[this] = true;
}

// clean up pointers
FloatFor::~FloatFor()
{
   delete m_start;
   delete m_stop;
   delete m_step;
   m_initial.erase(this);
   m_nextLine.erase(this);
}

// run this line of the program
bool FloatFor::execute(
   int /* lineNumber */, 
   bool next) const
{
   float s = 1.0;                  // default step size
   float val = 0.0;
   
   if (m_step != NULL) {
      s = m_step->value();            // evaluate the step every time
   }
   
   if (m_initial[this]) {                  // start the loop
      val = m_start->value();
   } 
   else {                     // increment the loop
      val = Basic::instance()->resolveFloat(m_var) + s;
   }
   
   m_initial[this] = true;                  // reset
   
   Basic::instance()->assign(m_var, val);   // store the value
   
   // check for loop termination
   if ((s > 0 && val > m_stop->value()) || (s < 0 && val < m_stop->value()) ) {
      Basic::instance()->gotoProgram(m_nextLine[this]);
   }
   
   if (next) {
      Basic::instance()->nextLine();   // continue to next line
   }
   return true;
}

// list this line
void FloatFor::list(std::ostream& os) const
{
   os << "FOR " << m_var << " = " << m_start->list() << " TO " << m_stop->list();
   if (m_step != NULL) {
      os << " STEP " << m_step->list();
   }
}

// run before main program execution
void FloatFor::preExecute() const
{
   Basic::instance()->pushFloatFor(this);
}

// register NEXT statement
void FloatFor::registerNext(const FloatNext* next) const
{
   m_nextLine[this] = next;
}

// called from NEXT statement
void FloatFor::doNext() const
{
   m_initial[this] = false;
}


// initialize with all necessary information
IntegerFor::IntegerFor(
   IntegerExpression* start, 
   IntegerExpression* stop, 
   IntegerExpression* step, 
   const std::string& var) :
   m_start(start),
   m_stop(stop),
   m_step(step),
   m_var(var)
{
   m_initial[this] = true;
}

// clean up pointers
IntegerFor::~IntegerFor()
{
   delete m_start;
   delete m_stop;
   delete m_step;
   m_initial.erase(this);
   m_nextLine.erase(this);
}

// run this line of the program
bool IntegerFor::execute(
   int /* lineNumber */, 
   bool next) const
{
   int s = 1;                  // default step size
   int val;
   
   if (m_step != NULL) {
      s = m_step->value();            // evaluate the step every time
   }
   
   if (m_initial[this]) {                  // start the loop
      val = m_start->value();
   } 
   else {                     // increment the loop
      val = Basic::instance()->resolveInteger(m_var) + s;
   }
   
   m_initial[this] = true;                  // reset
   
   Basic::instance()->assign(m_var, val);   // store the value
   
   // check for loop termination
   if ((s > 0 && val > m_stop->value()) || (s < 0 && val < m_stop->value())) {
      Basic::instance()->gotoProgram(m_nextLine[this]);
   }
   
   if (next) {
      Basic::instance()->nextLine();   // continue to next line
   }
   return true;
}

// list this line
void IntegerFor::list(std::ostream& os) const
{
   os << "FOR " << m_var << " = " << m_start->list() << " TO " << m_stop->list();
   if (m_step != NULL) {
      os << " STEP " << m_step->list();
   }
}

// run before main program execution
void IntegerFor::preExecute() const
{
   Basic::instance()->pushIntegerFor(this);
}

// register NEXT statement
void IntegerFor::registerNext(const IntegerNext* next) const
{
   m_nextLine[this] = next;
}

// called from NEXT statement
void IntegerFor::doNext() const
{
   m_initial[this] = false;
}
