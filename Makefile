NAME			:=	miniRT

COMPILER		:=   cc
RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

CFLAGS			 =	-flto -Ofast

#		CFLAGS for testing
CFLAGS			+=	-MMD -MP
# CFLAGS			+=	-Wall -Wextra
# # Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-Werror
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code
CFLAGS			+=	-g3

SCREEN_RES := $(shell xrandr | grep '*' | uniq | awk '{print $$1}')
SCREEN_WIDTH := $(shell echo $(SCREEN_RES) | cut -d 'x' -f 1)
SCREEN_HEIGHT := $(shell echo $(SCREEN_RES) | cut -d 'x' -f 2)

# Pass screen resolution as defines to the compiler
CFLAGS += -D SCREEN_WIDTH=$(SCREEN_WIDTH) -D SCREEN_HEIGHT=$(SCREEN_HEIGHT)

#		Directories
BUILD_DIR		:=	.build/
INCD			:=	include/
#		Extern Libaries Directories
EXTERN_LIBS		:=	extern_libraries/
LIBFT_DIR		:=	$(EXTERN_LIBS)libft/
MLX42_PATH		:=	$(EXTERN_LIBS)MLX42/

#		SOURCE FILES
SRC_DIR			:=	src/

MAIN			:=	main.c

MLX				:=	window_setup.c			keyhooks.c		

SCENE			:=	create.c				test.c

UTILS			:=	utils.c					math.c

# plane.c										
# sphere.c										

#		Find all .c files in the specified directories
SRCP			:=	$(addprefix $(SRC_DIR), $(MAIN))				\
					$(addprefix $(SRC_DIR)/mlx/, $(MLX))			\
					$(addprefix $(SRC_DIR)/scene/, $(SCENE))		\
					$(addprefix $(SRC_DIR)/utils/, $(UTILS))

#		Generate object file names
OBJS 			:=	$(SRCP:%.c=$(BUILD_DIR)%.o)
#		Generate Dependency files
DEPS			:=	$(OBJS:.o=.d)

#		HEADERS
INCS			:=	miniRT.h				scene.h				RTmlx.h					utils.h
INCP			:=	$(addprefix $(INCD), $(INCS))
HEADERS			:=	$(INCP)
INCLUDE_RT		:=	-I $(INCD)

#		LIBFT
LIBFT_D			:=	$(EXTERN_LIBS)libft/
LIBFT_N			:=	libft.a

LIBFT_I			:=	$(addprefix $(LIBFT_D), $(INCD))
LIBFT_L			:=	$(addprefix $(LIBFT_D), $(LIBFT_N))

INCLUDE			 =	-I $(LIBFT_I)
LIBS			 =	$(LIBFT_L)

#		MLX42
MLX42_D			:=	$(EXTERN_LIBS)MLX42/
MLX42_N			:=	libmlx42.a
MLX42_I			:=	$(addprefix $(MLX42_D), $(INCD))
MLX42_L			:=	$(addprefix $(MLX42_D)build/, $(MLX42_N))

INCLUDE			+=	-I $(MLX42_I)
LIBS			+=	$(MLX42_L)

LINKER_FLAGS	 =	-lglfw -lm

BUILD			:=	$(COMPILER) $(INCLUDE) $(CFLAGS)

#		Remove these created files
DELETE			 =	*.out										\
					.DS_Store									\
					*.dSYM/

#		RECIPES
all:	$(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(BUILD) $(OBJS) $(LIBS) $(LINKER_FLAGS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(BUILD) $(INCLUDE_RT) -c $< -o $@

$(LIBFT_L):
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_D)

$(MLX42_L):
	# @cmake $(MLX42_D) -B $(MLX42_D)/build && cmake --build $(MLX42_D)/build --parallel
	@printf "MLX is being built..."
	@cmake $(MLX42_D) -B $(MLX42_D)/build > /dev/null 2>&1 && cmake --build $(MLX42_D)/build --parallel > /dev/null 2>&1
	@printf "\rMLX has been built!  \n"

cln:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

clean:
	$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_DIR) clean
	@$(RM) $(MLX42_PATH)/build
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean:	clean
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_DIR) no_print_fclean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

fcln:	cln
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:		fclean all

valgrind: all
	./$(NAME)

print-%:
	$(info $($*))

#		Include the dependency files
-include $(DEPS)

.PHONY:	$(NAME) $(BUILD_DIR) $(LIBFT_L) all cln clean fclean fcln re print-%

# ----------------------------------- colors --------------------------------- #
BOLD		= \033[1m
DIM			= \033[2m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m
RESET		= \033[0m

R_MARK_UP	= $(MAGENTA)$(BOLD)
CA_MARK_UP	= $(GREEN)$(BOLD)

# ----------------------------------- messages ------------------------------- #
CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED := $(R_MARK_UP)REMOVED $(CYAN)%s$(MAGENTA) (%s) $(RESET)\n
CREATED := $(CA_MARK_UP)CREATED $(CYAN)%s$(GREEN) (%s) $(RESET)\n

test: all
	./$(NAME)

valgrind: all
	valgrind -s --leak-check=full ./$(NAME)
