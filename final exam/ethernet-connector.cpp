/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <ethernet-connector.h>
#include <iostream>

const std::string EthConn::LOCAL_HOST = "127.0.0.1";

EthConn::EthConn(const std::string& ip_addr, int port_num)
:
ip(ip_addr),
port(port_num)
{

}

EthConn::EthConn(int port_num)
:
ip(EthConn::LOCAL_HOST),
port(port_num)
{

}

EthConn::~EthConn(){
	
}

void EthConn::print(std::ostream& out) const
{
  // EXERCISE 1: implement this method, which will print
  // relevant information on this class (e.g., that
  // it is an EthConn running on a certain IP and port).
  /*Add your code here*/
  out << "EthConn instance running on IP=" << ip << " and port=" << port << std::endl;
}

std::ostream& operator<<(std::ostream& out, const EthConn& conn) 
{
	// EXERCISE 1: implement this method so that works correctly
  // also when EthConn is overloaded.
  /*Add your code here*/
  conn.print(out);
  return out;
}
