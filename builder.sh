#!/bin/sh
set -eu
docker build -t epwing-exporter .
docker run --rm -it -v "$PWD:/workspace" epwing-exporter
