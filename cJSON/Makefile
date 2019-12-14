NAME = libjson.a

FLAGS = -Wall -Wextra -Werror

SRCS = cJSON.c

OUT = cJSON.o

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRCS)
	ar rc $(NAME) $(OUT)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OUT)

fclean : clean
	/bin/rm -f $(NAME)

re: fclean all
