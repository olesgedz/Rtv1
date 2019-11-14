# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2019/11/14 19:06:12 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rt

FLAGS = -g #-Wall -Wextra -Werror
CC = clang
LIBRARIES = $(GUI_LIB) -lft -L$(LIBFT_DIRECTORY)  -lsdl -L$(LIBSDL_DIRECTORY)  -lm   -lvect -L$(LIBVECT) -lgnl -L$(LIBGNL) -lcl -L$(LIBCL)
INCLUDES = $(GUI_INC) -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)  -I$(SDL_HEADERS) -I$(LIBMATH_HEADERS) -I$(LIBSDL_HEADERS) -I$(LIBVECT)includes/ -Isrcs/cl_error/ -I$(LIBGNL)includes/ -I$(LIBCL)includes/

GUI_LIB = -L./gui/build/src -lKiWi #$(shell pkg-config --libs sdl2_ttf) $(shell pkg-config --libs sdl2_image) $(shell pkg-config --libs sdl2_mixer)
GUI_INC = -I./include/SDL2 -I./gui/KiWi/src -I./gui/inc #$(shell pkg-config --cflags sdl2_ttf) $(shell pkg-config --cflags sdl2_image) $(shell pkg-config --cflags sdl2_mixer)
DIR_KiWi = ./gui/build/src/
LIB_KiWi = $(DIR_KiWi)/libKiWi.dylib

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
HEADERS_LIST = rt.h
HEADERS = ./includes/rt.h ./gui/inc/gui.h

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

RMRF = gui/src/gui_main.o\
		gui/src/start_screen.o\
		gui/src/surf_tex.o\
		gui/src/scene_select.o\
		gui/src/main_screen.o\
		gui/src/obj_select.o\
		gui/src/ren_button.o\
		gui/src/gui_bar.o\
		gui/src/buttons.o\
		gui/src/add_obj.o\
		cJSON/cJSON.o

SRCS_LIST = main.c\
			cl_lib/gpu_init.c\
			textures.c\
			schwimmer_verwalten.c\
			cl_float3_rotate.c\
			keys.c\
			camera.c\
			const.c\
			hilfefunktionen.c\
			init_scene.c\
			render.c\
			mouse.c\
			../gui/src/gui_main.c\
			../gui/src/add_obj.c\
			../gui/src/buttons.c\
			../gui/src/gui_bar.c\
			../gui/src/start_screen.c\
			../gui/src/surf_tex.c\
			../gui/src/scene_select.c\
			../gui/src/main_screen.c\
			../gui/src/ren_button.c\
			../gui/src/obj_select.c\
			../cJSON/cJSON.c\
			neue_schlanke_analyse.c\
			analyse_dienstprogramme.c\
			util.c

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

ifeq ($(detected_OS),Linux)
	LIBRARIES += -lOpenCL
	GUI_LIB += $(shell pkg-config --libs SDL2_ttf) $(shell pkg-config --libs SDL2_image) $(shell pkg-config --libs SDL2_mixer)
	 GUI_INC += $(shell pkg-config --cflags SDL2_ttf) $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_mixer)
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBRARIES += -framework OpenCL
	GUI_LIB += $(shell pkg-config --libs sdl2_ttf) $(shell pkg-config --libs sdl2_image) $(shell pkg-config --libs sdl2_mixer)
  GUI_INC += $(shell pkg-config --cflags sdl2_ttf) $(shell pkg-config --cflags sdl2_image) $(shell pkg-config --cflags sdl2_mixer)
endif


.PHONY: clean fclean re

all: $(MAKES) $(NAME)


$(NAME): $(LIB_KiWi) $(LIBFT)  $(LIBSDL) $(LIBCL) $(LIBGNL)  $(LIBVECT) $(OBJS_DIRECTORY) $(OBJS) $(HEADERS)
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

$(LIB_KiWi):
	@cmake -S ./gui/KiWi -B ./gui/build
	@$(MAKE) -sC $(DIR_KiWi)

$(SDL_LIBS):
	cd SDL2; ./configure --prefix=$(DIRECTORY); make;
	$(MAKE) -sC $(SDL_MAKE) install

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(LIBSDL):
	@echo "$(NAME): $(GREEN)Creating $(LIBSDL)...$(RESET)"
	@$(MAKE) -sC $(LIBSDL_DIRECTORY)

norm:
	norminette gui/inc gui/src includes srcs libs/libcl libs/libft libs/libgnl libs/libsdl/includes libs/libsdl/srcs/ libs/libvect

clean:
	@rm -rf ./gui/build $(RMRF)
	$(MAKE) -sC $(LIBFT_DIRECTORY)	clean
	$(MAKE) -sC $(LIBSDL_DIRECTORY) clean
	$(MAKE) -sC $(LIBVECT)	clean
	$(MAKE) -sC $(LIBCL)	clean
	$(MAKE) -sC $(LIBGNL) 	clean
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
	@$(MAKE) -sC $(LIBVECT) fclean
	@$(MAKE) -sC $(LIBCL) fclean
	@$(MAKE) -sC $(LIBGNL) fclean
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
