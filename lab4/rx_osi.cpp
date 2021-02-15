#include <iostream>
#include "mac-layer.h"
#include "phy-layer.h"

using namespace std;

int main(int argc, char** argv){
	
	shared_ptr<OsiLayer> mac = make_shared<MacLayer>();
	shared_ptr<OsiLayer> phy = make_shared<PhyLayer>();
	
	mac->setLowerLayer(phy);
	phy->setUpperLayer(mac);
	
	shared_ptr<Packet> pkt;
	
	phy->sendToUpperLayer(pkt);
	mac->sendToUpperLayer(pkt);
	
	return 0;

}
