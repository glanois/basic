#include "rem.h"
#include "basic.h"

using std::endl;
using std::cout;

// instantiate rem statement
Rem::Rem(const char* remark) : remark_(remark) {
}

// list this line
void Rem::list(std::ostream& os) const{
	os << remark_;
}
