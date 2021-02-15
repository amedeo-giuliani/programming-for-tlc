#include "packet.h"

Packet::Packet(std::initializer_list<std::shared_ptr<Header>> hl){
	hdr_counter = hl.size();
	for(std::shared_ptr<Header> i : hl){
		pkt.insert({i->getLayer(),i});
	}
}

Packet::~Packet() {
	for(auto i : pkt){
		i.second.reset();
	}
}

bool Packet::addHeader(std::shared_ptr<Header> h) {
	auto it = pkt.find(h->getLayer());
	if((h==nullptr)||(it!=pkt.end())){
		if(it!=pkt.end())
			h.reset();
		return false;
	}
	pkt.insert({h->getLayer(),h});
	hdr_counter++;
	return true;
}

int Packet::getNumHeaders() const { return hdr_counter; }

void Packet::print() const {
	for(const auto i : pkt){
		std::cout << "Header size: " << i.second->getSize() << "B" << std::endl << "Header info: " << i.second->getInfo() << std::endl;
	}
}
