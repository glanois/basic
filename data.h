#ifndef _DATA_H_
#define _DATA_H_

#include <vector>

#include "program.h"

/*
This class implements the DATA statement, storing numbers
for later use by READ.
*/
class Data : public Program {
public:
	Data(std::vector<float> vals);
	
   virtual bool execute(int lineNumber, bool next) const;
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	std::vector<float> vals;			// floats to be stored
};

#endif
