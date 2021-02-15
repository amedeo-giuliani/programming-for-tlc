#include "headers.h"

class NETHeader : public Header{

	public:
	NETHeader(int);
	virtual ~NETHeader();
	std::string getInfo() const;

};
