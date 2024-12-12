NAME	=	miniRT

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

FSANIT	=	-g -fsanitize=address

LMLXDIR	=	./libs/MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LFTDIR	=	./libs/libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS	=	-I ./include -I $(LMLXDIR)/include
LIBS	=	$(LIBMLX) $(LIBFT)

SRCDIR	=	./mandatory/src
SRC		=	/main.c \
			/utils_window.c

OBJDIRM	=	./mandatory/obj_mandatory
OBJS	=	${SRC:(SRCDIR)%.c=(OBJDIRM)%.o}

all: $(LIBS) $(NAME)

#bonus

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
	rm -df $(OBJDIRM)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LMLXDIR)/build
	rm -rf $(LFTDIR)/libft.a

re: clean all

.PHONY: all clean fclean re