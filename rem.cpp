#include "rem.h"
#include "basic.h"

using std::endl;
using std::cout;

// instantiate rem statement
Rem::Rem(const std::string& remark) : remark_(remark) 
{
}

bool Rem::execute(int /* lineNumber */, bool /* next */) const
{
   // Always go to the next line.  Even if it is a multi-statement
   // line like:
   //   100 PRINT "SOMETHING" : REM THIS IS A COMMENT : PRINT "THIS WON'T PRINT"
   Basic::instance()->nextLine();
   return true;
}

// list this line
void Rem::list(std::ostream& os) const{
	os << remark_;
}
