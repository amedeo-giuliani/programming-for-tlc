/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server-connection.h>
#include <modem.h>
#include <basic-utilities.h>
#include <iostream>
#include <cctype>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Method use to accept a new connection from an opened server
 * @param server pointer to an EthConn, that points to a TcpServer
 * @return false if the object is not a TcpServer or if the accept fails
 */
bool acceptTcpConn(std::shared_ptr<EthConn> server) 
{
  auto casted_server = std::dynamic_pointer_cast<TcpServerConnection>(server);
  if(casted_server != nullptr && casted_server->acceptConn()) {
    std::cout << "server accepted client " << casted_server->getIp() << std::endl;
    return true;
  }
  return false;
}

int main(int argc, char** argv) 
{

  // READ from argv the command line argument vector, by checking the arguments
  // counter (argc), i.e.,
  //   ./tcp_server has argc = 1 and no command line arguments
  //   ./tcp_server 55556 has argc = 2 and the socket port as argument
  const int listen_port = argc ==1 ? 55555 : atoi(argv[1]);
  std::shared_ptr<EthConn> server = std::make_shared<TcpServerConnection>(listen_port);

  // EXERCISE 4: Create an object of the class Modem 
  // (the name of the variable is modem1)
  
  /*Add your code here*/
  Modem modem1{};
  
  if(!acceptTcpConn(server)) {
    return (int)TestResult::FAILED;
  }

  auto io_buffer = std::make_shared<std::array<char,MTU>>();

  bool is_exit = false;
  size_t tx_size = 0;
  while(!is_exit) {
    // EXERCISE 5: Reset the content of the io_buffer, and use it to receive
    // data from server. Store also the data size into an integer variable
    // rx_size. If the read data is valid, print it to standard output,  
    // otherwise exit the main by returning TestResult::FAILED.
    // To access its data you can use the instruction "io_buffer->data()".
    
    /*Add your code here*/
    memset(io_buffer->data(),0,MTU);
    size_t rx_size = server->receive(io_buffer);
    if(rx_size>0){
    	std::cout << "IO BUFFER: " << io_buffer->data() << std::endl;
    }
    else{
    	return (int)TestResult::FAILED;
    }
    
    modem1.configure(io_buffer,rx_size,tx_size,is_exit);

    std::cout << "configuration result = " << io_buffer->data() << std::endl;

    if(server->transmit(io_buffer,tx_size) < 0) {
      return (int)TestResult::FAILED;
    }
  }

  std::cout << *server << std::endl;

  std::cout << "End of exam, number of successful configurations = " 
            << modem1.getConfigurationsCounter() << std::endl;
  return (int)TestResult::PASSED;

}
