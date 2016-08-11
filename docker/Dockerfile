FROM ubuntu:16.04
RUN apt-get update && \
    apt-get install -y gcc
COPY demo.c /bin/demo.c
WORKDIR /bin
RUN gcc /bin/demo.c -o solver
RUN chmod 755 /bin/solver
ENTRYPOINT ["/bin/solver"]
