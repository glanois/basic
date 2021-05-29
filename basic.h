#ifndef _BASIC_H_
#define _BASIC_H_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <stack>

#include "program.h"
#include "doubleexpression.h"

class DoubleFor;
class IntegerFor;

/*
This is a singleton class which contains all the program lines.
*/
class Basic {
public:
	void add(int index, const Program *program);		// add a new line to the program
	void list(std::ostream &out);						// list out all the existing lines
	void execute();										// run the program
	void remove(int index);								// remove program line
	void saveProgram();									// save active program to disk
	void unsaveProgram();								// delete saved program from disk
	void newProgram();									// start a new program
	void oldProgram();									// load program from disk
	void erase();										// clear stored program lines
	void renameProgram();								// rename the current program
	void catalogPrograms();								// list saved programs
	void gotoLine(int line);							// jump to program line
	void nextLine();									// go to next program line
	void gotoProgram(const Program *program);			// go to program line
	void endProgram();									// end execution
	void read(std::string var);							// assign next data value to var
	void pushData(std::vector<double> vals);			// push more values onto data vector
	void pushDoubleFor(const DoubleFor *forLoop);					// push a FOR loop onto the stack
	const DoubleFor *popDoubleFor();								// pop last FOR off the stack
	void pushIntegerFor(const IntegerFor *forLoop);					// push a FOR loop onto the stack
	const IntegerFor *popIntegerFor();								// pop last FOR off the stack
	
	static Basic *instance();							// access the singleton instance

	void assign(const std::string& var, double value);			// assign a value to a variable
	void assign(const std::string& var, long value);			// assign a value to a variable
	void assign(const std::string& var, const std::string& value);			// assign a value to a variable
	double resolveDouble(const std::string& var);					// return variable value
	long resolveInteger(const std::string& var);					// return variable value
   std::string resolveString(const std::string& var);					// return variable value
	
private:
	std::map<int, const Program*> lines;				// store the lines in a map
	std::map<std::string, double> doubleVars;					// store variables
	std::map<std::string, long> integerVars;					// store variables
	std::map<std::string, std::string> stringVars;					// store variables
	std::string name;									// name of active program
	std::map<int, const Program*>::iterator counter;	// program line to run next
	std::deque<double> data;							// stored data block for READ
	std::stack<const DoubleFor*> doubleForLoops;		// stack for registering FOR/NEXT statements
	std::stack<const IntegerFor*> integerForLoops;	// stack for registering FOR/NEXT statements
	
	static Basic *b;									// singleton instance
};

#endif
