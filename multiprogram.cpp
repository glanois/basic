#include "multiprogram.h"
#include "basic.h"

MultiProgram::MultiProgram() : Program()
{
}

void MultiProgram::execute(bool /* next */) const
{
	std::vector<Program*>::const_iterator it;
	for(it = programs_.cbegin(); it != programs_.cend(); ++it )
   {
		(*it)->execute(false /* Don't execute next line - keep executing the statements in this line. */);
	}
	
   // Now that all the colon-separated statements on this line have
   // been executed, continue to the next line.
   Basic::instance()->nextLine();
}

void MultiProgram::list(std::ostream& os) const
{
	std::vector<Program*>::const_iterator it = programs_.cbegin();
	(*it)->list(os);		// print out first statement
	for(++it; it != programs_.cend(); ++it )
   {
		os << " : ";
      (*it)->list(os);	// print out remaining statements
	}
}

void MultiProgram::add(Program* program)
{
   programs_.push_back(program);
}

