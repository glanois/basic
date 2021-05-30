#ifndef _STRINGEXPRESSION_H_
#define _STRINGEXPRESSION_H_

#include "expression.h"

/*
Class used for storing a text value
*/
class StringExpression : public Expression {
public:
	StringExpression(const std::string& text);		// take a string as input
	
	virtual std::string print() const;		// return the stored value
	virtual std::string list() const;			// printable version
	virtual std::string value() const;
	
private:
	std::string text_;						// data storage
};

#endif
