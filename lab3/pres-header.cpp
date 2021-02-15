#include "pres-header.h"

PRESHeader::PRESHeader(int s) : Header::Header(Header::OsiLayer::PRES,s) {}
PRESHeader::~PRESHeader() {}
std::string PRESHeader::getInfo() const { return "PRES Header"; }
