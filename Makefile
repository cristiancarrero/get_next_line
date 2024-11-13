NAME = get_next_line.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADERS = get_next_line.h
BONUS_HEADERS = get_next_line_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus