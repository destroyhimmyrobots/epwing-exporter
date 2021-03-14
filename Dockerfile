FROM debian:buster-slim
RUN apt update && apt install -y clang cmake git xsltproc zlib1g-dev
WORKDIR /workspace
