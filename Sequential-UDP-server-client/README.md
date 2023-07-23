# UDP server and client

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The directory consists of three programs: `client`, `server`, and `fancyclient`. 

The `client` reads lines of text from the keyboard and then sends them to the specified server. The program must be able to read multiple lines, one at a time, and send them to the server. 

`server` reads a string from the given port and sends it back to the client - over UDP.

`fancyclient` is a fancy version of a client that reads a string from the keyboard, sends it to the server, then reads the string from the server and prints it on the screen.


## Building the code

The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run.

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Sequential-UDP-server-client/
make
```

## Running the code

`./client IP_ADDRESS PORT_NUMBER`

`./server PORT_NUMBER`

`./fancyclient IP_ADDRESS PORT_NUMBER`

netcat (`nc`) can also be used to listen to a local port in order to validate the clients:

`nc -l -u PORT_NUMBER`
