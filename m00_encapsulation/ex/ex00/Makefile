CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SUPP_FILE = ignore_eh.supp

NAME = ex00

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -fr $(NAME)

re: fclean all

valgrind: all
	@if [ ! -f $(SUPP_FILE) ]; then \
		echo "Creating $(SUPP_FILE)..."; \
		echo "{" > $(SUPP_FILE); \
		echo "   ignore_libstdc++_emergency_buffer" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   fun:malloc" >> $(SUPP_FILE); \
		echo "   fun:_GLOBAL__sub_I_eh_alloc.cc" >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
	fi
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=$(SUPP_FILE) ./$(NAME)

.PHONY: all clean fclean re valgrind
