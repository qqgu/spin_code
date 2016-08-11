FROM ubuntu:16.04
RUN apt-get update && \
    apt-get install -y gcc
COPY demo.c /bin/demo.c
RUN gcc /bin/demo.c -o sover
ENTRYPOINT ["/bin/sover"]
