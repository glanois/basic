#include "data.h"
#include "basic.h"

Data::Data(std::vector<double> vals){
	this->vals = vals;
}

bool Data::execute(bool next) const
{
   // Just skip over DATA statement when executing.
   if (next)
   {
      Basic::instance()->nextLine();	// continue to next line
   }
   return true;
}

// list this line
void Data::list(std::ostream& os) const{
	os << "DATA ";
	std::vector<double>::const_iterator it = vals.cbegin();
	os << *it;		// print out first value
	for(  ++it; it != vals.cend(); ++it ){
		os << ", " << *it;	// print out remaining values
	}
}

// run before main program execution
void Data::preExecute() const{
	Basic::instance()->pushData(vals);
}
