# Distributed Systems with Networking (Tutorial 1a)

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS))

The directory consists of three header files, three source files and a Makefile.

## Source and Header files
The three header files and corresponding source files are: 
1. **hello-world.c/h**: Compiling, linking and executing the associated binary would print a "hello-world" on the console.

2. **international-hello-world.c/h**: Compiling, linking and executing the associated binary would print the "hello-world" in the language specified in the Makefile. The language can be one of FRENCH, ENGLISH, SPANISH, CHINESE and DANISH.

3. **fancy-hello-world.c/h**: Compiling, linking and executing the associated binary would print "Hello world, hello NAME" where NAME can be specified while running the executable.

## Makefile

The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run. The Makefile contains targets for compiling each project (hello-world, international-hello-world, fancy-hello-world), together and apart. It can be used to clean and remove the generated executable and object files.

## Running the code

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Tutorial_1a
make
```

Run the desired executable:

`./hello-world` or `./international-hello-world` or `./fancy-hello-world`

In order to delete the generated files and clean the project directory, run: `make clean`.
