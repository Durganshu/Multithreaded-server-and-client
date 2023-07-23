# Distributed Systems with Networking (Tutorial 2a)

(The instructions for running the code are for Linux (particularly for Ubuntu 20.04 LTS)

The directory consists of two sub directories: `ex04-url` and `ex05-sockets`. 

The `ex04-url` directory consists of the implementations of test_url. This includes the implementation of parse_url() function and is the solution for the first part of tutorial. The Makefile can be used to build the program (compiling + linking). The Makefile contains all the target names and their dependencies as well as the commands to run. It contains targets for compiling each project together and apart. It can be used to clean and remove the generated executable and object files.

`ex05-sockets` consists of the implementation of 'wgetX'. It is based on the provided template code (including url.c/h) and makefile. **wgetX.c** has been modified as per the questions to generate the required output. makefile hasn't been changed and works perfectly to compile and link the associated binary. There's also a 'sample_weblinks.log' file which contains some sample weblinks that are active and can be used for downloading using our program


## Running the code

Get inside the directory (wherever it is placed) and build the target:
```shell
cd Tutorial_2a/ex05-sockets/
make
```

Run the executable:

`./wgetX <url>`

By default, the downloaded page would be saved in a file called `received_page`. In case, the user wants to name his own file, it can be done using this command:

`./wgetX <url> <file name>`

In order to delete the generated files and clean the project directory, run: `make clean`.
