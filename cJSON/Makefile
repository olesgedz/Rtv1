NAME = libjson.a

FLAGS = -Wall -Wextra -Werror

SRCS = *.c

OUT = *.o

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
