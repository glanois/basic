#include "multiprogram.h"
#include "basic.h"

MultiProgram::MultiProgram() : Program()
{
}

bool MultiProgram::execute(int lineNumber, bool /* next */) const
{
	std::vector<Program*>::const_iterator it;

   // We are done if a statement tells us so (eg, "GOTO", "STOP", or "END").
   bool terminate = false;
   int s = 0;
	for (it = programs_.cbegin(); it != programs_.cend() && !terminate; ++it)
   {
		terminate = !(*it)->execute(lineNumber, false /* Don't execute next line - keep executing the statements in this line. */);
	}
	
   // Now that all the colon-separated statements on this line have
   // been executed, continue to the next line (unless the line was
   // ended by a GOTO or the program was ended by a STOP or END).
   if (!terminate)
   {
      Basic::instance()->nextLine();
   }

   return !terminate;
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

void MultiProgram::preExecute() const
{
   // Run the preExecute() of all the sub-statements.
	std::vector<Program*>::const_iterator it;
	for (it = programs_.cbegin(); it != programs_.cend(); ++it)
   {
		(*it)->preExecute();
	}
}

void MultiProgram::add(Program* program)
{
   programs_.push_back(program);
}

