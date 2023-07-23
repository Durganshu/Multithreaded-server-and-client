Multithreaded UDP Server and Client

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The `client` is a multi-threaded application that uses two threads: one to receive the server's replies and another to simultaneously read user messages (and send them as requests).

`server` reads a string from the given port and sends it back to the client - over UDP. The server has an upper bound ('MAX_CLIENTS') for the number of clients that can be simultaneously active. Requests received when there are 'MAX_CLIENTS' active requests are put on hold until the server can handle them (that is, until the number of active requests < 'MAX_CLIENTS'). Requests received when the number of active requests < 'MAX_CLIENTS' are processed normally.

`pokingclient` is a fancy version of the client that is to be called using the script `multiple-run.sh`. `pokingclient` has a hard-coded message, and `multiple-run.sh` send a number of these requests simultaneously to the server. This helps in validating the multi-threaded nature of the server.

## Building the code

The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names, their dependencies, and the commands to run. It can also clean and remove the generated executable and object files.

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Multithreaded-UDP-server-client/
make
```

## Running the code

Multi-threaded UDP echo server and client:

```shell
shell1$ ./client IP_ADDRESS PORT_NUMBER`
shell2$ ./server PORT_NUMBER
```
For sending multiple requests to the server:

```shell
shell1$ ./client IP_ADDRESS PORT_NUMBER`
shell2$ ./multiple-run.sh ./pokingclient IP_ADDRESS PORT_NUMBER`
```
