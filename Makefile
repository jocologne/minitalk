NAME1=client
NAME2=server

COMP=cc
FLAGS=

#PrintF
PRINT_PATH = ft_printf/
PRINT_NAME = libftprintf.a
PRINT = $(PRINT_PATH)$(PRINT_NAME)

all: $(PRINT) $(NAME1) $(NAME2)

$(PRINT):
	@$(MAKE) -C $(PRINT_PATH) > /dev/null 2>/dev/null

$(NAME1): client.c
	@$(COMP) $(FLAGS) -o $(NAME1) client.c $(PRINT)

$(NAME2): server.c
	@$(COMP) $(FLAGS) -o $(NAME2) server.c $(PRINT)

clean:
	@$(MAKE) clean -C $(PRINT_PATH) > /dev/null 2>/dev/null

fclean: clean
	@rm -f $(NAME1) $(NAME2)
	@$(MAKE) fclean -C $(PRINT_PATH) > /dev/null 2>/dev/null

re: fclean all