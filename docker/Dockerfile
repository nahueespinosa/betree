FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update \
  && apt-get install --no-install-recommends -y \
    apt-transport-https \
    apt-utils \
    bash-completion \
    build-essential \
    ca-certificates \
    cmake \
    git \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/betree

COPY . /usr/src/betree

ENV WITHIN_DEV 1

ENTRYPOINT ["/bin/bash"]
