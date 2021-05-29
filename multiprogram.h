#ifndef _MULTIPROGRAM_H_
#define _MULTIPROGRAM_H_

#include <iostream>
#include <vector>

#include "program.h"

/*
This class holds multiple program lines
*/
class MultiProgram : public Program 
{
public:
   MultiProgram();
	virtual bool execute(int lineNumber, bool next) const;				// run this line of the program
	virtual void list(std::ostream& os) const;	// list this line
	virtual void preExecute() const;			// run before main program execution

   void add(Program* program);
private:
   std::vector<Program*> programs_;
};

#endif
