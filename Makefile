CLIENT_SOURCES = mandatory/client.c

SERVER_SOURCES = mandatory/server.c mandatory/server_util.c

CLIENT_BONUS_SOURCES = bonus/client_bonus.c

SERVER_BONUS_SOURCES = bonus/server_bonus.c  bonus/server_bonus_util.c

OBJECTS = $(CLIENT_SOURCES:.c=.o) $(SERVER_SOURCES:.c=.o) $(CLIENT_BONUS_SOURCES:.c=.o) $(SERVER_BONUS_SOURCES:.c=.o)

LIBS = ./libs/libft.a ./libs/libftprintf.a

FLAGS = -Wall -Werror -Wextra

INCLUDES = ./headers/

CLIENT = client

SERVER = server

CLIENT_BONUS = client_bonus

SERVER_BONUS = server_bonus

$(CLIENT): $(CLIENT_SOURCES:.c=.o) $(SERVER)
	cc $(FLAGS) $(CLIENT_SOURCES:.c=.o) $(LIBS) -I $(INCLUDES) -o $(CLIENT) -g3

$(SERVER): $(SERVER_SOURCES:.c=.o)
	cc $(FLAGS) $(SERVER_SOURCES:.c=.o) $(LIBS) -I $(INCLUDES) -o $(SERVER) -g3

$(CLIENT_BONUS): $(CLIENT_BONUS_SOURCES:.c=.o) $(SERVER_BONUS)
	cc $(FLAGS) $(CLIENT_BONUS_SOURCES:.c=.o) $(LIBS) -I $(INCLUDES) -o $(CLIENT_BONUS) -g3

$(SERVER_BONUS): $(SERVER_BONUS_SOURCES:.c=.o)
	cc $(FLAGS) $(SERVER_BONUS_SOURCES:.c=.o) $(LIBS) -I $(INCLUDES) -o $(SERVER_BONUS) -g3

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@ -g3

all: $(CLIENT)

bonus: $(CLIENT_BONUS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re