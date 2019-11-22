NAME=libft.a

CC = clang

CFLAGS=  -g3 -Wall -Wextra -Werror

INCLUDES = -I$(HEADERS_DIRECTORY)
HEADERS_LIST =libft.h

DIRECTORY =  $(shell pwd)
HEADERS_DIRECTORY = includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_DIRECTORY = sources/

SOURCES_LIST= mem/ft_memset.c mem/ft_bzero.c mem/ft_memcpy.c mem/ft_memccpy.c \
mem/ft_memmove.c mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memalloc.c \
mem/ft_memdel.c mem/ft_malloc_err.c mem/ft_mempcpy.c\
str/ft_strlen.c str/ft_strdup.c str/ft_strcpy.c str/ft_strncpy.c str/ft_strcat.c str/ft_strncat.c \
str/ft_strlcat.c str/ft_strchr.c str/ft_strrchr.c str/ft_strstr.c str/ft_strnstr.c \
str/ft_strcmp.c str/ft_strncmp.c standart/ft_atoi.c \
standart/ft_isalpha.c standart/ft_isdigit.c standart/ft_isalnum.c standart/ft_isascii.c standart/ft_isprint.c \
standart/ft_toupper.c standart/ft_tolower.c \
str/ft_strnew.c str/ft_strdel.c str/ft_strclr.c str/ft_striter.c str/ft_striteri.c \
str/ft_strmap.c str/ft_strmapi.c str/ft_strequ.c str/ft_strnequ.c str/ft_strsub.c str/ft_strjoin.c \
str/ft_strtrim.c str/ft_strsplit.c  str/ft_nsplit.c str/ft_word.c\
standart/ft_itoa.c \
standart/ft_putchar.c standart/ft_putstr.c standart/ft_putendl.c standart/ft_putnbr.c standart/ft_putchar_fd.c \
standart/ft_putstr_fd.c standart/ft_putendl_fd.c standart/ft_putnbr_fd.c standart/ft_terminate.c \
lst/ft_lstadd.c lst/ft_lstdel.c lst/ft_lstdelone.c lst/ft_lstiter.c lst/ft_lstmap.c lst/ft_lstnew.c \
lst/ft_lstprint.c array/ft_arraymax.c array/ft_arraymin.c standart/ft_swap_int.c array/ft_arrayprint.c \
array/ft_arraysort.c array/ft_2darray_uchar_free.c lst/ft_lstdel_u.c lst/ft_lstdelmid.c  get_next_line/get_next_line.c \
standart/ft_printmap.c array/ft_2darrayclean.c array/ft_2darraynew.c standart/ft_point_new.c lst/ft_lstcount.c \
lst/ft_lstrev.c standart/ft_is_space.c standart/ft_countwords.c str/ft_strnewch.c  standart/ft_sign.c\
stack/ft_stack_print.c stack/ft_stack_create.c stack/ft_stack_push.c stack/ft_stack_pop.c\
stack/ft_stack_peek.c lst/ft_lst2w_pushback.c lst/ft_lst2w_new.c mem/ft_memprint.c\
standart/ft_print_node.c btree/ft_btree_create_node.c btree/ft_btree_apply_prefix.c btree/ft_btree_apply_infix.c\
btree/ft_btree_apply_suffix.c btree/ft_btree_insert_data.c btree/ft_btree_search_item.c btree/ft_btree_level_count.c\
queue/ft_queue_push.c queue/ft_queue_pop.c btree/ft_btree_apply_by_level.c btree/ft_btree_print.c rb_tree/ft_rb_node_create.c\
rb_tree/ft_rb_insert.c rb_tree/ft_rb_node_print.c standart/ft_realloc.c\
vector/vector_add.c vector/vector_delete.c vector/vector_free.c vector/vector_get.c vector/vector_init.c vector/vector_set.c vector/vector_total.c vector/vector_resize.c\
get_next_line/read_file.c

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
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CLEAR_LINE)[`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%] $(COL_BLUE)[$(NAME)] $(COL_GREEN)Compiling file [$(COL_VIOLET)$<$(COL_GREEN)].($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

clean:
	@rm -rf $(OBJECTS_DIRECTORY)

nu:
	@echo -ne "\r [`expr $(CURRENT_FILES) '*' 100 / $(TOTAL_FILES)`%]"

test: $(NAME) main.c
	@gcc -g $(NAME) main.c -I$(HEADERS_DIRECTORY) -o test

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
