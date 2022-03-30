FROM yg397/thrift-microservice-deps:xenial AS builder

RUN --mount=type=cache,target=/var/cache/apt \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y ccache

# config ccache
RUN /usr/sbin/update-ccache-symlinks
ENV PATH="/usr/lib/ccache:$PATH"
RUN echo $(ccache -s)

COPY ./ /social-network-microservices
RUN --mount=type=cache,id=ccache,target=/root/.ccache \
    cd /social-network-microservices \
    && mkdir -p build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make -j$(nproc) \
    && make install

# finish build
RUN echo $(ccache -s)

FROM ubuntu:16.04

# Copy compiled C++ binaries and dependencies
COPY --from=builder /usr/local/bin/* /usr/local/bin/
COPY --from=builder /usr/local/lib/* /usr/local/lib/

# Install system dependencies
RUN --mount=type=cache,target=/var/cache/apt \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        openssl \
        ca-certificates \
        libsasl2-2 \
        libmemcached11 \
        libmemcachedutil2 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /social-network-microservices

