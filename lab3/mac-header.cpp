#include "mac-header.h"

MACHeader::MACHeader(int s) : Header::Header(Header::OsiLayer::MAC,s) {}
MACHeader::~MACHeader() {}
std::string MACHeader::getInfo() const { return "MAC Header"; }
