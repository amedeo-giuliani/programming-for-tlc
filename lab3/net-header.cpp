#include "net-header.h"

NETHeader::NETHeader(int s) : Header::Header(Header::OsiLayer::NET,s) {}
NETHeader::~NETHeader() {}
std::string NETHeader::getInfo() const { return "NET Header"; }
