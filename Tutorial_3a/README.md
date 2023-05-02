# Distributed Systems with Networking (Tutorial 3a)

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The project directory consists of four programs: `mutex`, `client`, `server` and `pokingclient`. All the application are multi-threaded.

`mutex` program is the solution to first part of this Tutorial. It is a multi-threaded code that demosntrates the usage of 50 threads to increment a counter.

The `client` is a multi-threaded application that uses two threads: one to receive server's replies and anothe to read user messages (and send them as requests) simultaneously.

`server` reads a string from the port given, and sends it right back to the client - over UDP. Server has an upper bound ('MAX_CLIENTS') for the number of clients that can be simultaneously active. Requests received when there are 'MAX_CLIENTS' active requests are put on hold until the server can handle them (that is, until the number of active requests < 'MAX_CLIENTS'). Requests received when the number of active requests < 'MAX_CLIENTS' are processed normally.

`pokingclient` is a fancy version of client that is to be called using the script `multiple-run.sh`. `pokingclient` has a hard coded message and `multiple-run.sh` send a number of these requests simultaneously to the server. This helps in validating the multi-threaded nature of the server.

The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run. It contains targets for compiling each project together and apart. It can be used to clean and remove the generated executable and object files.

## Running the code

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Tutorial_3a/
make
```

Run the executable:

Mutex: 
```shell
./mutex
```
Multi-threaded UDP echo server and client:

```shell
shell1$ ./client IP_ADDRESS PORT_NUMBER`

shell2$ ./server PORT_NUMBER
```
For sending multiple requests to the server:

```shell
./multiple-run.sh ./pokingclient IP_ADDRESS PORT_NUMBER`
```

In order to delete the generated files and clean the project directory, run: `make clean`.
