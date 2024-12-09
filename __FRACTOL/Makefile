NAME	= fractol

CC		= cc

CFLAGS	= -Wall -Werror -Wextra

FSANIT	= -g -fsanitize=address

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LMLXDIR)/include
LIBS	= $(LIBMLX) $(LIBFT)

SRCDIR	= ./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/math.c \
			$(SRCDIR)/init_struct.c \
			$(SRCDIR)/image.c \
			$(SRCDIR)/key_mlx.c \
			$(SRCDIR)/key_utils.c \
			$(SRCDIR)/key_palette.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/color.c \
			$(SRCDIR)/split.c \
			$(SRCDIR)/hooks_mlx.c \
			$(SRCDIR)/input_handling.c \
			$(SRCDIR)/palette_init_j.c \
			$(SRCDIR)/palette_init_m.c

OBJS	= ${SRC:.c=.o}

all: $(LIBS) $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(FSANIT) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LMLXDIR)/build
	rm -rf $(LFTDIR)/libft.a

re: clean all

.PHONY: all clean fclean re