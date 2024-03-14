#######################################################
# GENERAL                                             #
#######################################################
CC = cc

CFLAGS = -Wall -Werror -Wextra

#######################################################
# SERVER                                              #
#######################################################
SERVER = server

SRV_SRC = server.c minitalk_utils.c

SRV_OBJ = $(SRV_SRC:.c=.o)

$(SERVER) : $(SRV_OBJ)
	$(CC) $(CFLAGS) $(SRV_OBJ) -o $(SERVER)

#######################################################
# CLIENT                                              #
#######################################################
CLIENT = client

CLT_SRC = client.c minitalk_utils.c

CLT_OBJ = $(CLT_SRC:.c=.o)

$(CLIENT) : $(CLT_OBJ)
	$(CC) $(CFLAGS) $(CLT_OBJ) -o $(CLIENT)

#######################################################
# OPS	                                              #
#######################################################
all : $(CLIENT) $(SERVER)

clean:
	rm -f $(CLT_OBJ) $(SRV_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all