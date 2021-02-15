#include <chat-client.h>

ChatClient::ChatClient(std::string server_ip, int server_port) : port(server_port), ip(server_ip), exit(false), sock_fd(-1) {
    server_addr = {0};
    addr_l = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) { 
        std::cout << "ERROR CONVERTING IP TO INTERNET ADDR" << std::endl;
        return;
    }
    
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0){
        std::cout << "ERROR: OPEN SOCKET" << std::endl;
        close(sock_fd);
        return;
    }
    if(!options()) {
        std::cout << "ERROR: OPTIONS" << std::endl;
        close(sock_fd);
        return;
    }
    thr_rx = std::unique_ptr<std::thread>(new std::thread(&ChatClient::run,this));
}

ChatClient::~ChatClient() {
    quit();
    if(thr_rx && thr_rx->joinable()) {
        thr_rx->join();
    }
    if(thr_tx && thr_tx->joinable()) {
        thr_tx->join();
    }
    std::cout << "joint" << std::endl;
}

void ChatClient::run() {
  char buf[C_MTU];
  while(!exit) {
    if(connect()) {
      if(thr_tx == nullptr) {
        thr_tx = std::unique_ptr<std::thread>(
          new std::thread (&ChatClient::txChat,this));
      }
      while(!exit) {
        if(recv(buf) <= 0) {
          std::cout << "read size less than zero size" << std::endl;
          close(sock_fd);
          sock_fd = -1;
          break;
        }
        std::cout << buf;
        memset(buf,0,C_MTU); // this cleans the buffer for a new read
      }
    }
  }
}

void ChatClient::txChat() {
  while(!exit) {
    std::string to_tx;
    std::getline(std::cin, to_tx);
    if(exit) {
      break;
    }
    if(send(to_tx.c_str(),to_tx.length()) >= 0) {
      send("\n",1);
    }
  }
}

int ChatClient::recv(char* buf)
{
  int rcv_size = ::recv(sock_fd,buf,C_MTU,0);
  if(rcv_size < 0) {
    std::cout << "ERROR: RECV" << std::endl;
    if(sock_fd >= 0) {
      close(sock_fd);
      sock_fd = -1;
    }
  }
  return rcv_size;
}


int ChatClient::send(const char* buf, size_t size_to_tx)
{
  if(sock_fd<0) {
    return -1;
  }
  int sent_size = ::send(sock_fd,buf,size_to_tx,0); // send the data through sckfd
  if(sent_size < 0) { // the send returns a size of -1 in case of errors
    std::cout << "ERROR: SEND" << std::endl;
    if(sock_fd >= 0) {
      close(sock_fd);
      sock_fd = -1;
    } // if error close the socket and exit
    return -4;
  }
  return sent_size;
}

bool ChatClient::connect(){    
    
    if (::connect(sock_fd, (struct sockaddr*) &server_addr, addr_l) < 0) { 
        std::cout << "ERROR: CONNECT" << std::endl;
        if(sock_fd>=0) {
            close(sock_fd);
            sock_fd = - 1;
        }
        return false;
    }
    return true;
}

bool ChatClient::options() {
  int option(1);
  setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,(char*)&option, sizeof(option));
  return true;
}

void ChatClient::quit() {
  exit = true;
  if(sock_fd >= 0){
    close(sock_fd);
    sock_fd = -1;
  }
}
