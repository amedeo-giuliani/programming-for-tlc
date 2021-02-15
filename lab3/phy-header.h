#include "headers.h"

class PHYHeader : public Header{

	public:
	PHYHeader(int);
	virtual ~PHYHeader();
	std::string getInfo() const;

};
