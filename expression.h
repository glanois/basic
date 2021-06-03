#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>

/*
Base class used for storing and evaluating data items
*/
class Expression {
public:
	virtual std::string print() const = 0;	 // return a string version for PRINT
	virtual std::string list() const = 0; // printable version suitable for LIST
};

#endif
