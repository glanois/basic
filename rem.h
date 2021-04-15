#ifndef _REM_H_
#define _REM_H_

#include <iostream>

#include "program.h"

/*
This class implements the REM statement
*/
class Rem : public Program {
public:
	Rem(const char* remark);	// instantiate rem statement
	
   // execute() - use default behavior (just skip this line)

	void list(std::ostream& os) const;	// list this line

private:
   std::string remark_;					// string containing remark
};

#endif
