#include "phy-layer.h"

PhyLayer::PhyLayer() : OsiLayer::OsiLayer("PHY"), fn{"packet.txt"}, tx_hdr{}, rx_hdr{} {}
PhyLayer::PhyLayer(phy_hdr hdr) : OsiLayer::OsiLayer("PHY"), fn{"packet.txt"}, tx_hdr{hdr}, rx_hdr{} {}
PhyLayer::~PhyLayer() {}

void PhyLayer::sendToLowerLayer(std::shared_ptr<Packet> p){
	if(!out_q.empty()){
		auto pkt = out_q.front();
		out_q.pop();
		if(!tx_hdr.serialize(pkt->buf,pkt->offset)){
			std::cout << "serialization error" << std::endl;
			exit(-1);
		}
		std::cout << "offset: " << p->offset;
		std::ofstream fout(fn.c_str(), std::ios_base::app);
		if(fout.is_open()){
			for(int i = 0; i < sizeof(pkt->buf); i++){
				fout << pkt->buf[i];
			}
			fout << std::endl;
		}
		else{
			std::cout << "Error while opening file " << fn << std::endl;
			exit(-2);
		}
		fout.close();
	}
}

void PhyLayer::sendToUpperLayer(std::shared_ptr<Packet> p){
	std::srand(std::time(nullptr));
	int rn = std::rand();
	size_t o = 0;
	p = std::make_shared<Packet>(rn,o);
	std::ifstream fin(fn);
	std::string line;
	if(fin.is_open()){
		while(getline(fin,line)){
			strcpy(p->buf,line.c_str());
			p->offset=19;
			if(!rx_hdr.deserialize(p->buf,p->offset)){
				std::cout << "deserialization error" << std::endl;
				exit(-1);
			}
			std::cout << "offset: " << p->offset;
			std::cout << "rx_hdr.bitrate = " << (int)rx_hdr.bitrate << " rx_hdr.timestamp = " << (int)rx_hdr.timestamp << std::endl;
			//OsiLayer::sendToUpperLayer(p);
			std::shared_ptr<OsiLayer> sp = upper_layer.lock();
			if(sp!=nullptr) {
				sp->addToInQueue(p);
			}
			rn = rand();
			p->u_id = rn;
			p->offset = o;
		}
	}
	else{
		std::cout << "Error while opening file " << fn << std::endl;
		exit(-2);
	}
	std::ofstream fout(fn.c_str(), std::ios_base::trunc);
	fout.close();
}
