# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/02 15:48:09 by bsouchet          #+#    #+#              #
#    Updated: 2019/08/30 19:31:59 by olesgedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

NAME		= libgnl.a

FLAGS		= -Wall -Wextra -Werror -g

DIR_S		= sources

DIR_O		= temporary

HEADER		= include ../libft/includes ../libvect/include

SOURCES		= gnl_vect.c \
	gnl_lines.c \

SUB_FOLDERS	=

SRCS		= $(addprefix $(DIR_S)/,$(SOURCES))

OBJS		= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

opti:
	@$(MAKE) all -j 8

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@[ -d $(DIR_O) ] || mkdir -p $(DIR_O)
	@$(CC) $(FLAGS) $(addprefix -I, $(HEADER)) -o $@ -c $<

norme:
	norminette ../libgnl/$(HEADER)
	@echo
	norminette ../libgnl/$(DIR_S)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all -j 8
