# ************************************************************************** #
#                                                                            #
#   Makefile                                                                 #
#                                                                            #
#   By: elhmn <www.elhmn.com>                                                #
#             <nleme@live.fr>                                                #
#                                                                            #
#   Created: Wed Dec 11 16:02:52 2019                        by elhmn        #
#   Updated: Thu Jan 09 16:30:07 2020                        by bmbarga      #
#                                                                            #
# ************************************************************************** #

NAME = puzzled

LIBFT =	ft_lstnew.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstadd.c \
		ft_lstmap.c ft_lstadd_end.c ft_hash.c

LIBFTDIR = libft/

LIBFTS = $(addprefix $(LIBFTDIR), $(LIBFT))

SRC =	main.c puzzled.c test_puzzled.c getfile.c grid.c dict.c bruteforce.c \
		putfile.c

OBJ = $(SRC:.c=.o) $(LIBFT:.c=.o)

OBJDIR = ./objs/

SRCDIR = ./srcs/

SRCS = $(addprefix $(SRCDIR), $(SRC)) $(addprefix $(SRCDIR), $(LIBFTS))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

GEN = "./gen"

INC = -I ./includes/

CC = gcc

FLAGS = -Wall -Werror -Wextra


ifeq ($(DEBUG), 1)
DEBUG_FLAG = -g
endif

ifeq ($(SAN), 1)
SANITIZE = -fsanitize=address,undefined -ferror-limit=10
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

cleangen:
	rm -rf $(GEN)/*

fclean: clean
	rm $(NAME)

re:  fclean all
