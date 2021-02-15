#ifndef H_ECHO_SERVER
#define H_ECHO_SERVER

#include "memory"
#include "thread"

constexpr size_t C_MTU = 512;

class EchoServer{
    public:
    EchoServer(int);
    ~EchoServer();
    int accept();
    int recv(char*,int );
    int send(const char*, size_t, int);
    
    private:
    std::string ip;
    int port;
    bool exit;
    int lsock,sock;
    std::unique_ptr<std::thread> rxt;
    std::unique_ptr<std::thread> txt;
    bool optionsAndBind();
    void quit();
    void run();
    void txEcho(char*,int);
};

#endif
