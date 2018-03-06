#include <zmq.hpp>
#include <iostream>
#include <async_otus/async.h>

int main ()
{
  std::size_t bulk = 5;
  auto h = async::connect(bulk);

  //  Prepare our context and socket
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_PULL);
  socket.bind ("tcp://*:5555");

  while (true)
  {
    zmq::message_t request;
    socket.recv (&request);
    std::string cmd = {static_cast<const char*>(request.data()), request.size()};
    cmd += "\n";
    async::receive(h, cmd.c_str(), cmd.length());
  }
  async::disconnect(h);

  return 0;
}
