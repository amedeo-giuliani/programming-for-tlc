/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <chrono>
#include <signal.h>
#include <string.h>
#include <chat-server.h>


int
main(int argc, char const *argv[])
{

  struct sigaction act;// structure that contains the handler
  memset(&act, '\0', sizeof(act));
  act.sa_handler = SIG_IGN; // handler that ignores the signal
  if (sigaction(SIGPIPE, &act, NULL) < 0) { // set the handler to
  // SIGPIPE
    std::cerr << "SIGPIPE" << std::endl; //
  }

  ChatServer server(55555);
  
  // THE NEXT LINE SLEEPS FOR 500 seconds before to exit
  std::this_thread::sleep_for(std::chrono::seconds(500));
  return 0;
}
