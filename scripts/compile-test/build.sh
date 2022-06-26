#!/bin/bash

set -e

cd $(dirname $0)/../../

docker build -t hotspot-build-ubuntu20.04 -f scripts/compile-test/Ubuntu20.04 .
docker build -t hotspot-build-ubuntu22.04 -f scripts/compile-test/Ubuntu22.04 .
docker build -t hotspot-build-fedora34 -f scripts/compile-test/Fedora34 .
docker build -t hotspot-build-archlinux -f scripts/compile-test/Archlinux .
docker build -t hotspot-build-opensuse-tumbleweed -f scripts/compile-test/OpenSuseTumbleweed .
