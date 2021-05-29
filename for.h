#ifndef _FOR_H_
#define _FOR_H_

#include <string>
#include <map>

#include "program.h"
#include "doubleexpression.h"
#include "integerexpression.h"

class DoubleNext;
class IntegerNext;

/*
This class provides the functionality to handle the FOR
loop statement.
*/
class DoubleFor : public Program {
public:
	DoubleFor(DoubleExpression *start, DoubleExpression *stop, DoubleExpression *step, std::string var);
	~DoubleFor();
	
	bool execute(int lineNumber, bool next) const;					// run this line of the program
	void list(std::ostream& os) const;		// list this line
	void preExecute() const;				// run before main program execution
	void registerNext(const DoubleNext *next) const;	// register NEXT statement
	void doNext() const;					// called from NEXT statement

private:
	DoubleExpression *start;			// expression to evaluate to start the loop
	DoubleExpression *stop;				// end condition expression
	DoubleExpression *step;				// step size expression
	std::string var;					// loop variable name
	static std::map<const DoubleFor*, const DoubleNext*> nextLine;	// NEXT statement to jump past when loop terminates
	static std::map<const DoubleFor*, bool> initial;	// is this the first time executing
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
