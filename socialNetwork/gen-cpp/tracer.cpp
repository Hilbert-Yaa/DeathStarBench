#include "tracer.h"

#include <iostream>
#include <memory>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TTransport.h>

namespace social_network {

Tracer::Tracer(const char *fname) {
  using namespace apache::thrift::transport;
  using namespace apache::thrift::protocol;
  using std::cerr;
  using std::make_shared;
  auto trans = std::make_shared<TSimpleFileTransport>(fname, false, true);
  if (!trans->isOpen()) {
    cerr << "Failed to open file transport...\n";
    exit(-3);
  }
  auto buffered_trans = std::make_shared<TBufferedTransport>(
      std::static_pointer_cast<TTransport>(trans));
  protocol = make_shared<TJSONProtocol>(
      TJSONProtocol(std::static_pointer_cast<TTransport>(buffered_trans)));
};

Tracer::~Tracer() { protocol->getTransport()->close(); }

} // namespace social_network