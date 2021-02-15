#include <memory>
#include <thread>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#ifndef H_CHAT_CLIENT
#define H_CHAT_CLIENT

constexpr size_t C_MTU = 512; /** <Chat MTU */

class ChatClient{
    public:
    /**
     * Class constructor.
     * @param port_num integer with the port number
     */
    ChatClient(std::string server_ip, int port_num);

    /**
     * Class destructor.
     */
    ~ChatClient();

    /**
     * Receives data from remote host.
     * @param buf buffer where the received data is stored
     * @return number of bytes received (-1 if error occurred)
     */
    int recv(char* buf);
   
    /**
     * Send data to remote host.
     * @param buf pointer to the buffer where the data to be sent is stored
     * @param size_to_tx size to transmit
     * @return number of bytes sent (-1 if error occurred)
     */
    int send(const char* buf, size_t size_to_tx);
    
    bool connect();
     
    private:
    int port; /**< server port number */
    std::string ip; /**< server address */
    bool exit; /**< true if run should end */
    int sock_fd; /**< data socket file descriptor */
    struct sockaddr_in server_addr;
    socklen_t addr_l;
    std::unique_ptr<std::thread> thr_rx; /**< thread for transmission */
    std::unique_ptr<std::thread> thr_tx; /**< thread for reception */

    /**
     * Set the socket options and bind.
     * @return false as soon as any of the operations it performs fails
     */
    bool options();

    /**
     * Function called by the destructor to close the sockets
     */
    void quit();

    /**
     * Function executed in a thread dispatched by the constructor 
     * to start the server listener
     */
    void run();

    /**
     * Function executed in a thread dispatched by the run function 
     * to start the transmission
     */
    void txChat();
};

#endif
