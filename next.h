#ifndef _NEXT_H_
#define _NEXT_H_

#include <string>
#include <map>

#include "program.h"

class FloatFor;
class IntegerFor;

/*
This class implements the NEXT part of a FOR/NEXT loop.
*/
class FloatNext : public Program {
public:
	FloatNext(std::string var);
	~FloatNext();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	static std::map<const FloatNext*, const FloatFor*> loop;	// FOR loop to jump back to
	std::string var;					// loop variable name
};

class IntegerNext : public Program {
public:
	IntegerNext(std::string var);
	~IntegerNext();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	static std::map<const IntegerNext*, const IntegerFor*> loop;	// FOR loop to jump back to
	std::string var;					// loop variable name
};

#endif
