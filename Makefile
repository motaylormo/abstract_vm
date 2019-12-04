NAME	:= abstract_vm
CC		:= clang++
FLAGS	:= -std=c++11 -Wall -Wextra -Werror -Wno-deprecated-register -g

FILES	:= src/*.cpp \
			src/classes/*.cpp \
			lexer/lex.yy.cc
OBJ		:= $(FILES:.cpp=.o)
LEX		:= lexer/abstract_vm.lex

all		: $(NAME)

$(NAME)	:
	flex++ $(LEX)
	mv lex.yy.cc lexer/
	$(CC) $(FLAGS) $(FILES) -o $(NAME)


clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

.PHONY: all, clean, fclean, re