#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>
#include <variant>

typedef short LineNumber;

typedef short IntValue;

typedef float FloatValue;

class StringValue : public std::string
{
public:
   StringValue();
   StringValue(const bool hasQuotes);
   StringValue(const char* s);
   StringValue(const char* s, const bool hasQuotes);
   StringValue(const std::string& s);
   StringValue(const std::string& s, const bool hasQuotes);
   bool getHasQuotes() const;
protected:
   bool m_hasQuotes;
};

typedef std::variant<IntValue, FloatValue, StringValue> DataValue;

#endif
