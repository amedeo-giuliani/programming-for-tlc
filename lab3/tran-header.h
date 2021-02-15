#include "headers.h"

class TRANHeader : public Header {
	
	public:
	TRANHeader(int);
	virtual ~TRANHeader();
	std::string getInfo() const;
};
