NAME=libsdl.a

CC=clang

CFLAGS= -g -Wall -Wextra -Werror

SDL_HEADERS = include/
LIBFT_HEADERS = ../libft/includes/
LIBMATH_HEADERS = ../libmath/includes/
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(SDL_HEADERS) -I$(LIBFT_HEADERS) -I$(LIBMATH_HEADERS)
HEADERS_LIST =libsdl.h

DIRECTORY =  $(shell pwd)
HEADERS_DIRECTORY = includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = srcs/

SOURCES_LIST=ft_plot_line.c\
			ft_put_pixel.c\
			ft_init_window.c\
			ft_exit.c\
			ft_input.c\
			ft_surface_present.c\
			ft_surface_clear.c\
			ft_surface_create.c\
			ft_surface_combine.c\
			ft_get_light.c\
			ft_percent.c\
			ft_get_color.c\
			ft_hex_to_rgb.c\
			ft_texture_lock.c\
			ft_texture_present.c\
			ft_texture_create.c\
			ft_rgb_to_hex.c

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
