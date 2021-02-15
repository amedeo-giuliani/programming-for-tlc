/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <memory>
#include "osi-layer.h"
#include "wrong-osi-layer.h"

int
main(int argc, char const *argv[])
{
  //GOOD
  std::shared_ptr<OsiLayer> network_l(std::make_shared<OsiLayer>("NET1"));
  std::cout << "network_l = " << *network_l << " network_l counter = " << network_l.use_count() << std::endl;
  
  std::shared_ptr<OsiLayer> mac_l(std::make_shared<OsiLayer>("MAC1"));
  std::cout << "mac_l = " << *mac_l << " mac_l counter = " << mac_l.use_count() << std::endl;

  network_l->setLowerLayer(mac_l);
  mac_l->setUpperLayer(network_l);
  std::cout << "network_l = " << *network_l << " network_l counter = " << network_l.use_count() << std::endl;
  std::cout << "mac_l = " << *mac_l << " mac_l counter = " << mac_l.use_count() << std::endl;

  std::shared_ptr<Packet> p1 = std::make_shared<Packet>(1);
  network_l->sendToLowerLayer(p1);
  std::shared_ptr<Packet> p2 = std::make_shared<Packet>(2);
  mac_l->sendToUpperLayer(p2);

  std::cout << "-----------------------------------------------------------" << std::endl;

  //THE FOLLOWING IS BAD: MEMORY LEAK!! THEY NEVER GET DESTROYED. WHY? BECAUSE 
  //THERE IS A CIRCULAR SHARED POINTER DEPENDENCY. DON'T YOU TRUST: CHECK THE DESTRUCTOR
  std::shared_ptr<WrongOsiLayer> w_network_l(std::make_shared<WrongOsiLayer>("NET2"));
  std::cout << "w_network_l = " << *w_network_l << " w_network_l counter = " << w_network_l.use_count() << std::endl;
  
  std::shared_ptr<WrongOsiLayer> w_mac_l(std::make_shared<WrongOsiLayer>("MAC2"));
  std::cout << "w_mac_l = " << *w_mac_l << " w_mac_l counter = " << w_mac_l.use_count() << std::endl;

  w_network_l->setLowerLayer(w_mac_l);
  w_mac_l->setUpperLayer(w_network_l);
  std::cout << "w_network_l = " << *w_network_l << " w_network_l counter = " << w_network_l.use_count() << std::endl;
  std::cout << "w_mac_l = " << *w_mac_l << " _wmac_l counter = " << w_mac_l.use_count() << std::endl;

  std::cout << "-----------------------------------------------------------" << std::endl;
  //HERE YOU HAVE THE DESTRUCTOR COUT

  return 0;
}
