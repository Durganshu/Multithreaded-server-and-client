# Distributed Systems with Networking (Tutorial 1b)

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The directory consists of two sub directories: `Practice` and `ex02-pointer-server`. 

The `Practice` directory consists of the implementations of linked lists and double linked lists. This was just implemented for practicing the implementation of pointers and references. The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run. The Makefile contains targets for compiling each project together and apart. It can be used to clean and remove the generated executable and object files.

`ex02-pointer-server` consists of the actual assignment. It consists of already shared idserver.c, idserver.h, pointer.c and makefile. **pointer.c** and **idserver.c** have been modified as per the questions to generate the required output. makefile hasn't been changed and works perfectly to compile and link the the associated binary.


## Running the code

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Tutorial_1b/ex02-pointer-server/
make
```

Run the executable:

`./pointer`

In order to delete the generated files and clean the project directory, run: `make clean`.
