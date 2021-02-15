#include "tran-header.h"

TRANHeader::TRANHeader(int s) : Header(OsiLayer::TRAN,s) {}
TRANHeader::~TRANHeader() {}
std::string TRANHeader::getInfo() const { return "Transport Header" ; }
