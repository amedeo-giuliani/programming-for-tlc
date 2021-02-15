#include "headers.h"

class APPHeader : public Header{
	
	public:
	APPHeader(int);
	virtual ~APPHeader();
	std::string getInfo() const;
	
};
