#include <chat-client.h>
#include <chrono>
#include <iostream>
#include <signal.h>
#include <string.h>

int main(int argc, char** argv){
    struct sigaction act;// structure that contains the handler
    memset(&act, '\0', sizeof(act));
    act.sa_handler = SIG_IGN; // handler that ignores the signal
    if (sigaction(SIGPIPE, &act, NULL) < 0) { // set the handler to
                                              // SIGPIPE
        std::cerr << "SIGPIPE" << std::endl; //
    }
    ChatClient client("127.0.0.1",55555);
    
    // THE NEXT LINE SLEEPS FOR 500 seconds before to exit
    std::this_thread::sleep_for(std::chrono::seconds(500));
    return 0;
}
