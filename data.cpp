#include <sstream>
#include "data.h"
#include "basic.h"

Data::Data(const std::vector<std::variant<int, float, std::string>>& vals) :
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
	std::vector<std::variant<int, float, std::string>>::const_iterator it = 
      _vals.cbegin();
	os << streamer{*it};		// print out first value
	for(  ++it; it != _vals.cend(); ++it ){
		os << "," << streamer{*it};	// print out remaining values
	}
}
#else

std::string toString(const std::variant<int, float, std::string>& val)
{
   std::ostringstream oss;
   if (std::holds_alternative<int>(val)) {
      oss << std::get<int>(val);
   }
   else if (std::holds_alternative<float>(val)) {
      // xxx - guarantee floats have a trailing .0 if needed.
      oss << std::get<float>(val);
   }
   else if (std::holds_alternative<std::string>(val)) {
      // This restores the double quotes around the string.
      oss << "\"" << std::get<std::string>(val) << "\"";
   }
   return oss.str();
}

// list this line
void Data::list(std::ostream& os) const
{
   os << "DATA ";
   std::vector<std::variant<int, float, std::string>>::const_iterator it = _vals.cbegin();
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
