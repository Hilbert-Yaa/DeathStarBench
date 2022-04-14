#include "tracer.h"

#include <iostream>
#include <memory>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSimpleFileTransport.h>
#include <thrift/transport/TTransport.h>

namespace social_network {

std::mutex Tracer::m;

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
  protocol = make_shared<TBinaryProtocol>(
      TBinaryProtocol(std::static_pointer_cast<TTransport>(buffered_trans)));
};

Tracer::~Tracer() { protocol->getTransport()->close(); }

} // namespace social_network