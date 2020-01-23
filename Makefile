NAME		= mburl.filler
NAME_V		= vis

# compiler

CC			= gcc
CFLAGS		= -Wall -Wextra -g

# colors

RED			:= "\033[31m"
WAVE		:= "\033[36m"
EOC			:= "\033[0m"
BLINK		:= "\033[5m"
GREEN		:= "\033[32m"

# srcs and obj

SRCS		=	main.c\
				algo.c\
				placement.c

SRCS_V		=	main_vis.c\
				parce.c\
				drawing.c\
				lst_work.c\
				key_parsing.c\
				draw_help.c\
				calculations.c

OBJ			= $(addprefix $(OBJDIR),$(SRCS:.c=.o))
OBJ_V		= $(addprefix $(OBJDIR_V),$(SRCS_V:.c=.o))

# directories

HEADER_LIST		= filler.h
INCDIR			= ./includes/
HEADERS			= $(addprefix $(INCDIR), $(HEADER_LIST))

SRC_DIR			= ./srcs/filler/
SRC_DIR_V		= ./srcs/vis/

OBJDIR			= ./obj/filler/
OBJDIR_V		= ./obj/vis/

# ft library

LIBFT			= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS	= $(LIBFT_DIRECTORY)includes/
LIBFT_LINK		=  -lft -L$(LIBFT_DIRECTORY)
# mlx library
MLX_LINK		= -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

# include
INCLUDES		= -I $(INCDIR) -I $(LIBFT_HEADERS)
INCLUDES_V		= -I $(INCDIR) -I $(LIBFT_HEADERS) $(MLX_LINK)
all: $(NAME) $(NAME_V)

obj:
	@echo 		" - Creating dir $(OBJDIR)"
	@echo 		" - Creating dir $(OBJDIR_V)"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR_V)

$(OBJDIR)%.o:$(SRC_DIR)%.c $(HEADERS)
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR_V)%.o:$(SRC_DIR_V)%.c $(HEADERS)
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(NAME): $(LIBFT) obj $(OBJ)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ) $(LIBFT_LINK) -o $@

$(NAME_V): $(LIBFT) obj $(OBJ_V)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ_V) $(MLX_LINK) $(LIBFT_LINK) -o $@

clean:
	@echo	" - Deleting dir obj/"
	@rm -rf obj/

fclean: clean
	@echo	" - Deleting $(NAME)"
	@echo	" - Deleting $(NAME_V)"
	@rm -rf $(NAME)
	@rm -rf $(NAME_V)
	@make -C $(LIBFT_DIRECTORY) fclean

re: fclean all