#include "headers.h"

Header::Header(Header::OsiLayer l,int s) : layer(l),size(s) {}
Header::~Header() {}

std::string Header::getInfo() const { return "Generic header"; }
int Header::getSize() const { return size; }
void Header::setSize(int s) { size = s; }
Header::OsiLayer Header::getLayer() const { return layer; }
