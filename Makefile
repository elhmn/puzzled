# ************************************************************************** #
#                                                                            #
#   Makefile                                                                 #
#                                                                            #
#   By: elhmn <www.elhmn.com>                                                #
#             <nleme@live.fr>                                                #
#                                                                            #
#   Created: Wed Dec 11 16:02:52 2019                        by elhmn        #
#   Updated: Tue Dec 17 10:51:57 2019                        by bmbarga      #
#                                                                            #
# ************************************************************************** #

NAME = puzzled

SRC =	main.c puzzled.c test_puzzled.c getfile.c

OBJ = $(SRC:.c=.o)

OBJDIR = ./objs/

SRCDIR = ./srcs/

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

INC = -I ./includes/

CC = gcc

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(FLAGS) $(INC) -c $(SRCS)
	mv $(OBJ) $(OBJDIR)

test: $(NAME)
	for f in $$(ls -1 ./tests | grep wrong); do echo ./tests/$$f; ./puzzled -t ./tests/$$f; echo ""; done;

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ)

fclean: clean
	rm $(NAME)

re:  fclean all
