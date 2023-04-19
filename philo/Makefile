NAME = philo
SRC = main.c eatsleepthink.c free.c init.c threads.c utils.c
OBJECT = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g
RM = rm -f
OBJDIR = obj
SRCDIR = src

all: obj $(OBJDIR) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)
	
clean:
	rm -rf $(OBJDIR)
	$(RM) $(OBJECT)

fclean: clean
	$(RM) $(NAME)

re: fclean all