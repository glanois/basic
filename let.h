#ifndef _LET_H_
#define _LET_H_

#include <string>

#include "program.h"
#include "doubleexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"
#include "basic.h"

/*
The Let class provides variable assignment capability.
*/
class DoubleLet : public Program {
public:
	DoubleLet(char *var, const DoubleExpression *expression);	// create a new LET assignment
	~DoubleLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var;
	const DoubleExpression *expression;
};

class IntegerLet : public Program {
public:
	IntegerLet(char *var, const IntegerExpression *expression);	// create a new LET assignment */
	~IntegerLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var;
	const IntegerExpression *expression;
};

class StringLet : public Program {
public:
	StringLet(char *var, const StringExpression *expression);	// create a new LET assignment */
	~StringLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var;
	const StringExpression *expression;
};

#endif
