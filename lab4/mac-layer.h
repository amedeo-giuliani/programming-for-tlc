#include "osi-layer.h"
#include "mac-hdr.h"
#include <string>
#include <iostream>

class MacLayer : public OsiLayer{

	private:
	mac_hdr tx_hdr;
	mac_hdr rx_hdr;
	
	public:
	MacLayer();
	MacLayer(mac_hdr);
	~MacLayer();
	
	void sendToLowerLayer(std::shared_ptr<Packet>);
	void sendToUpperLayer(std::shared_ptr<Packet>);

};
