#include "osi-layer.h"
#include "phy-hdr.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>

class PhyLayer : public OsiLayer{

	private:
	std::string fn;
	phy_hdr tx_hdr;
	phy_hdr rx_hdr;

	public:
	PhyLayer();
	PhyLayer(phy_hdr);
	~PhyLayer();
	
	using OsiLayer::sendToUpperLayer;
	void sendToLowerLayer(std::shared_ptr<Packet>);
	void sendToUpperLayer(std::shared_ptr<Packet>);

};
