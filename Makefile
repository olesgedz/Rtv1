# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2019/12/02 21:33:26 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rt

FLAGS = -g #-Wall -Wextra -Werror
CC = clang
LIBRARIES = -lSDL2_image  -lSDL2_mixer  -lsdl -L$(LIBSDL_DIRECTORY)   -lcl -L$(LIBCL) -lgnl -L$(LIBGNL) -lvect -L$(LIBVECT) -lft -L$(LIBFT_DIRECTORY) -lm -lpthread
INCLUDES = $(GUI_INC) -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS)  -I$(SDL_HEADERS) -I$(LIBMATH_HEADERS) -I$(LIBSDL_HEADERS) -I$(LIBVECT)includes/ -Isrcs/cl_error/ -I$(LIBGNL)includes/ -I$(LIBCL)includes/ $(shell pkg-config --libs sdl2_ttf) $(shell pkg-config --libs sdl2_image) $(shell pkg-config --libs sdl2_mixer)
GUI_INC = -I./include/SDL2 -I./gui/KiWi/src -I./gui/build/src -I./gui/inc $(shell pkg-config --cflags sdl2_ttf) $(shell pkg-config --cflags sdl2_image) $(shell pkg-config --cflags sdl2_mixer)
#DIR_KiWi = ./gui/build/src/

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
		gui/src/change_obj.o\
		gui/src/smsht.o\
		gui/src/editboxes.o\
		gui/src/editboxes2.o\
		gui/src/parse_obj.o\
		gui/src/parse_box.o\
		gui/src/parse_box2.o\
		gui/src/create_obj.o\
		gui/src/push_new.o\
		gui/src/del_obj.o\
		gui/src/cameras.o\
		gui/src/change_cam.o\
		gui/src/cam_buttons.o\
		gui/src/cam_select.o\
		gui/src/cam_parser.o\
		gui/src/add_camera.o\
		gui/src/stereo.o\
		gui/src/eff.o\
		gui/src/add_tex.o\
		gui/KiWi/src/KW_button.o\
		gui/KiWi/src/KW_checkbox.o\
		gui/KiWi/src/KW_editbox.o\
		gui/KiWi/src/KW_editbox_internal.o\
		gui/KiWi/src/KW_eventwatcher.o\
		gui/KiWi/src/KW_frame.o\
		gui/KiWi/src/KW_frame_internal.o\
		gui/KiWi/src/KW_gui.o\
		gui/KiWi/src/KW_label.o\
		gui/KiWi/src/KW_label_internal.o\
		gui/KiWi/src/KW_rect.o\
		gui/KiWi/src/KW_renderdriver.o\
		gui/KiWi/src/KW_renderdriver_sdl2.o\
		gui/KiWi/src/KW_scrollbox.o\
		gui/KiWi/src/KW_scrollbox_internal.o\
		gui/KiWi/src/KW_tilerenderer.o\
		gui/KiWi/src/KW_toggle.o\
		gui/KiWi/src/KW_widget.o\
		gui/KiWi/src/KW_widget_eventhandlers.o\
		gui/KiWi/src/file2c.o\
		gui/build/src/resources.o\
		gui/KiWi/src/utf8.o\
		#gui/KiWi/*.o\
		cJSON/cJSON.o

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
			../gui/src/cam_select.c\
			../gui/src/change_obj.c\
			../gui/src/smsht.c\
			../gui/src/editboxes.c\
			../gui/src/editboxes2.c\
			../gui/src/parse_obj.c\
			../gui/src/parse_box.c\
			../gui/src/parse_box2.c\
			../gui/src/create_obj.c\
			../gui/src/push_new.c\
			../gui/src/del_obj.c\
			../gui/src/change_cam.c\
			../gui/src/cam_buttons.c\
			../gui/src/cam_parser.c\
			../gui/src/cameras.c\
			../gui/src/add_camera.c\
			../gui/src/eff.c\
			../gui/src/add_tex.c\
			../gui/src/stereo.c\
			../cJSON/cJSON.c\
			neue_schlanke_analyse.c\
			analyse_dienstprogramme.c\
			util.c\
			obj3d_parser.c\
			../gui/KiWi/src/KW_button.c\
			../gui/KiWi/src/KW_checkbox.c\
			../gui/KiWi/src/KW_editbox.c\
			../gui/KiWi/src/KW_editbox_internal.c\
			../gui/KiWi/src/KW_eventwatcher.c\
			../gui/KiWi/src/KW_frame.c\
			../gui/KiWi/src/KW_frame_internal.c\
			../gui/KiWi/src/KW_gui.c\
			../gui/KiWi/src/KW_label.c\
			../gui/KiWi/src/KW_label_internal.c\
			../gui/KiWi/src/KW_rect.c\
			../gui/KiWi/src/KW_renderdriver.c\
			../gui/KiWi/src/KW_renderdriver_sdl2.c\
			../gui/KiWi/src/KW_scrollbox.c\
			../gui/KiWi/src/KW_scrollbox_internal.c\
			../gui/KiWi/src/KW_tilerenderer.c\
			../gui/KiWi/src/KW_toggle.c\
			../gui/KiWi/src/KW_widget.c\
			../gui/KiWi/src/KW_widget_eventhandlers.c\
			../gui/KiWi/src/file2c.c\
			../gui/build/src/resources.c\
			../gui/KiWi/src/utf8.c

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
	LIBRARIES += -rpath ./gui/build/src/ -L./gui/build/src/ -lKiWi   -lOpenCL -lrt
	GUI_LIB +=    $(shell pkg-config --libs SDL2_image) $(shell pkg-config --libs SDL2_ttf) $(shell pkg-config --libs SDL2_mixer)
	 GUI_INC += $(shell pkg-config --cflags SDL2_ttf) $(shell pkg-config --cflags SDL2_image) $(shell pkg-config --cflags SDL2_mixer)
	LIB_KiWi = $(DIR_KiWi)/libKiWi.so
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBRARIES += -framework OpenCL
	GUI_LIB += $(shell pkg-config --libs sdl2_ttf) $(shell pkg-config --libs sdl2_image) $(shell pkg-config --libs sdl2_mixer)
  GUI_INC += $(shell pkg-config --cflags sdl2_ttf) $(shell pkg-config --cflags sdl2_image) $(shell pkg-config --cflags sdl2_mixer)
	LIB_KiWi = $(DIR_KiWi)/libKiWi.dylib
	GUI_LIB += -L./gui/build/src -lKiWi

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
