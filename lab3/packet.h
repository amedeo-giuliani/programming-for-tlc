#include <iostream>
//#include <vector>
#include <map>
#include <initializer_list>
#include <memory>
#include "headers.h"

class Packet{
	
	private:
	//std::vector<Header*> pkt;
	std::map<Header::OsiLayer,std::shared_ptr<Header>> pkt;
	int hdr_counter;
	
	public:
	Packet(std::initializer_list<std::shared_ptr<Header>> il);
	~Packet();
	bool addHeader(std::shared_ptr<Header>);
	int getNumHeaders() const;
	void print() const;
};
