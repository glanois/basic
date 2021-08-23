#include <cstring>

#include "ifthen.h"
#include "basic.h"

// create a new statement instance
FloatIfThen::FloatIfThen(
   FloatExpression* a, 
   FloatExpression* b, 
   const std::string& op, 
   int line) : 
   m_a(a),
   m_b(b),
   m_op(op),
   m_line(line)
{
}

// clean up the expression pointers
FloatIfThen::~FloatIfThen()
{
   delete m_a;
   delete m_b;
}

// run this line of the program
bool FloatIfThen::execute(
   int /* lineNumber */, 
   bool next) const
{
   float aVal = m_a->value();
   float bVal = m_b->value();
   bool result = false;
   
   if (m_op.compare("=") == 0) {
      result = aVal == bVal;
   }
   else if (m_op.compare("<") == 0) {
      result = aVal < bVal;
   }
   else if (m_op.compare(">") == 0) {
      result = aVal > bVal;
   }
   else if (m_op.compare("<=") == 0) {
      result = aVal <= bVal;
   }
   else if (m_op.compare(">=") == 0) {
      result = aVal >= bVal;
   }
   else if (m_op.compare("<>") == 0) {
      result = aVal != bVal;
   }
   
   if (result) {
      Basic::instance()->gotoLine(m_line);
   }
   else {
      if (next) {
         Basic::instance()->nextLine();
      }
   }

   // When result == true, then the rest of the multi-statement
   // needs to be skipped (and control passes to the line number
   // specified by the THEN).  When result == false, execute the next
   // sub-statement in the multi-statement.
   return !result;
}

// list this line
void FloatIfThen::list(std::ostream& os) const
{
   os << "IF " << m_a->list() << ' ' << m_op << ' ';
   os << m_b->list() << " THEN " << m_line;
}


// create a new statement instance
IntegerIfThen::IntegerIfThen(
   IntegerExpression* a, 
   IntegerExpression* b, 
   const std::string&  op, 
   int line) :
   m_a(a),
   m_b(b),
   m_op(op),
   m_line(line)
{
}

// clean up the expression pointers
IntegerIfThen::~IntegerIfThen()
{
   delete m_a;
   delete m_b;
}

// run this line of the program
bool IntegerIfThen::execute(
   int /* lineNumber */, 
   bool next) const
{
   int aVal = m_a->value();
   int bVal = m_b->value();
   bool result = false;
   
   if (m_op.compare("=") == 0) {
      result = aVal == bVal;
   }
   else if (m_op.compare("<") == 0) {
      result = aVal < bVal;
   }
   else if (m_op.compare(">") == 0) {
      result = aVal > bVal;
   }
   else if (m_op.compare("<=") == 0) {
      result = aVal <= bVal;
   }
   else if (m_op.compare(">=") == 0) {
      result = aVal >= bVal;
   }
   else if (m_op.compare("<>") == 0) {
      result = aVal != bVal;
   }
   
   if (result) {
      Basic::instance()->gotoLine(m_line);
   }
   else
   {
      if (next) {
         Basic::instance()->nextLine();
      }
   }

   // When result == true, then the rest of the multi-statement
   // needs to be skipped (and control passes to the line number
   // specified by the THEN).  When result == false, execute the next
   // sub-statement in the multi-statement.
   return !result;
}

// list this line
void IntegerIfThen::list(std::ostream& os) const
{
   os << "IF " << m_a->list() << ' ' << m_op << ' ';
   os << m_b->list() << " THEN " << m_line;
}


// create a new statement instance
StringIfThen::StringIfThen(
   StringExpression* a, 
   StringExpression* b, 
   const std::string& op, 
   int line) :
   m_a(a),
   m_b(b),
   m_op(op),
   m_line(line)
{
}

// clean up the expression pointers
StringIfThen::~StringIfThen()
{
   delete m_a;
   delete m_b;
}

// run this line of the program
bool StringIfThen::execute(
   int /* lineNumber */, 
   bool next) const
{
   std::string aVal = m_a->value();
   std::string bVal = m_b->value();
   bool result = false;
   
   if (m_op.compare("=") == 0) {
      result = aVal == bVal;
   }
   else if (m_op.compare("<") == 0) {
      result = aVal < bVal;
   }
   else if (m_op.compare(">") == 0) {
      result = aVal > bVal;
   }
   else if (m_op.compare("<=") == 0) {
      result = aVal <= bVal;
   }
   else if (m_op.compare(">=") == 0) {
      result = aVal >= bVal;
   }
   else if (m_op.compare("<>") == 0) {
      result = aVal != bVal;
   }
   
   if (result) {
      Basic::instance()->gotoLine(m_line);
   }
   else
   {
      if (next) {
         Basic::instance()->nextLine();
      }
   }

   // When result == true, then the rest of the multi-statement
   // needs to be skipped (and control passes to the line number
   // specified by the THEN).  When result == false, execute the next
   // sub-statement in the multi-statement.
   return !result;
}

// list this line
void StringIfThen::list(std::ostream& os) const
{
   os << "IF " << m_a->list() << ' ' << m_op << ' ';
   os << m_b->list() << " THEN " << m_line;
}
