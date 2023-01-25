NAME			=	minishell

CC			=	gcc

SRC_DIR			=	$(shell find srcs -type d)

LIBFT			=	./libft
LIBFT_A			=	./libft/libft.a
OBJ_DIR			=	.obj

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

# library -----------------------------------------------------------

SRC			=	main.c env.c pwd.c error.c env_list_utils.c ft_exec.c parsing_manager.c signals.c token_list_utils.c

INC			=	includes/minishell.h 

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags -------------------------------------------------

CFLAGS			=	-Wall -Wextra -Werror -g3
IFLAGS		=	-I includes/ -I libft/includes -I /usr/include

# Colors ------------------------------------------------------------

_GREY	=	$'\e[30m
_RED	=	$'\e[31m
_GREEN	=	$'\e[32m
_YELLOW	=	$'\e[33m
_BLUE	=	$'\e[34m
_PURPLE	=	$'\e[35m
_CYAN	=	$'\e[36m
_WHITE	=	$'\e[37m

# main part ---------------------------------------------------------

$(OBJ_DIR)/%.o : %.c $(INC)
		@echo "Compiling $(_YELLOW)$@$(_WHITE) ... \c"
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
		@echo "$(_GREEN)DONE$(_WHITE)"

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
		@make -C $(LIBFT)

$(NAME): $(OBJ)
		@echo "-----\nCreating Binary File $(_YELLOW)$@$(_WHITE) ... \c"
		$(CC) $(CFLAGS) $(OBJ) $(IFLAGS) $(LIBFT_A) -o $(NAME) -lreadline
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"

clean:
		@echo "$(_WHITE)Deleting Objects Directory $(_YELLOW)$(OBJ_DIR)$(_WHITE) ... \c"
		@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
		@make clean -C $(LIBFT)
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"

fclean: clean
		@echo "$(_WHITE)Deleting Binary File $(_YELLOW)$(NAME)$(_WHITE) ... \c"
		@rm -f $(NAME) $(NAME_BONUS)
		@echo "$(_GREEN)DONE$(_WHITE)\n-----"

re:		fclean all

.PHONY:		all bonus clean fclean re
