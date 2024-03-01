SERVER = server

CLIENT = client

CLT_SRC = client.c

CLT_OBJ = $(CLT_SRC:.c=.o)

SRV_SRC = server.c

SRV_OBJ = $(SRV_SRC:.c=.o)

$(SERVER) : $(SRV_OBJ)
	cc $(SRV_OBJ) -o $(SERVER)

$(CLIENT) : $(CLT_OBJ)
	cc $(CLT_OBJ) -o $(CLIENT)

clean:
	rm -f $(CLT_OBJ) $(SRV_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all