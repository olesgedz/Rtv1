
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2019/11/29 21:06:38 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rt

FLAGS = -g #-Wall -Wextra -Werror
CC = clang
LIBRARIES =  $(GUI_LIB) -lSDL2_image  -lSDL2_mixer  -lsdl -L$(LIBSDL_DIRECTORY)   -lcl -L$(LIBCL_DIR) -lgnl -L$(LIBGNL_DIR) -lvect -L$(LIBVECT_DIR) -lft -L$(LIBFT_DIRECTORY) -lm -lpthread -ljson -L$(cJSON_DIRECTORY)
INCLUDES = $(GUI_INC) -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)  -I$(SDL_HEADERS) -I$(LIBMATH_HEADERS) -I$(LIBSDL_HEADERS) -I$(LIBVECT_DIR)includes/ -Isrcs/cl_error/ -I$(LIBGNL_DIR)includes/ -I$(LIBCL_DIR)includes/ -I$(cJSON_DIRECTORY)


GUI_INC = -I./include/SDL2 -I./gui/KiWi/src
DIR_KiWi = ./gui/build/src

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

cJSON = $(cJSON_DIRECTORY)libjson.a

LIBMATH = $(LIBMATH_DIRECTORY)libmath.a
LIBMATH_DIRECTORY = ./libmath/
LIBMATH_HEADERS = $(LIBMATH_DIRECTORY)includes/

LIBFT_DIRECTORY = libs/libft/
LIBVECT_DIR = libs/libvect/
LIBCL_DIR	= libs/libcl/
LIBGNL_DIR	= libs/libgnl/
LIBVECT = $(LIBVECT_DIR)/libvect.a
LIBCL = $(LIBCL_DIR)/libcl.a
LIBGNL = $(LIBGNL_DIR)/libgnl.a

LIBSDL_DIRECTORY = libs/libsdl/
cJSON_DIRECTORY = cJSON/


SDL_HEADERS = include/
LIBSDL = $(LIBSDL_DIRECTORY)libsdl.a
LIBSDL_HEADERS = $(LIBSDL_DIRECTORY)includes/

HEADERS_DIRECTORY = ./includes/
HEADERS_LIST = rt.h
HEADERS = ./includes/rt.h ./includes/gui.h

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

SRCS_LIST = main.c \
			cl_lib/gpu_init.c\
			textures.c\
			schwimmer_verwalten.c\
			cl_float3_rotate.c\
			keys.c\
			camera.c\
			const.c\
			hilfefunktionen.c\
			init_scene.c\
			help_fun.c\
			render.c\
			mouse.c\
			net/net_gui.c\
			net/net_connect.c\
			net/net_srv.c\
			net/net_string.c\
			gui/gui_main.c\
			gui/add_obj.c\
			gui/buttons.c\
			gui/gui_bar.c\
			gui/start_screen.c\
			gui/surf_tex.c\
			gui/scene_select.c\
			gui/main_screen.c\
			gui/ren_button.c\
			gui/obj_select.c\
			gui/cam_select.c\
			gui/change_obj.c\
			gui/smsht.c\
			gui/editboxes.c\
			gui/editboxes2.c\
			gui/parse_obj.c\
			gui/parse_box.c\
			gui/parse_box2.c\
			gui/create_obj.c\
			gui/push_new.c\
			gui/del_obj.c\
			gui/change_cam.c\
			gui/cam_buttons.c\
			gui/cam_parser.c\
			gui/cameras.c\
			gui/add_camera.c\
			gui/eff.c\
			gui/gui_mod_butt.c\
			gui/add_tex.c\
			gui/stereo.c\
			gui/tor_hyper.c\
			gui/basis.c\
			gui/pars_tor_hyper.c\
			gui/dumper_butt.c\
			gui/dumper_parts.c\
			gui/dumper_parts2.c\
			../cJSON/cJSON.c\
			neue_schlanke_analyse.c\
			analyse_dienstprogramme.c\
			util.c\
			parse/obj3d_parser.c\
			parse/read_scene.c\
			parse/check_scene.c\
			parse/check_cam.c\
			parse/check_object.c\
			parse/parse_triangle.c\
			parse/parse_rest.c\
			parse/parse_basis.c\
			parse/parse_facing.c\
			parse/parse_necessary.c


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
	LIBRARIES += -rpath ./gui/build/ -L./gui/build/ -lKiWi   -lOpenCL -lrt
	GUI_LIB +=    $(shell pkg-config --libs SDL2_image) $(shell pkg-config --libs SDL2_ttf) $(shell pkg-config --libs SDL2_mixer) $(shell pkg-config --libs SDL2_net)
	 GUI_INC += $(shell pkg-config --cflags SDL2_ttf) $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_mixer) $(shell pkg-config --cflags SDL2_net)
	LIB_KiWi = $(DIR_KiWi)/libKiWi.so
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBRARIES += -framework OpenCL
	GUI_LIB += $(shell pkg-config --libs sdl2_ttf) $(shell pkg-config --libs sdl2_image) $(shell pkg-config --libs sdl2_mixer) $(shell pkg-config --libs sdl2_net)
  GUI_INC += $(shell pkg-config --cflags sdl2_ttf) $(shell pkg-config --cflags sdl2_image) $(shell pkg-config --cflags sdl2_mixer) $(shell pkg-config --cflags sdl2_net)
	LIB_KiWi = $(DIR_KiWi)/libKiWi.dylib
	GUI_LIB += -L./gui/build/src -lKiWi

endif


.PHONY: clean fclean re

all: $(MAKES) $(NAME)


$(NAME): $(LIB_KiWi) $(LIBFT) $(cJSON)  $(LIBSDL) $(LIBCL_DIR) $(LIBGNL_DIR)  $(LIBVECT_DIR) $(OBJS_DIRECTORY) $(OBJS) $(HEADERS)
	@$(CC) $(FLAGS) $(LIBSDL) $(INCLUDES) $(OBJS) $(SDL_CFLAGS) $(SDL_LDFLAGS) -o $(NAME) $(LIBRARIES)
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_END)"

$(MAKES):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
	@$(MAKE) -sC $(LIBSDL_DIRECTORY)
	@$(MAKE) -sC $(LIBVECT_DIR)
	@$(MAKE) -sC $(LIBGNL_DIR)
	@$(MAKE) -sC $(LIBCL_DIR)
	@$(MAKE) -sC $(cJSON_DIRECTORY)

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
	norminette gui/inc gui includes srcs libs/libcl libs/libft libs/libgnl libs/libsdl/includes libs/libsdl/srcs/ libs/libvect

clean:
	@rm -rf ./gui/build
	$(MAKE) -sC $(LIBFT_DIRECTORY)	clean
	$(MAKE) -sC $(LIBSDL_DIRECTORY) clean
	$(MAKE) -sC $(LIBVECT_DIR)	clean
	$(MAKE) -sC $(LIBCL_DIR)	clean
	$(MAKE) -sC $(LIBGNL_DIR) 	clean
	$(MAKE) -sC $(cJSON_DIRECTORY)	clean
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
	@$(MAKE) -sC $(LIBVECT_DIR) fclean
	@$(MAKE) -sC $(LIBCL_DIR) fclean
	@$(MAKE) -sC $(LIBGNL_DIR) fclean
	@$(MAKE) -sC $(cJSON_DIRECTORY) fclean
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
