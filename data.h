#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <variant>

#include "program.h"

typedef short IntValue;
typedef float FloatValue;
class StringValue : public std::string
{
public:
   StringValue();
   StringValue(const bool hasQuotes);
   StringValue(const char*);
   StringValue(const char*, const bool hasQuotes);
   bool getHasQuotes() const;
protected:
   bool m_hasQuotes;
};

typedef std::variant<IntValue, FloatValue, StringValue> DataValue;

/*
This class implements the DATA statement, storing values
for later use by READ.
*/
class Data : public Program {
public:
	Data(const std::vector<DataValue>& vals);
	
   virtual bool execute(int lineNumber, bool next) const;
	void list(std::ostream& os) const;	// list this line
	void preExecute() const;			// run before main program execution
	
private:
	std::vector<DataValue> _vals;
};

#endif
