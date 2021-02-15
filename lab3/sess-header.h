#include "headers.h"

class SESSHeader : public Header{
	
	public:
	SESSHeader(int);
	virtual ~SESSHeader();
	std::string getInfo() const;
	
};
