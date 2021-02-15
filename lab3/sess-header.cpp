#include "sess-header.h"

SESSHeader::SESSHeader(int s) : Header::Header(Header::OsiLayer::SESS,s) {}
SESSHeader::~SESSHeader() {}
std::string SESSHeader::getInfo() const { return "SESS Header"; }
