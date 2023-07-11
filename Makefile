NAME = ircserver
CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = server.cpp create_socket.cpp client.cpp User.cpp commands.cpp join_cmd.cpp kick_cmd.cpp main1.cpp Channel.cpp
INCLUDE = server.hpp client.hpp User.hpp commands.hpp Channel.hpp
OBJECTS = $(SRC:.cpp=.o)

all: $(NAME)

ircserver :	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
%.o : %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf $(OBJECTS)
fclean:clean
	rm -rf $(NAME)

re: fclean all
