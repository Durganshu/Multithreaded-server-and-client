# Distributed Systems with Networking (Tutorial 2b)

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The directory consists of three programs: `client`, `server` and `fancyclient`. 

The `client` reads lines of text from the keyboard, and then sends them to the specified server. The program must be able to read multiple lines, one at a time, and send them to the server. 

`server` reads a string from the port given, and sends it right back to the client - over UDP.

`fancyclient` is a fancy version of client that reads a string from the keyboard, sends it to the server, then reads the string from the server and prints it on the screen.

The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run. It contains targets for compiling each project together and apart. It can be used to clean and remove the generated executable and object files.

## Running the code

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Tutorial_2b/
make
```

Run the executable:

`./client IP_ADDRESS PORT_NUMBER`

`./server PORT_NUMBER`

`./fancyclient IP_ADDRESS PORT_NUMBER`

`nc` can be used to listen a local port in order to validate the clients.


In order to delete the generated files and clean the project directory, run: `make clean`.
