# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: abeznik <abeznik@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/29 11:09:35 by abeznik       #+#    #+#                  #
#    Updated: 2022/03/28 12:32:00 by abeznik       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

SOURCES		=	build_path.c \
				main.c \
				parse_input.c \
				pipex.c \

SRC_DIR		=	srcs

UTILS		=	exit_message.c \
				free_split.c \
				ft_intlen.c \
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

subj: re # subject example
	< infile grep a1 | wc -w > outfile
	./pipex myinfile "grep a1" "wc -w" myoutfile
	make diff_out

0: re # cmd1 valid & cmd2 valid
	< infile ls | wc > outfile
	./pipex myinfile ls wc myoutfile
	make diff_out

1: re # cmd1 valid & cmd2 valid
	< infile ls -l | wc -l > outfile
	./pipex myinfile "ls -l" "wc -l" myoutfile
	make diff_out

2: re # cmd1 valid & cmd2 valid => potential leaks
	< infile ls | sed 's/infile/YES/g' > outfile
	./pipex myinfile ls "sed 's/infile/YES/g'" myoutfile
	make diff_out

3: re # cmd1 invalid param & cmd2 valid
	< infile grep a1 | wc -w > outfile
	./pipex myinfile "grep a1" "wc -w" myoutfile
	make diff_out

4: re # cmd1 valid & cmd2 valid
	< infile /bin/ls | wc -w > outfile
	./pipex myinfile "/bin/ls" "wc -w" myoutfile
	make diff_out

5: re # cmd1 valid & cmd2 valid
	< infile /bin/ls -l | wc -w > outfile
	./pipex myinfile "/bin/ls -l" "wc -w" myoutfile
	make diff_out

6: re # cmd1 arg invalid & cmd2 path invalid
	./pipex myinfile "grep codam" "/bin/wc -l" myoutfile

7: re # cmd1 valid & cmd2 valid
	< infile      ls |         wc   > outfile
	./pipex myinfile      "ls"          "wc"    myoutfile
	make diff_out

8: re # invalid infile
	< minfile ls | wc > outfile
	./pipex minfile ls wc myoutfile
	make diff_out

9: re # cmd1 valid & cmd2 path invalid
	< infile ls | /usr/wc > outfile
	# ./pipex myinfile ls /usr/wc myoutfile
	make diff_out

10: re # invalid outfile
	< infile ls | wc > utfile
	./pipex myinfile ls wc youtfile
	diff -y youtfile utfile

11: re # invalid relative path cmd1 - Test 22
	< infile ../../../../usr/bin/grep codam | wc -l > /tmp/file_out_bash
	./pipex infile "../../../../usr/bin/grep codam" "wc -l" /tmp/file_out
	make diff_bash

12: re # valid relative path cmd1 - Test 23
	< infile ../../../../../usr/bin/grep codam | wc -l > /tmp/file_out_bash
	./pipex infile "../../../../../usr/bin/grep codam" "wc -l" "/tmp/file_out"
	make diff_bash

13: re # invalid relative path cmd2 - Test 24
	./pipex infile "grep codam" "../../../../usr/bin/wc -l" "/tmp/file_out"
	< infile grep codam | ../../../../usr/bin/wc -l > /tmp/file_out_bash
	make diff_bash

14: re # valid relative path cmd2 - Test 25
	# < infile grep codam | ../../../../../usr/bin/wc -l > /tmp/file_out_bash
	./pipex infile "grep codam" "../../../../../usr/bin/wc -l" "/tmp/file_out"
	make diff_bash

15: re # invalid cmd2
	./pipex myinfile "grep codam" "/bin/wc -l" myoutfile
	< infile "grep codam" "/bin/wc -l" > outfile
	make diff_bash

16: re # empty cmd2
	./pipex infile "ls -la" "" "/tmp/file_out"
	# < infile ls -la | \"\" > /tmp/file_out_bash
	make diff_bash
	
tester: re
	./run_tests.sh

diff_out:
	diff -y myoutfile outfile

diff_bash:
	diff -y /tmp/file_out /tmp/file_out_bash

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
	# lldb db.out -- myinfile "grep codam" "/bin/wc -l" myoutfile
	lldb db.out -- myinfile ls /usr/wc myoutfile
	
re: fclean all

.PHONY: fclean re all clean