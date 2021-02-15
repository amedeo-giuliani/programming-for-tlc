#include "headers.h"

class MACHeader : public Header{
	
	public:
	MACHeader(int);
	virtual ~MACHeader();
	std::string getInfo() const;
	
};
