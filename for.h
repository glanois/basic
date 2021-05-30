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
	FloatFor(FloatExpression *start, FloatExpression *stop, FloatExpression *step, std::string var);
	~FloatFor();
	
	bool execute(int lineNumber, bool next) const;					// run this line of the program
	void list(std::ostream& os) const;		// list this line
	void preExecute() const;				// run before main program execution
	void registerNext(const FloatNext *next) const;	// register NEXT statement
	void doNext() const;					// called from NEXT statement

private:
	FloatExpression *start;			// expression to evaluate to start the loop
	FloatExpression *stop;				// end condition expression
	FloatExpression *step;				// step size expression
	std::string var;					// loop variable name
	static std::map<const FloatFor*, const FloatNext*> nextLine;	// NEXT statement to jump past when loop terminates
	static std::map<const FloatFor*, bool> initial;	// is this the first time executing
};

class IntegerFor : public Program {
public:
	IntegerFor(IntegerExpression *start, IntegerExpression *stop, IntegerExpression *step, std::string var);
	~IntegerFor();
	
	bool execute(int lineNumber, bool next) const;					// run this line of the program
	void list(std::ostream& os) const;		// list this line
	void preExecute() const;				// run before main program execution
	void registerNext(const IntegerNext *next) const;	// register NEXT statement
	void doNext() const;					// called from NEXT statement

private:
	IntegerExpression *start;			// expression to evaluate to start the loop
	IntegerExpression *stop;				// end condition expression
	IntegerExpression *step;				// step size expression
	std::string var;					// loop variable name
	static std::map<const IntegerFor*, const IntegerNext*> nextLine;	// NEXT statement to jump past when loop terminates
	static std::map<const IntegerFor*, bool> initial;	// is this the first time executing
};

#endif
