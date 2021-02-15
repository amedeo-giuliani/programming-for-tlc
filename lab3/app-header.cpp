#include "app-header.h"

APPHeader::APPHeader(int s) : Header::Header(Header::OsiLayer::APP,s) {}
APPHeader::~APPHeader() {}
std::string APPHeader::getInfo() const { return "APP Header"; }
