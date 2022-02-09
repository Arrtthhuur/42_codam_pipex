# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 11:09:35 by abeznik       #+#    #+#                  #
#    Updated: 2022/02/09 14:36:27 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

SOURCES		=	main.c \
				open_files.c \

SRC_DIR		=	srcs

UTILS		=	exit_message.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strjoin.c \
				ft_split.c \
				ft_substr.c \
				ft_strdup.c \
				ft_memcpy.c \

UTL_DIR		=	utils

OBJ_DIR		=	obj

HEADER		=	includes

SRCS 		=	$(addprefix $(SRC_DIR)/,$(SOURCES))
OBJ_S 		=	$(patsubst %, $(OBJ_DIR)/srcs/%, $(SOURCES:.c=.o))

UTLS		=	$(addprefix $(UTL_DIR)/,$(UTILS))
OBJ_U 		=	$(patsubst %, $(OBJ_DIR)/utils/%, $(UTILS:.c=.o))

CC			=	gcc
# CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -f

all:			$(NAME)

$(NAME):		$(OBJ_S) $(OBJ_U)
	$(CC) $(OBJ_S) $(OBJ_U) -o $(NAME)

$(OBJ_DIR)/srcs/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj/srcs
	$(CC) -c $(CFLAGS) -I $(HEADER) -o $@ $<

$(OBJ_DIR)/utils/%.o: $(UTL_DIR)/%.c
	@mkdir -p obj/utils
	$(CC) -c $(CFLAGS) -I $(HEADER) -o $@ $<

clean:
	$(RM) $(OBJ_S) $(OBJ_U)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

norm:
	norminette srcs/ utils/ includes/

del: fclean
	$(RM) *.out
	rm -rf *.dSYM

debug:
	gcc -g3 -o db.out $(SRCS) $(UTLS)
	lldb db.out
	
re: fclean all

.PHONY: fclean re all clean