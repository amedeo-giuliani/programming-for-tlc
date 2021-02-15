#include "headers.h"

class PRESHeader : public Header{
	
	public:
	PRESHeader(int);
	virtual ~PRESHeader();
	std::string getInfo() const;
	
};
