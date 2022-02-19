# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 11:09:35 by abeznik       #+#    #+#                  #
#    Updated: 2022/02/19 14:12:34 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

SOURCES		=	main.c \
				open_files.c \
				parse_input.c \
				get_cmd.c \
				build_path.c \
				pipex.c \

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
CFLAGS		=	-Wall -Werror -Wextra
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

0: re
	< infile ls | wc > outfile
	./pipex myinfile ls wc myoutfile

1: re
	< infile ls -l | wc -l > outfile
	./pipex myinfile "ls -l" "wc -l" myoutfile

2: re
	< infile ls | sed 's/infile/YES/g' > outfile
	./pipex myinfile ls "sed 's/infile/YES/g'" myoutfile

3: re
	< infile grep a1 | wc -w > outfile
	./pipex myinfile "grep a1" "wc -w" myoutfile

4: re
	< infile /bin/ls | wc -w > outfile
	./pipex myinfile "/bin/ls" "wc -w" myoutfile

5: re
	< infile /bin/ls -l | wc -w > outfile
	./pipex myinfile "/bin/ls -l" "wc -w" myoutfile

norm:
	norminette srcs/ utils/ includes/

git: fclean
	git add *
	git commit -m "Committed via make"
	git push origin master
	git push github master

del: fclean
	$(RM) *.out
	rm -rf *.dSYM

debug:
	gcc -g3 -o db.out $(SRCS) $(UTLS)
	# lldb db.out -- infile /bin/ls wc outfile
	lldb db.out -- infile /bin/ls "sed 's/infile/YES/g'" outfile
	
re: fclean all

.PHONY: fclean re all clean