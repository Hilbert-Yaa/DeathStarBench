#! /bin/bash

exec ComposePostService | tee /social-network-microservices/logs/trace.dat 2>&1
# exec ComposePostService