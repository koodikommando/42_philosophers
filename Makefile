CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRCS = init.c \
	monitoring.c \
	philosophers.c \
	routine_functions.c \
	threads.c \
	utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all