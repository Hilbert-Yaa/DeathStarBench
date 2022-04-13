#pragma once

#include <memory>
#include <thrift/protocol/TJSONProtocol.h>

namespace social_network {

class Tracer {
public:
  Tracer(const char *fname);
  ~Tracer();
  Tracer(const Tracer &) = delete;
  Tracer(Tracer &&) = delete;
  Tracer &operator=(const Tracer &) = delete;
  Tracer &operator=(Tracer &&) = delete;
  template <typename T> void log(const T &args) {
    args.write(protocol.get());
    protocol->getTransport()->flush();
  }

private:
  std::shared_ptr<apache::thrift::protocol::TJSONProtocol> protocol;
};

} // namespace social_network