#ifndef _BASIC_H_
#define _BASIC_H_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <variant>

#include "program.h"
#include "floatexpression.h"

class FloatFor;
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
	void pushData(const std::vector<std::variant<int, float, std::string>>& vals); // push DATA values
	void pushFloatFor(const FloatFor *forLoop);					// push a FOR loop onto the stack
	const FloatFor *popFloatFor();								// pop last FOR off the stack
	void pushIntegerFor(const IntegerFor *forLoop);					// push a FOR loop onto the stack
	const IntegerFor *popIntegerFor();								// pop last FOR off the stack
	
	static Basic *instance();							// access the singleton instance

	void assign(const std::string& var, const std::variant<int, float, std::string>& value); // assign a value to a variable
   void assign(const std::string& var, float value);
   void assign(const std::string& var, int value);
   void assign(const std::string& var, const std::string& value);
	float resolveFloat(const std::string& var);					// return variable value
	int resolveInteger(const std::string& var);					// return variable value
   std::string resolveString(const std::string& var);					// return variable value
	
private:
	std::map<int, const Program*> lines;				// store the lines in a map
	std::map<std::string, float> floatVars;        // store float variables
	std::map<std::string, int> integerVars;        // store int variables
	std::map<std::string, std::string> stringVars; // store string variables
	std::string name;									// name of active program
	std::map<int, const Program*>::iterator counter;	// program line to run next
	std::deque<std::variant<int, float, std::string>> data; // stored DATA for READ
	std::stack<const FloatFor*> floatForLoops;		// stack for registering FOR/NEXT statements
	std::stack<const IntegerFor*> integerForLoops;	// stack for registering FOR/NEXT statements
	
	static Basic *b;									// singleton instance
};

#endif
