#include <sstream>

#include "data.h"
#include "basic.h"

Data::Data(const std::vector<DataValue>& vals) :
   _vals(vals)
{
}

bool Data::execute(int /* lineNumber */, bool next) const
{
   // Just skip over DATA statement when executing.
   if (next)
   {
      Basic::instance()->nextLine();	// continue to next line
   }
   return true;
}

#if 0
// How to stream std::variant<…,…>
// https://stackoverflow.com/questions/47168477/how-to-stream-stdvariant
template<class T>
struct streamer {
    const T& val;
};
template<class T> streamer(T) -> streamer<T>;

template<class T>
std::ostream& operator<<(std::ostream& os, streamer<T> s) {
    os << s.val;
    return os;
}

template<class... Ts>
std::ostream& operator<<(std::ostream& os, streamer<std::variant<Ts...>> sv) {
   std::visit([&os](const auto& v) { os << streamer{v}; }, sv.val);
   return os;
}

// list this line
void Data::list(std::ostream& os) const{
	os << "DATA ";
	std::vector<DataValue>::const_iterator it = 
      _vals.cbegin();
	os << streamer{*it};		// print out first value
	for(  ++it; it != _vals.cend(); ++it ){
		os << "," << streamer{*it};	// print out remaining values
	}
}
#else

std::string toString(const DataValue& val)
{
   std::ostringstream oss;
   if (std::holds_alternative<IntValue>(val)) {
      oss << std::get<IntValue>(val);
   }
   else if (std::holds_alternative<FloatValue>(val)) {
      // xxx - guarantee floats have a trailing .0 if needed.
      oss << std::get<FloatValue>(val);
   }
   else if (std::holds_alternative<StringValue>(val)) {
      // If it was a quoted string, add the double quotes.
      // Otherwise just print it without the double quotes.
      auto v = std::get<StringValue>(val);
      if (v.getHasQuotes()) {
         oss << "\"" << v << "\"";
      }
      else {
         oss << v;
      }
   }
   return oss.str();
}

// list this line
void Data::list(std::ostream& os) const
{
   os << "DATA ";
   std::vector<DataValue>::const_iterator it = _vals.cbegin();
   os << toString(*it); // print out first value
   for (++it; it != _vals.cend(); ++it) {
      os << "," << toString(*it);	// print out remaining values
   }
}
#endif

// run before main program execution
void Data::preExecute() const{
	Basic::instance()->pushData(_vals);
}
