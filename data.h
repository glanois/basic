#ifndef _DATA_H_
#define _DATA_H_

#include <vector>

#include "program.h"
#include "types.h"


/**
  This class implements the DATA statement, storing values
  for later use by READ.
*/
class Data : public Program {
public:
	Data(const std::vector<DataValue>& vals);
	
   virtual bool execute(int lineNumber, bool next) const;
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	std::vector<DataValue> _vals;
};

#endif
