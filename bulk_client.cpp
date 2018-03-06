#include <zmq.h>
#include <iostream>

int main (int, char**)
{
  void *context = zmq_ctx_new ();
  void *requester = zmq_socket (context, ZMQ_PUSH);
  zmq_connect (requester, "tcp://localhost:5555");

  std::string cmd;
  while (std::getline(std::cin, cmd))
  {
    zmq_send (requester, cmd.c_str(), cmd.size(), 0);
  }
  zmq_close (requester);
  zmq_ctx_destroy (context);
  return 0;
}
