NAME	=	PmergeMe

CC	=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC	=	main.cpp PmergeMe.cpp

HEADER	=	PmergeMe.hpp

OBJ_DIR	=	objs
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST	=	`shuf -i 0-10000 -n 3000 | xargs`

all:	$(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f leaks.txt

fclean:	clean
	rm -f $(NAME)

re: fclean all

leaks: all
	valgrind --leak-check=full --log-file="leaks.txt" ./$(NAME) $(TEST)
