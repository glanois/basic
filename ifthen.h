#ifndef _IFTHEN_H_
#define _IFTHEN_H_

#include <string>

#include "program.h"
#include "floatexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"

/*
This class provides support for the IF-THEN statement.
*/
class FloatIfThen : public Program {
public:
	FloatIfThen(
      FloatExpression* a, 
      FloatExpression* b, 
      const std::string& op, int line);
	~FloatIfThen();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line

private:
	FloatExpression* m_a;
   FloatExpression* m_b;
   std::string m_op;
	int m_line;
};

class IntegerIfThen : public Program {
public:
	IntegerIfThen(
      IntegerExpression* a, 
      IntegerExpression* b, 
      const std::string& op, 
      int line);
	~IntegerIfThen();
	
	bool execute(int lineNumber, bool next) const;				// run this line of the program
	void list(std::ostream& os) const;	// list this line

private:
	IntegerExpression* m_a;
   IntegerExpression* m_b;
   std::string m_op;
	int m_line;
};

class StringIfThen : public Program {
public:
	StringIfThen(
      StringExpression* a, 
      StringExpression* b, 
      const std::string& op, int line);
	~StringIfThen();
	
	bool execute(int lineNumber, bool next) const; // run this line of the program
	void list(std::ostream& os) const;	// list this line

private:
	StringExpression* m_a;
   StringExpression* m_b;
   std::string m_op;
	int m_line;
};

#endif
