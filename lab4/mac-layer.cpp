#include "mac-layer.h"

MacLayer::MacLayer() : OsiLayer::OsiLayer("MAC"), tx_hdr{}, rx_hdr{} {}
MacLayer::MacLayer(mac_hdr hdr) : OsiLayer::OsiLayer("MAC"), tx_hdr{hdr}, rx_hdr{} {}
MacLayer::~MacLayer() {}

void MacLayer::sendToLowerLayer(std::shared_ptr<Packet> p) {
	if(!tx_hdr.serialize(p->buf,p->offset)){
		std::cout << "serialization error" << std::endl;
		exit(-1);
	}
	std::cout << "offset: " << p->offset;
	//OsiLayer::sendToLowerLayer(p);
	std::shared_ptr<OsiLayer> sp = lower_layer.lock();
	if(sp!=nullptr) {
		sp->addToOutQueue(p);
	}
}

void MacLayer::sendToUpperLayer(std::shared_ptr<Packet> p){
	if(!in_q.empty()){
		do{
		auto pkt = in_q.front();
		in_q.pop();
		//pkt->offset = 0;
		pkt->offset=0;
		if(!rx_hdr.deserialize(pkt->buf,pkt->offset)){
			std::cout << "deserialization error" << std::endl;
			exit(-1);
		}
		
		std::cout << "rx_hdr.sn = " << (int)rx_hdr.sn << " rx_hdr.src = " << (int)rx_hdr.src << " rx_hdr.dest = " << (int)rx_hdr.dest << std::endl;
		}while(!in_q.empty());
	}
}
