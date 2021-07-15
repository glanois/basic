#include "read.h"
#include "basic.h"

Read::Read(std::vector<std::string> vars){
	this->vars = vars;
}

// run this line of the program
bool Read::execute(int /* lineNumber */, bool next) const{
	for( std::vector<std::string>::const_iterator it = vars.cbegin(); it != vars.cend(); ++it ){
		Basic::instance()->read(*it);
	}
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this line
void Read::list(std::ostream& os) const{
	os << "READ ";
	std::vector<std::string>::const_iterator it = vars.cbegin();
	os << *it;		// print out first value
	for(  ++it; it != vars.cend(); ++it ){
		os << "," << *it;	// print out remaining values
	}
}
