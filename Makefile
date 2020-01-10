NAME	= mburl.filler

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

OBJ		= $(addprefix $(OBJDIR),$(SRCS:.c=.o))


# directories
INCDIR			= ./includes/

SRC_DIR			= ./srcs/

OBJDIR			= ./obj/

# ft library
FT				= ./libft/
FT_LIB			= $(addprefix $(FT),libft.a)
FT_INC			= -I ./libft/includes
FT_LNK			= -L ./libft -l ft


all: obj $(FT_LIB) $(NAME)

obj:
	@echo " - Creating dir $(OBJDIR)"
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRC_DIR)%.c
	@echo $(WAVE) " - Compiling $<  ->  $@" $(EOC)
	@$(CC) -g $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(NAME): $(OBJ)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ) $(FT_LNK) -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all