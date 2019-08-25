# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/02 15:48:09 by bsouchet          #+#    #+#              #
#    Updated: 2019/08/05 01:55:21 by olesgedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

NAME		= libvect.a

FLAGS		= -Wall -Wextra -Werror -g

DIR_S		= sources

DIR_O		= temporary

HEADER		= include ../libft/includes

SOURCES		= vect_add.c \
	vect_cmp.c \
	vect_del.c \
	vect_grow.c \
	vect_init.c \
	vect_memcmp.c \
	vect_memmem.c \
	vect_mset.c \
	vect_mset_end.c \
	vect_new.c \
	vect_print.c \
	vect_push.c \
	vect_req.c \
	vect_str_add.c \
	vect_str_push.c \
	vect_wrap.c \

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
	norminette ../libvect/$(HEADER)
	@echo
	norminette ../libvect/$(DIR_S)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all -j 8
