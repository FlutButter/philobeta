NAME = philo

RM = RM -f
CC = cc

SRCS = philo.c initialize.c utils.c activity.c 
HEADER = philo.h

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	fclean all

.PHONY: all clean fclean re