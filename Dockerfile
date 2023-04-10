FROM ubuntu:20.04

LABEL Description = "Build environment"

ARG DEBIAN_FRONTEND=non_interactive

COPY . /usr/src/cpp_test

WORKDIR /usr/src/cpp_test

CMD tail -f /dev/null

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    cmake \
    libboost-all-dev

RUN cd /usr/src/cpp_test && \
    mkdir build && \
    cd build && \
    cmake -b . -s .. && \
    make 
    