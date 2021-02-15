/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <osi-layer.h>

OsiLayer::OsiLayer(const std::string& name) 
: 
layer_name{name},
upper_layer{},
lower_layer{},
out_q{},
in_q{}
{
  
}

OsiLayer::~OsiLayer()
{
  std::cout << "destructor of " << layer_name << std::endl; 
}

void OsiLayer::setLowerLayer(std::shared_ptr<OsiLayer> l_l)
{
  lower_layer = l_l;
}

void OsiLayer::setUpperLayer(std::shared_ptr<OsiLayer> u_l)
{
  upper_layer = u_l;
}


void OsiLayer::print(std::ostream& out) const
{
  out << layer_name;
}

void OsiLayer::sendToUpperLayer(std::shared_ptr<Packet> p) 
{
  // upper_layer is a weakpointer: to use it safe:
  // use it by calling lock(), that returns a shared pointer
  // then check if the shared pointer is not a nullptr
  std::shared_ptr<OsiLayer> sp = upper_layer.lock();
  if(sp!=nullptr) {
    sp->addToInQueue(p);
  }
}
void OsiLayer::sendToLowerLayer(std::shared_ptr<Packet> p)
{
  // lower_layer is a weakpointer: to use it safe:
   // use it by calling lock(), that returns a shared pointer
  // then check if the shared pointer is not a nullptr
  std::shared_ptr<OsiLayer> sp = upper_layer.lock();
  if(sp!=nullptr) {
    sp->addToOutQueue(p);
  }
}
void OsiLayer::addToOutQueue(std::shared_ptr<Packet> p)
{
  out_q.push(p);
}
void OsiLayer::addToInQueue(std::shared_ptr<Packet> p)
{
  in_q.push(p);
}

std::ostream& operator<<(std::ostream& out, const OsiLayer& layer)
{
  layer.print(out);
  return out;
}
