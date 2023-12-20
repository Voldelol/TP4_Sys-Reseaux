# makefile
#################################################################
SRC = main.c
module = client
Warning = -Wall -Wextra
SRCs = main.c client_fcts.c
CC = gcc
LIB=-lseg -L.

client make :
	$(CC) $(SRCs) -o $(module) $(Warning)

lib :
	$(CC) $(SRC) -o $(module) $(Warning) $(LIB)
clean:
	rm -f $(module)
