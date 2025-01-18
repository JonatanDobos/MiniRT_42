NAME	=	miniRT

# CC		=	cc

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	=	-flto -O3
# CFLAGS	+=	-Wunused -Wconversion -Wimplicit
# CFLAGS	+=	-g
# CFLAGS	+=	-fsanitize=address

#		Optimization flags
# Generate code optimized for the host machine's CPU
OFLAGS			 =	-march=native
# Disable setting errno after math functions for better performance
OFLAGS			+=	-fno-math-errno
# This flag allows the compiler to use reciprocal approximations for division operations, which can improve performance but may reduce precision.
OFLAGS			+=	-freciprocal-math
# This flag allows the compiler to ignore the distinction between positive and negative zero, which can enable more aggressive optimizations.
OFLAGS			+=	-fno-signed-zeros
# This flag tells the compiler that floating-point operations cannot generate traps (such as overflow or division by zero), allowing for more aggressive optimizations.
OFLAGS			+=	-fno-trapping-math

LMLXDIR	=	./libs/MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LFTDIR	=	./libs/libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS	=	-I ./include -I $(LMLXDIR)/include
LIBS	=	$(LIBMLX) $(LIBFT)

SRCDIR	=	./mandatory/src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/camera_move.c \
			$(SRCDIR)/camera_rotate.c \
			$(SRCDIR)/cleanup.c \
			$(SRCDIR)/error.c \
			$(SRCDIR)/exit.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/mlx_hook.c \
			$(SRCDIR)/mlx_init.c \
			$(SRCDIR)/parse_objects.c \
			$(SRCDIR)/parse_peripherals.c \
			$(SRCDIR)/parsing_utils.c \
			$(SRCDIR)/parsing.c \
			$(SRCDIR)/print.c \
			$(SRCDIR)/render_utils.c \
			$(SRCDIR)/render.c \
			$(SRCDIR)/scaling.c \
			$(SRCDIR)/string_utils.c \
			$(SRCDIR)/vec_advanced.c \
			$(SRCDIR)/vec_math.c \
			$(SRCDIR)/_debug.c

OBJDIRM	=	./mandatory/obj
OBJS	=	$(SRC:$(SRCDIR)%.c=$(OBJDIRM)%.o)

all: $(LIBS) $(NAME)

#bonus

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(OBJDIRM)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(OFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJDIRM) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJDIRM):
	mkdir -p $(OBJDIRM)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(OBJS)
	rm -df $(OBJDIRM)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LMLXDIR)/build
	rm -rf $(LFTDIR)/libft.a

mclean:
	rm -rf $(OBJS)
	rm -df $(OBJDIRM)
	rm -rf $(NAME)

test: mclean all

re: fclean all

.PHONY: all clean fclean re