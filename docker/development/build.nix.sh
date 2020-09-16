#!/bin/bash
set -x
set -e
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
uid=$(id -u)
gid=$(id -g)
echo "Using uid:gid $uid:$gid"
cd $DIR
docker build --build-arg USER=$uid --build-arg GROUP=$gid -t imgs_dev:latest .
