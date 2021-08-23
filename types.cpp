#include <iostream>

#include "types.h"

StringValue::StringValue() : 
   m_hasQuotes(true),
   std::string()
{
}

StringValue::StringValue(const bool hasQuotes) : 
   m_hasQuotes(hasQuotes),
   std::string()
{
}

StringValue::StringValue(const char* s) : 
   m_hasQuotes(true), 
   std::string(s)
{
}

StringValue::StringValue(
   const char* s,
   const bool hasQuotes) : 
   m_hasQuotes(hasQuotes), 
   std::string(s)
{
}

StringValue::StringValue(const std::string& s) : 
   m_hasQuotes(true), // Has quotes by default.
   std::string(s)
{
}

StringValue::StringValue(
   const std::string& s,
   const bool hasQuotes) : 
   m_hasQuotes(hasQuotes), 
   std::string(s)
{
}

bool StringValue::getHasQuotes() const
{
   return m_hasQuotes;
}

