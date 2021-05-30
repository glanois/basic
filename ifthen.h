#ifndef _IFTHEN_H_
#define _IFTHEN_H_

#include "program.h"
#include "floatexpression.h"
#include "integerexpression.h"

/*
This class provides support for the IF-THEN statement.
*/
class FloatIfThen : public Program {
public:
	FloatIfThen(FloatExpression *a, FloatExpression *b, char *op, int line);
	~FloatIfThen();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line

private:
	FloatExpression *a, *b;
	char *op;
	int line;
};

class IntegerIfThen : public Program {
public:
	IntegerIfThen(IntegerExpression *a, IntegerExpression *b, char *op, int line);
	~IntegerIfThen();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line

private:
	IntegerExpression *a, *b;
	char *op;
	int line;
};

#endif
