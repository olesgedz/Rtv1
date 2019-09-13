# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2019/09/13 22:55:23 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rtv1

FLAGS = -g
CC = gcc
LIBRARIES = $(GUI_LIB) -lft -L$(LIBFT_DIRECTORY)  -lsdl -L$(LIBSDL_DIRECTORY)  -lm -framework OpenCL  -lvect -L$(LIBVECT) -lgnl -L$(LIBGNL) -lcl -L$(LIBCL)
INCLUDES = $(GUI_INC) -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)  -I$(SDL_HEADERS) -I$(LIBMATH_HEADERS) -I$(LIBSDL_HEADERS) -I$(LIBVECT)include/ -Isrcs/cl_error/ -I$(LIBGNL)include/ -I$(LIBCL)include/

GUI_LIB = -L./gui/build/src -lKiWi -L/Users/lminta/.brew/Cellar/sdl2_ttf/2.0.15/lib -lSDL2_ttf
GUI_INC = -I./include/SDL2 -I./gui/KiWi/src -I./gui/inc -I/Users/lminta/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

LIBMATH = $(LIBMATH_DIRECTORY)libmath.a
LIBMATH_DIRECTORY = ./libmath/
LIBMATH_HEADERS = $(LIBMATH_DIRECTORY)includes/

LIBFT_DIRECTORY = libs/libft/
LIBVECT = libs/libvect/
LIBCL	= libs/libcl/
LIBGNL	= libs/libgnl/
LIBSDL_DIRECTORY = libs/libsdl/


SDL_HEADERS = include/

LIBSDL = $(LIBSDL_DIRECTORY)libsdl.a
LIBSDL_HEADERS = $(LIBSDL_DIRECTORY)includes/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = rtv1.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

DIRECTORY =  $(shell pwd)
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)
SDL_DIRECTORY = $(DIRECTORY)/lib
SDL_MAKE = $(DIRECTORY)/SDL2

LIB_LIST =	libSDL2.a\
			libSDL2.la\
			libSDL2_test.la\
			libSDL2main.la\
			libSDL2-2.0.0.dylib\
			libSDL2.dylib\
			libSDL2_test.a\
			libSDL2main.a

SRCS_DIRECTORY = ./srcs/

SRCS_LIST = main.c\
			cl_lib/gpu_init.c\
			textures.c\
			add_object.c parse.c\
			cl_float3_manage.c\
			../gui/src/gui_main.c\
			../gui/src/start_screen.c

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
SDL_LIBS = $(addprefix $(DIRECTORY)/lib/, $(LIB_LIST))
MAKES = makes

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
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

TOTAL_FILES := $(shell echo $(SRCS_LIST) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(DIRECTORY)/objects/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')



ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname)
endif

ifeq ($(detected_OS),Windows)
	CFLAGS += -D WIN32
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	CFLAGS += -D OSX
endif


.PHONY: clean fclean re

all: $(MAKES) $(NAME)


$(NAME): $(LIBFT)  $(LIBSDL) $(LIBCL) $(LIBGNL)  $(LIBVECT) $(OBJS_DIRECTORY) $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBSDL) $(INCLUDES) $(OBJS) $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $(NAME) $(LIBRARIES)
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(MAKES):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
	@$(MAKE) -sC $(LIBSDL_DIRECTORY)
	@$(MAKE) -sC $(LIBVECT)
	@$(MAKE) -sC $(LIBGNL)
	@$(MAKE) -sC $(LIBCL)


$(OBJS_DIRECTORY):
	@mkdir -p $(OBJS_DIRECTORY)


$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Compiling file [$(COL_VIOLET)$<$(COL_GREEN)].($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

count:
	@echo $(TOTAL_FILES)
	@echo $(CURRENT_FILES)

depend:
						makedepend --$(SRCS_DIRECTORY)/$(SRCS_LIST);

sdl:
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

this:
	@rm -rf $(OBJS_DIRECTORY) && make;

$(SDL_LIBS):
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(SDL_MAKE) install

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(LIBSDL):
	@echo "$(NAME): $(GREEN)Creating $(LIBSDL)...$(RESET)"
	@$(MAKE) -sC $(LIBSDL_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(LIBSDL_DIRECTORY) clean
	@rm -rf $(OBJS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"
	#@$(MAKE) -sC $(SDL_MAKE) clean
	@echo "$(SDL_MAKE): $(RED)object files were deleted$(RESET)"

dd:
	rm $(NAME)

lib:
	 @$(MAKE) -sC $(LIBSDL_DIRECTORY) re

fclean: clean
	@rm -r $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@$(MAKE) -sC $(LIBSDL_DIRECTORY) fclean
	#@rm -f $(DIRECTORY)/bin/sdl2-config
	#@rm -f $(DIRECTORY)/lib/libSDL2.la
	#@rm -f $(DIRECTORY)/lib/libSDL2main.la
	#@rm -f $(DIRECTORY)/lib/libSDL2_test.la
	#@rm -f $(DIRECTORY)/share/aclocal/sdl2.m4
	#@rm -f $(DIRECTORY)/lib/pkgconfig/sdl2.pc
	#@rm -f $(DIRECTORY)/lib/cmake/SDL2/sdl2-config.cmake
	#@rm -rf lib bin share
	#@echo "$(SDL_MAKE): $(RED)was unistalled$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
# DO NOT DELETE
