# ************************************************************************** #
#                                                                            #
#   Makefile                                                                 #
#                                                                            #
#   By: elhmn <www.elhmn.com>                                                #
#             <nleme@live.fr>                                                #
#                                                                            #
#   Created: Wed Dec 11 16:02:52 2019                        by elhmn        #
#   Updated: Sun Jan 12 17:47:03 2020                        by elhmn        #
#                                                                            #
# ************************************************************************** #

#########################
### puzzled 2019
### crossword generator
###
##

CORENAME = puzzled

LIBFT =	ft_lstnew.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstadd.c \
		ft_lstmap.c ft_lstadd_end.c ft_hash.c

LIBFTDIR = libft/

LIBFTS = $(addprefix $(LIBFTDIR), $(LIBFT))

SRC =	main.c puzzled.c test_puzzled.c getfile.c grid.c dict.c bruteforce.c \
		putfile.c wasm.c

OBJ = $(SRC:.c=.o) $(LIBFT:.c=.o)

OBJDIR = ./objs/

SRCDIR = ./srcs/

BUILDDIR = ./build/

SRCS = $(addprefix $(SRCDIR), $(SRC)) $(addprefix $(SRCDIR), $(LIBFTS))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

GEN = "./gen"

INC = -I ./includes/

FLAGS = -Wall -Werror -Wextra

ifeq ($(SAN), true)
SANITIZE = -fsanitize=address,undefined -ferror-limit=10
endif

ifeq ($(WASM), true) #compile for webassembly

ifeq ($(DEBUG), true)
DEBUGFLAGS = -g -s ONLY_MY_CODE=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0
endif


NAME = $(BUILDDIR)$(CORENAME).html
CC = emcc
WASMFLAGS= --emrun -s WASM=1 --preload-file ./tests/dicts/wasm.dict -s ALLOW_MEMORY_GROWTH=1
RUN = emrun --verbose --serve_after_exit --serve_after_close --port 8080 $(NAME)
CLEAN= $(BUILDDIR)$(CORENAME)*
MOVEBUILD= mv $(CORENAME)* $(BUILDDIR)

else 				#compile for unix

NAME = $(CORENAME)
CC = gcc
RUN = echo "only works with WASM=true"
CLEAN= $(NAME)

ifeq ($(DEBUG), true)
DEBUGFLAGS = -g -s ONLY_MY_CODE=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0
endif

ifeq ($(SAN), true)
SANITIZE = -fsanitize=address,undefined -ferror-limit=10
endif

endif

##detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)        # Mac OS X
INSTALLSDL= brew install sdl2; \
			brew install SDL2_image; \
			brew install SDL2_ttf
endif

##make: build your project
##	- make
##	- make WASM=true
## FLAGS:
##	- WASM=true for webassembly
##	- DEBUG=true for debugging
##	- SAN=true for sanitize build
##
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(DEBUGFLAGS) $(FLAGS) $(WASMFLAGS) $(SANITIZE) -o $(NAME) $(OBJS)
	-$(MOVEBUILD)

$(OBJS): $(SRCS)
	$(CC) $(DEBUGFLAGS) $(FLAGS) $(WASMFLAGS) $(SANITIZE) $(INC) -c $(SRCS)
	mv $(OBJ) $(OBJDIR)

##testwrong: test crossword tests
testwrong: $(NAME)
	@./scripts/test_wrong.sh

##testgen: test every generated crossword
testgen: $(NAME)
	@./scripts/test_gen.sh

##clean: cleans .o and project files
clean:
	-rm -rf $(OBJS)
	-rm -rf $(OBJ)

##cleangen: cleans generated crossword
cleangen:
	-rm -rf $(GEN)/*

##run: starts your project, only works with WASM=true flag
##	- make run WASM=true
run: $(NAME)
	$(RUN)

##fclean: cleans build binaries
fclean: clean
	-rm $(CLEAN)

##re: rebuild project
##	- make re
##	- make re WASM=true
re:  fclean all

##install-deps: install dependencies
install-deps:
	$(INSTALLSDL)

##help: show help
help : Makefile
	@sed -n 's/^##//p' $<

.PHONY : help all cleangen clean fclean
