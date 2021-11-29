# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 11:09:35 by abeznik       #+#    #+#                  #
#    Updated: 2021/11/29 11:14:35 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

SOURCES		=	main.c \

SRC_DIR		=	srcs

OBJ_DIR		=	obj

HEADER		=	includes

SRCS 		=	$(addprefix $(SRC_DIR)/,$(SOURCES))
OBJ_S 		=	$(patsubst %, $(OBJ_DIR)/srcs/%, $(SOURCES:.c=.o))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -f

all:			$(NAME)

$(NAME):		$(OBJ_S)
	$(CC) $(OBJ_S) -o $(NAME)

$(OBJ_DIR)/srcs/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj/srcs
	$(CC) -c $(CFLAGS) -I $(HEADER) -o $@ $<

fclean: clean
	$(RM) $(NAME)

del: fclean
	$(RM) *.out
	rm -rf *.dSYM

debug:
	gcc -g3 -o db.out $(SRCS)
	lldb db.out
	
re: fclean all

.PHONY: fclean re all clean