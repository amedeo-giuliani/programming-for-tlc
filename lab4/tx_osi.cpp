#include <iostream>
#include "mac-layer.h"
#include "phy-layer.h"

using namespace std;

int main(int argc, char** argv){
	
	mac_hdr tx_hdr1{};
	tx_hdr1.sn=10;
	tx_hdr1.src=1;
	tx_hdr1.dest=7;
	
	phy_hdr tx_hdr2{};
	tx_hdr2.bitrate = 20;
	tx_hdr2.timestamp=50;

	shared_ptr<OsiLayer> mac = make_shared<MacLayer>(tx_hdr1);
	shared_ptr<OsiLayer> phy = make_shared<PhyLayer>(tx_hdr2);
	
	mac->setLowerLayer(phy);
	phy->setUpperLayer(mac);
	
	size_t offset = 0;
	shared_ptr<Packet> pkt = make_shared<Packet>(5415,0);
	mac->sendToLowerLayer(pkt);
	phy->sendToLowerLayer(pkt);
	
	return 0;

}
