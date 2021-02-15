/* 
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
 */

#include <tcp-server-connection.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

TcpServerConnection::TcpServerConnection(int port_num)
:
EthConn(port_num),
l_sock_fd(-1),
sock_fd(-1),
connections_count(0)
{
  l_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (l_sock_fd < 0){ 
    std::cout << "ERROR: OPEN SOCKET" << std::endl;
    close(l_sock_fd);
    return;
  }
  if(!optionsAndBind()) {
    std::cout << "ERROR: BIND" << std::endl;
    close(l_sock_fd);
    return;
  }
}

TcpServerConnection::~TcpServerConnection() {
  if(l_sock_fd >= 0) {
    close(l_sock_fd);
  }
  if(sock_fd >= 0) {
    close(sock_fd);
  }
}

bool TcpServerConnection::optionsAndBind() 
{
  int option(1);
  setsockopt(l_sock_fd, SOL_SOCKET, SO_REUSEADDR, 
                  (char*)&option, sizeof(option));
  struct sockaddr_in my_addr = {0}; // set all elements of the struct to 0
  my_addr.sin_family = AF_INET; // address family is AF_INET (IPV4)

  // convert listener_port to network number format
  my_addr.sin_port = htons(port); 
  // accept connection from all interfaces of the Network Interface Card (NIC)
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  // bind the socket to the port
  if (bind(l_sock_fd,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { 
    std::cout << "ERROR: BIND SOCKET" << std::endl;
    close(l_sock_fd);
    return false;
  }

  // Accept at max 1 client at a time: by changing 1 to 5 in the next line 
  // you accept at most the connection of 5 clients in parallel.
  if (listen(l_sock_fd, 1) < 0) { 
    std::cout << "ERROR: LISTEN SOCKET" << std::endl;
    close(l_sock_fd);
    return false;
  //ERR
  }
  return true;
}

bool TcpServerConnection::acceptConn() 
{
  struct sockaddr_in client_addr;
  socklen_t addr_l = sizeof(client_addr);
  sock_fd = accept(l_sock_fd, (struct sockaddr*) &client_addr, &addr_l);
  if(sock_fd < 0) {
    std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
    return false;
  }
  // The next line prints the client address, converting to char* 
  // the network address (inet_ntoa)
  std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl; 
  ip = inet_ntoa(client_addr.sin_addr);
  connections_count++;
  return true;
}


int TcpServerConnection::receive(std::shared_ptr<std::array<char,MTU>> buf)  
{
  if(sock_fd < 0) {
    return -1;
  }
  int rcv_size = recv(sock_fd,buf->data(),buf->max_size(),0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    close(sock_fd);
    sock_fd = -1;
  }
  return rcv_size;
}


int TcpServerConnection::transmit(std::shared_ptr<std::array<char,MTU>> buf, 
  size_t size_to_tx) 
{
  if(sock_fd < 0) {
    return -1;
  }
  int sent_size = send(sock_fd,buf->data(),size_to_tx,0); // send the data through sckfd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    close(sock_fd); // if error close the socket and exit
    sock_fd = -1;
  }
  return sent_size;
}

void TcpServerConnection::print(std::ostream& out) const
{
  // EXERCISE 1: implement this method, which will print
  // relevant information on this class (e.g., that
  // it is an TcpServerConnection, the last IP that 
  // connected and the number of connections so far.
  /*Add your code here*/
  out << "TcpServerConnection instance running on IP=" << ip << " and port=" << port << std::endl;
}
