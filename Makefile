NAME = ircserver
CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = server.cpp create_socket.cpp
INCLUDE = server.hpp
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