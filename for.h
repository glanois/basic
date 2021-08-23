#ifndef _FOR_H_
#define _FOR_H_

#include <string>
#include <map>

#include "program.h"
#include "floatexpression.h"
#include "integerexpression.h"

class FloatNext;
class IntegerNext;

/*
This class provides the functionality to handle the FOR
loop statement.
*/
class FloatFor : public Program {
public:
	FloatFor(
      FloatExpression* start, 
      FloatExpression* stop, 
      FloatExpression* step, 
      const std::string& var);
	~FloatFor();
	
	bool execute(
      int lineNumber, 
      bool next) const; // run this line of the program
	void list(std::ostream& os) const; // list this line
	void preExecute() const; // run before main program execution
	void registerNext(const FloatNext* next) const;	// register NEXT statement
	void doNext() const; // called from NEXT statement

private:
	FloatExpression* m_start;			// expression to evaluate to start the loop
	FloatExpression* m_stop;				// end condition expression
	FloatExpression* m_step;				// step size expression
	std::string m_var;					// loop variable name
	static std::map<const FloatFor*, const FloatNext*> m_nextLine; // NEXT statement to jump past when loop terminates
	static std::map<const FloatFor*, bool> m_initial; // is this the first time executing
};

class IntegerFor : public Program {
public:
	IntegerFor(
      IntegerExpression* start,
      IntegerExpression* stop,
      IntegerExpression* step,
      const std::string& var);
	~IntegerFor();
	
	bool execute(
      int lineNumber,
      bool next) const;					// run this line of the program
	void list(std::ostream& os) const;		// list this line
	void preExecute() const;				// run before main program execution
	void registerNext(const IntegerNext* next) const;	// register NEXT statement
	void doNext() const;					// called from NEXT statement

private:
	IntegerExpression* m_start; // expression to evaluate to start the loop
	IntegerExpression* m_stop; // end condition expression
	IntegerExpression* m_step; // step size expression
	std::string m_var; // loop variable name
	static std::map<const IntegerFor*, const IntegerNext*> m_nextLine; // NEXT statement to jump past when loop terminates
	static std::map<const IntegerFor*, bool> m_initial; // is this the first time executing
};

#endif
