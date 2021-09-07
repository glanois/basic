#ifndef _LET_H_
#define _LET_H_

#include <string>

#include "program.h"
#include "floatexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"
#include "basic.h"

/*
The Let class provides variable assignment capability.
*/
class FloatLet : public Program {
public:
	FloatLet(const std::string& var, const FloatExpression* expression);	// create a new LET assignment
	~FloatLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var_;
	const FloatExpression* expression_;
};

class IntegerLet : public Program {
public:
	IntegerLet(const std::string& var, const IntegerExpression* expression);	// create a new LET assignment */
	~IntegerLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var_;
	const IntegerExpression* expression_;
};

class StringLet : public Program {
public:
	StringLet(const std::string& var, const StringExpression* expression);	// create a new LET assignment */
	~StringLet();												// clean up

	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	
private:
	std::string var_;
	const StringExpression* expression_;
};

#endif
