#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <iostream>

/*
This is the base class for executable program statements
*/
class Program{
public:
	virtual ~Program();
   // Execute this program statement.  
   // next - set to true to advance the line counter to the next line
   // returns - true = continue executing the next line, otherwise terminate (due to STOP or END)
   virtual bool execute(bool next) const = 0;
	virtual void list(std::ostream& os) const;	// list this line
	virtual void preExecute() const;	// run before main program execution
};

#endif
