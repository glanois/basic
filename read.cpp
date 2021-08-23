#include "read.h"
#include "basic.h"

Read::Read(const std::vector<StringValue>& vars) :
   m_vars(vars)
{
}

// run this line of the program
bool Read::execute(int /* lineNumber */, bool next) const{
   for (std::vector<StringValue>::const_iterator it = m_vars.cbegin(); 
        it != m_vars.cend(); 
        ++it) {
      Basic::instance()->read(*it);
   }
   if (next)
   {
      Basic::instance()->nextLine();
   }
   return true;
}

// list this line
void Read::list(std::ostream& os) const
{
   os << "READ ";
   std::vector<StringValue>::const_iterator it = m_vars.cbegin();
   os << *it;      // print out first value
   for (++it; it != m_vars.cend(); ++it) {
      os << "," << *it;   // print out remaining values
   }
}
