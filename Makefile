NAME	= mburl.filler
NAME_V	= vis

# compiler

CC		= gcc
CFLAGS	= -Wall -Wextra -g

# colors

RED		:= "\033[31m"
WAVE	:= "\033[36m"
EOC		:= "\033[0m"
BLINK	:= "\033[5m"
GREEN	:= "\033[32m"

# srcs and obj

SRCS		= main.c algo.c placement.c
SRCS_V		= main_vis.c parce.c

OBJ		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))
OBJ_V		= $(addprefix $(OBJDIR_V),$(SRCS_V:.c=.o))

# directories
INCDIR			= ./includes/

SRC_DIR			= ./srcs/filler/
SRC_DIR_V		= ./srcs/vis/

OBJDIR			= ./obj/filler/
OBJDIR_V		= ./obj/vis/

# ft library
FT				= ./libft/
FT_LIB			= $(addprefix $(FT),libft.a)
FT_INC			= -I ./libft/includes
FT_LNK			= -L ./libft -l ft


all: obj $(FT_LIB) $(NAME) $(NAME_V)

obj:
	@echo " - Creating dir $(OBJDIR)"
	@echo " - Creating dir $(OBJDIR_V)"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR_V)

$(OBJDIR)%.o:$(SRC_DIR)%.c
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(OBJDIR_V)%.o:$(SRC_DIR_V)%.c
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(NAME): $(OBJ)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ) $(FT_LNK) -o $@

$(NAME_V): $(OBJ_V)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ_V) $(FT_LNK) -o $@

clean:
	rm -rf obj/

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_V)
	make -C $(FT) fclean

re: fclean all