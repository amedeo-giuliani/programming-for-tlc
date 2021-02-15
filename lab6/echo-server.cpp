#include <echo-server.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

EchoServer::EchoServer(int pn) : port(pn), ip("127.0.0.1"), exit(false), lsock(-1), sock(-1){
    lsock = socket(AF_INET,SOCK_STREAM,0);
    if(lsock < 0){
        std::cout << "OPEN SOCKET ERROR" << std::endl;
        close(lsock);
        return;
    }
    if(!optionsAndBind()){
        std::cout << "BIND SOCKET ERROR" << std::endl;
        close(lsock);
        return;
    }
    rxt = std::unique_ptr<std::thread>(new std::thread(&EchoServer::run,this));
}

EchoServer::~EchoServer(){
    quit();
    if(rxt && rxt->joinable()){
        rxt->join();    
    }
    if(txt && txt->joinable()) {
        txt->join();
    }
    std::cout << "joined" << std::endl;
}

void EchoServer::run(){
    char buf[C_MTU];
    while(!exit) {
        int curr_sock = accept();
        if(curr_sock >= 0) {
            if(txt == nullptr) {
                txt = std::unique_ptr<std::thread>(new std::thread(&EchoServer::txEcho,this,buf,curr_sock));
            }
            //std::cout << buf;
            memset(buf,0,C_MTU);
            txt->detach();
            txt.reset();
        }
    }
}

void EchoServer::txEcho(char* buf, int curr_sock){
    int size = recv(buf,curr_sock);
    if(size <= 0) {
        std::cout << "read size less than zero size" << std::endl;
        close(curr_sock);
        sock = -1;
    }
    if(send(buf,size,curr_sock) >= 0) {
        send("\n",1,curr_sock);
    }
}

void EchoServer::quit(){
    exit = true;
    if(lsock >= 0) {
        close(lsock);
        lsock = -1;
    }
    if(sock >= 0){
        close(sock);
        sock = -1;
    }
}

bool EchoServer::optionsAndBind(){
    int option(1);
    setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR,(char*)&option, sizeof(option));
    struct sockaddr_in my_addr = {0};
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(lsock,(struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        std::cout << "ERROR: BIND SOCKET" << std::endl;
        if(lsock >= 0) {
            close(lsock);
        }
        return false;
    }

    if (listen(lsock, 20) < 0) {
        std::cout << "ERROR: LISTEN SOCKET" << std::endl;
        return false;
    }
    return true;
}

int EchoServer::accept(){
    struct sockaddr_in client_addr;
    socklen_t addr_l = sizeof(client_addr);
    sock = ::accept(lsock,(struct sockaddr*)&client_addr,&addr_l);
    if(sock < 0) {
        std::cout << "ERROR: ACCEPT CONNECTION" << std::endl;
        if(lsock >= 0) {
            close(lsock);
            lsock = - 1;
        }
        return false;
    }
    std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
    ip = inet_ntoa(client_addr.sin_addr);
    return sock;
}


int EchoServer::recv(char* buf, int curr_sock){
    int rcv_size = ::recv(sock,buf,C_MTU,0);
    if(rcv_size < 0) {
        std::cout << "ERROR: RECV" << std::endl;
        if(sock >= 0) {
            close(curr_sock);
            curr_sock = -1;
        }
    }
    return rcv_size;
}


int EchoServer::send(const char* buf, size_t tx_size, int curr_sock)
{
    if(sock < 0) {
        return -1;
    }
    int sent_size = ::send(curr_sock,buf,tx_size,0); // send the data through sckfd
    if(sent_size < 0) { // the send returns a size of -1 in case of errors
        std::cout << "ERROR: SEND" << std::endl;
        if(curr_sock >= 0) {
            close(curr_sock);
            curr_sock = -1;
        }
        return -4;
    }
    return sent_size;
}
