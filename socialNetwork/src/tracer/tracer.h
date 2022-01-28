#pragma once
#include "../../gen-cpp/ComposePostService.h"
#include <thrift/protocol/TProtocol.h>

namespace social_network {
void TRACE(const social_network::ComposePostService_ComposePost_args &args,
           const char *fname = nullptr);
void DUMP(apache::thrift::protocol::TProtocol *iprot);
} // namespace tracer