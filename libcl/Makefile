# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/30 19:39:22 by olesgedz          #+#    #+#              #
#    Updated: 2019/08/30 21:12:03 by olesgedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME=libcl.a

CC=clang

CFLAGS= -g -Wall -Wextra -Werror

SDL_HEADERS = include/
LIBFT_HEADERS = ../libft/includes/
LIBVECT_HEADERS = ../libvect/include/
LIBGNL_HEADERS = ../libgnl/include/
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(LIBVECT_HEADERS) -I$(LIBGNL_HEADERS)
HEADERS_LIST =libcl.h 

DIRECTORY =  $(shell pwd)
HEADERS_DIRECTORY = include/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = srcs/

SOURCES_LIST= cl_init.c   cl_krl_build.c cl_krl_exec.c  cl_krl_init.c  cl_read.c cl_write.c


SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

CLEAR_LINE	:= \033[2K
BEGIN_LINE	:= \033[A
COL_END		:= \033[0m
COL_RED		:= \033[1;31m
COL_GREEN	:= \033[1;32m
COL_YELLOW	:= \033[1;33m
COL_BLUE	:= \033[1;34m
COL_VIOLET	:= \033[1;35m
COL_CYAN	:= \033[1;36m
COL_WHITE	:= \033[1;37m

PREC = echo -ne "\r [`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%]"

TOTAL_FILES := $(shell echo $(SOURCES_LIST) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(DIRECTORY)/objects/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Compiling file [$(COL_VIOLET)$<$(COL_GREEN)].($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)

nu:
	@echo -ne "\r [`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%]"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
