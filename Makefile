# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 11:09:35 by abeznik       #+#    #+#                  #
#    Updated: 2022/03/21 15:45:13 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

SOURCES		=	build_path.c \
				get_cmd.c \
				main.c \
				open_files.c \
				parse_input.c \
				pipex.c \

SRC_DIR		=	srcs

UTILS		=	exit_message.c \
				free_split.c \
				ft_memcpy.c \
				ft_split.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_substr.c \
				wrapper.c \

UTL_DIR		=	utils

OBJ_DIR		=	obj

HEADER		=	includes

SRCS 		=	$(addprefix $(SRC_DIR)/,$(SOURCES))
OBJ_S 		=	$(patsubst %, $(OBJ_DIR)/srcs/%, $(SOURCES:.c=.o))

UTLS		=	$(addprefix $(UTL_DIR)/,$(UTILS))
OBJ_U 		=	$(patsubst %, $(OBJ_DIR)/utils/%, $(UTILS:.c=.o))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g
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

0: re # cmd1 valid & cmd2 valid
	< infile ls | wc > outfile
	./pipex myinfile ls wc myoutfile

1: re # cmd1 valid & cmd2 valid
	< infile ls -l | wc -l > outfile
	./pipex myinfile "ls -l" "wc -l" myoutfile

2: re # cmd1 valid & cmd2 valid => potential leaks
	< infile ls | sed 's/infile/YES/g' > outfile
	./pipex myinfile ls "sed 's/infile/YES/g'" myoutfile

3: re # cmd1 invalid param & cmd2 valid
	< infile grep a1 | wc -w > outfile
	./pipex myinfile "grep a1" "wc -w" myoutfile

4: re # cmd1 valid & cmd2 valid
	< infile /bin/ls | wc -w > outfile
	./pipex myinfile "/bin/ls" "wc -w" myoutfile

5: re # cmd1 valid & cmd2 valid
	< infile /bin/ls -l | wc -w > outfile
	./pipex myinfile "/bin/ls -l" "wc -w" myoutfile

6: re # cmd1 arg invalid & cmd2 path invalid
	< infile grep codam | /bin/wc -l > outfile
	./pipex myinfile "grep codam" "/bin/wc -l" myoutfile

7: re # cmd1 valid & cmd2 valid
	< infile      ls |         wc   > outfile
	./pipex myinfile      "ls"          "wc"    myoutfile

8: re # invalid infile
	< minfile ls | wc > outfile
	./pipex minfile ls wc myoutfile

9: re # cmd1 valid & cmd2 path invalid
	< infile ls | /usr/wc > outfile
	./pipex myinfile ls /usr/wc myoutfile

10: re # invalid outfile
	< infile ls | wc > utfile
	./pipex myinfile ls wc youtfile

11: re # invalid relative path cmd1
	./pipex file_in "../../../../usr/bin/grep codam" "wc -l" /tmp/file_out
	cat /tmp/file_out
	< file_in ../../../../usr/bin/grep codam | wc -l > /tmp/file_out_bash
	cat /tmp/bash_test

12: re # valid relative path cmd1
	./pipex file_in "../../../../../usr/bin/grep codam" "wc -l" "/tmp/file_out"
	cat /tmp/file_out
	< file_in ../../../../../usr/bin/grep codam | wc -l > /tmp/file_out_bash
	cat /tmp/file_out_bash

13: re # invalid relative path cmd2
	./pipex file_in "grep codam" "../../../../usr/bin/wc -l" "/tmp/file_out"
	cat /tmp/file_out
	# < file_in grep codam | ../../../../usr/bin/wc -l > /tmp/file_out_bash
	# cat /tmp/file_out_bash

norm:
	norminette srcs/ utils/ includes/

git: del
	git add *
	git commit -m "Quick commit via make"
	git push origin master
	git push github master

del: fclean
	$(RM) *.out
	rm -rf *.dSYM

debug:
	gcc -g3 -o db.out $(SRCS) $(UTLS)
	# lldb db.out -- infile /bin/ls wc outfile
	# lldb db.out -- infile /bin/ls "sed 's/infile/YES/g'" outfile
	lldb db.out -- myinfile "grep codam" "/bin/wc -l" myoutfile
	
re: fclean all

.PHONY: fclean re all clean