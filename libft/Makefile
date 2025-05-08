# Text styles
DEL_LINE =		\033[2K
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m

# Basic bright colors
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m

# Other colors
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

SRC = \
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_itoa.c\
	ft_hxtoa.c\
	ft_printf_itoa.c\
	ft_printf_utoa.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putunbr_fd.c\
	ft_print_memory.c\
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_printf/ft_printf.c\
	ft_printf/parsing.c\
	ft_printf/apply_specifiers.c\
	ft_printf/ft_printf_c_s_u.c\
	ft_printf/ft_printf_d_i.c\
	ft_printf/ft_printf_x_p.c\
	get_next_line/get_next_line.c\
	get_next_line/get_next_line_utils.c

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
OBJ_DIR = build
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC
NAME = libft.a

# Compile libft
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\n${GREEN} Created $(NAME) ${DEF_COLOR}\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$<${DEF_COLOR}"
	@$(CC) $(CFLAGS) -c $< -o $@

# Targets
all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "${GREEN} Cleaned $(NAME) library ${DEF_COLOR}"

re: fclean all
