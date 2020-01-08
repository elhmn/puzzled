# ************************************************************************** #
#                                                                            #
#   Makefile                                                                 #
#                                                                            #
#   By: elhmn <www.elhmn.com>                                                #
#             <nleme@live.fr>                                                #
#                                                                            #
#   Created: Wed Dec 11 16:02:52 2019                        by elhmn        #
#   Updated: Wed Jan 08 14:18:45 2020                        by bmbarga      #
#                                                                            #
# ************************************************************************** #

NAME = puzzled

SRC =	main.c puzzled.c test_puzzled.c getfile.c grid.c dict.c bruteforce.c

OBJ = $(SRC:.c=.o)

OBJDIR = ./objs/

SRCDIR = ./srcs/

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

INC = -I ./includes/

CC = gcc

FLAGS = -Wall -Werror -Wextra


ifeq ($(DEBUG), 1)
DEBUG_FLAG= -g
endif

ifeq ($(SAN), 1)
SANITIZE= -fsanitize=address,undefined -ferror-limit=10
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(SANITIZE) -o $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(DEBUG_FLAG) $(FLAGS) $(SANITIZE) $(INC) -c $(SRCS)
	mv $(OBJ) $(OBJDIR)

test: $(NAME)
	@./scripts/test_wrong.sh

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ)

fclean: clean
	rm $(NAME)

re:  fclean all
