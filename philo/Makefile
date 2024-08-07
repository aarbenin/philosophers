# Цвета для вывода в консоль
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

NAME = philo

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./includes

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

CC = cc
SAN_FLAGS = # -fsanitize=thread
CFLAGS = -Wall -Werror -Wextra -pthread -g $(SAN_FLAGS) -I$(INCDIR)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(SAN_FLAGS)
	@echo "${GREEN}All source files have been successfully compiled${RESET}"
	@echo "${GREEN}Yay! $(NAME) is ready to run! 🚀${RESET}"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJDIR)
	@echo "${RED}Cleaned up the mess! 🧹${RESET}"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}All clean, like it never happened!${RESET}"

re: fclean all

.PHONY: all clean fclean re
