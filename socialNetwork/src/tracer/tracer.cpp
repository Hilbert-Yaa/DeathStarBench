#include "tracer.h"
#include <fcntl.h>
#include <iostream>
#include <thrift/protocol/TDebugProtocol.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TProtocolException.h>
#include <thrift/protocol/TProtocolTap.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TFDTransport.h>
#include <thrift/transport/TTransport.h>
#include <thrift/transport/TTransportUtils.h>

namespace social_network {
// TODO: dump the protocols
void TRACE(const social_network::ComposePostService_ComposePost_args &args,
           const char *fname) {
  using std::cout;
  using std::endl;
  using std::shared_ptr;
  using namespace apache::thrift::protocol;
  using namespace apache::thrift::transport;
  std::cout
      << "########################### Separator ###########################"
      << std::endl;

  TFDTransport *fdtptr;
  int fd = open(fname, O_WRONLY);
  fdtptr = new TFDTransport(fd == -1 ? STDOUT_FILENO : fd);
  auto dump_prot = new TDebugProtocol(shared_ptr<TTransport>(
      new TBufferedTransport(shared_ptr<TTransport>(fdtptr))));
  args.write(dump_prot);
  dump_prot->getTransport()->flush();
}

void DUMP(apache::thrift::protocol::TProtocol *iprot) {
  using namespace apache::thrift::protocol;
  using namespace apache::thrift::transport;
  using std::shared_ptr;
  // TODO: insert a wiretap here
  shared_ptr<TProtocol> dump_prot(
      new TDebugProtocol(shared_ptr<TTransport>(new TBufferedTransport(
          shared_ptr<TTransport>(new TFDTransport(STDOUT_FILENO))))));
  TProtocolTap tap(shared_ptr<TProtocol>(iprot, [](TProtocol *) {}), dump_prot);
  // start dumping the protocol
  try {
    std::string name;
    protocol::TMessageType messageType;
    int32_t seqid_tap;
    while (true) {
      tap.readMessageBegin(name, messageType, seqid_tap);
      // protocol::skip(tap, apache::thrift::protocol::T_STRUCT);
      tap.readMessageEnd();
    }
  } catch (const protocol::TProtocolException e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    dump_prot->getTransport()->flush(); // if any, directly flush the output
  }
}

} // namespace social_network