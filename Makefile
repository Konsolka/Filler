NAME		= mburl.filler
NAME_V		= vis

# COMPIER

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

# COLORS

RED				:=	"\033[31m"
WAVE			:=	"\033[36m"
EOC				:=	"\033[0m"
BLINK			:=	"\033[5m"
GREEN			:=	"\033[32m"


# SCRIPT

SCRIPT_DIR		=	scripts/


# SRCS & OBJ

SRCS			:=	main.c algo.c placement.c

SRCS_V			:=	main_vis.c parce.c drawing.c lst_work.c
SRCS_V			+=	key_parsing.c draw_help.c calculations.c

OBJ				=	$(addprefix $(OBJDIR),$(SRCS:.c=.o))
OBJ_V			=	$(addprefix $(OBJDIR_V),$(SRCS_V:.c=.o))

# HEADERS

HEADER_LIST		=	filler.h
HEADER_LIST_V	=	vis.h

HEADERS			=	$(addprefix $(INCDIR), $(HEADER_LIST))
HEADERS_V		=	$(addprefix $(INCDIR), $(HEADER_LIST_V))

# DIRECTORIES

INCDIR			=	./includes/

SRC_DIR			=	./srcs/filler/
SRC_DIR_V		=	./srcs/vis/

OBJDIR_M		=	./obj/
OBJDIR			=	./obj/filler/
OBJDIR_V		=	./obj/vis/

# FT LIBRARY

LIBFT			=	$(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY =	./libft/
LIBFT_HEADERS	=	$(LIBFT_DIRECTORY)includes/
LIBFT_LINK		=	 -lft -L$(LIBFT_DIRECTORY)

# MLX LIBRARY

MLX_LINK		:=	-I /usr/local/include -L /usr/local/lib
MLX_LINK		+=	-lmlx -framework OpenGL -framework AppKit

# INCLUDES

INCLUDES		=	-I $(INCDIR) -I $(LIBFT_HEADERS)
INCLUDES_V		=	-I $(INCDIR) -I $(LIBFT_HEADERS) $(MLX_LINK)


all: $(NAME) $(NAME_V)

obj:
	@echo " - Creating dir $(OBJDIR)"
	@echo " - Creating dir $(OBJDIR_V)"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR_V)

$(OBJDIR)%.o:$(SRC_DIR)%.c $(HEADERS)
	@printf "\e[1;34m - Compiling %-23s  ->  %-23s\n\e[m" "$<" "$@"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR_V)%.o:$(SRC_DIR_V)%.c $(HEADERS_V)
	@printf "\e[1;34m - Compiling %-23s  ->  %-23s\n\e[m" "$<" "$@"
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
	@echo " - Deleting $(OBJDIR_M)"
	@rm -rf $(OBJDIR_M)


fclean: clean
	@echo " - Deleting $(NAME)"
	@echo " - Deleting $(NAME_V)"
	@echo " - Cleaning $(LIBFT_DIRECTORY)"
	@rm -rf $(NAME)
	@rm -rf $(NAME_V)
	@make -C $(LIBFT_DIRECTORY) fclean
re: fclean all


play5: $(NAME)
	@sh $(SCRIPT_DIR)play_5_games.sh

cleanlog:
	@sh $(SCRIPT_DIR)clean.sh

gamelog:
	@sh $(SCRIPT_DIR)game_log_file.sh

norm:
	@sh $(SCRIPT_DIR)norm.sh
ffclean: fclean cleanlog

.PHONY: all obj clean fclean re