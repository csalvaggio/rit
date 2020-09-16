#!/bin/bash
xhost + 127.0.0.1
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}
docker run \
  -it \
  --rm \
  -e DISPLAY=host.docker.internal:0 \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v $(realpath ${DIR}/../..):/home/developer/src \
  -e CMAKE_GENERATOR=Ninja \
  -e CCACHE_DIR=/ccache \
  -v $HOME/.ccache:/ccache \
  imgs_dev:latest
