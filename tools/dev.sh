#!/bin/bash

cd $(dirname "$(readlink -f "$BASH_SOURCE")")/..

[[ ! -z "${WITHIN_DEV}" ]] && echo "Already in the development environment!" && exit 1

cd docker
[[ "${1}" == "--build" ]] && docker-compose build
docker-compose run --rm dev
