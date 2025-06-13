NAME	:= fractol
UNAME_S := $(shell uname -s)

CFLAGS	:= -Wextra -Wall -Werror
LIBFT	:= ./lib/libft


SRCS	:= $(shell find ./srcs -iname "*.c")
OBJS	:= ${SRCS:./srcs/%.c=./objs/%.o}

ifeq ($(UNAME_S),Linux)
	LIBMLX	:= ./lib/minilibx-linux/
	LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/libmlx.a -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBMLX	:= ./lib/minilibx/
	LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/libmlx.a -framework OpenGL -framework AppKit
endif
HEADERS	:= -I ./includes -I $(LIBMLX) -I . -I$(LIBFT)/includes
all: libmlx libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)
libmlx:
	@$(MAKE) -C $(LIBMLX)

./objs/%.o: ./srcs/%.c
	@mkdir -p objs/
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "\\nCompiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf ./objs

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) clean -C $(LIBMLX)

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
