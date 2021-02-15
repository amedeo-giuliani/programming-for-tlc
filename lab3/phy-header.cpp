#include "phy-header.h"

PHYHeader::PHYHeader(int s) : Header::Header(Header::OsiLayer::PHY,s) {}
PHYHeader::~PHYHeader() {}
std::string PHYHeader::getInfo() const { return "PHY Header"; }
