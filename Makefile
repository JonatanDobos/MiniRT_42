NAME	=	miniRT

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra
# CFLAGS	+=	-Wunused -Wconversion -Wimplicit
# CFLAGS	+=	-g -fsanitize=address

LMLXDIR	=	./libs/MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LFTDIR	=	./libs/libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS	=	-I ./include -I $(LMLXDIR)/include
LIBS	=	$(LIBMLX) $(LIBFT)

SRCDIR	=	./mandatory/src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/cleanup.c \
			$(SRCDIR)/error.c \
			$(SRCDIR)/exit.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/mlx_hook.c \
			$(SRCDIR)/mlx_init.c \
			$(SRCDIR)/parsing_utils.c \
			$(SRCDIR)/parsing.c \
			$(SRCDIR)/print.c \
			$(SRCDIR)/scaling.c \
			$(SRCDIR)/string_utils.c \
			$(SRCDIR)/vec_advanced.c \
			$(SRCDIR)/vec_math.c

OBJDIRM	=	./mandatory/obj
OBJS	=	$(SRC:$(SRCDIR)%.c=$(OBJDIRM)%.o)

all: $(LIBS) $(NAME)

#bonus

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(OBJDIRM)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJDIRM) $(OBJS)
	$(CC) $(FSANIT) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

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

re: fclean all

.PHONY: all clean fclean re