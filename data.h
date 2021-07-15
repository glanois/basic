#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <variant>

#include "program.h"

/*
This class implements the DATA statement, storing numbers
for later use by READ.
*/
class Data : public Program {
public:
	Data(const std::vector<std::variant<int, float, std::string>>& vals);
	
   virtual bool execute(int lineNumber, bool next) const;
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	std::vector<std::variant<int, float, std::string>> _vals;
};

#endif
