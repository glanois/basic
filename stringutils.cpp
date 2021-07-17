#include "stringutils.h"

namespace StringUtils
{

// https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
// trim from left
std::string& ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
std::string& rtrim(std::string& s, const char* t)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
std::string& trim(std::string& s, const char* t)
{
    return ltrim(rtrim(s, t), t);
}

// copying versions

std::string ltrim_copy(std::string s, const char* t)
{
    return ltrim(s, t);
}

std::string rtrim_copy(std::string s, const char* t)
{
    return rtrim(s, t);
}

std::string trim_copy(std::string s, const char* t)
{
    return trim(s, t);
}

}


