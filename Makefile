NAME			=	miniRT

#	libaries
EXTERN_LIBS	=	./extern_libraries

#	Libraries
LIBFT			=	$(LIBFT_DIR)/libft.a

#	Directories
LIBFT_DIR		=	./extern_libraries/libft
SRC_DIR			=	source
CMD_DIR			=	$(SRC_DIR)
MLX42_PATH		=	$(EXTERN_LIBS)/MLX42
BUILD_DIR		=	.build

#	MLX
HEADERS		=	-Iinclude -lglfw -L "/usr/local/Cellar/glfw/3.4/lib/"
MLXLIB		=	$(MLX42_PATH)/build/libmlx42.a

#	Flags
COMPILER		=   cc
# CFLAGS			+=	-Wall -Wextra
# Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-Werror
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code
CFLAGS			+=	-MMD -MP
CFLAGS			+=	-g3
RM				=	rm -rf
MKDIR_P			=	mkdir -p
PRINT_NO_DIR	=	--no-print-directory

#	Remove these created files
DELETE			=	*.out						\
					.DS_Store					\
					*.dSYM/

MAIN			=	main.c
# MAIN			=	

CMD				=	keyhooks.c					\
					plane.c						\
					sphere.c					\
					test.c

# Find all .c files in the specified directories
SRCS		:=	$(addprefix $(SRC_DIR)/, $(MAIN))	\
				$(addprefix $(CMD_DIR)/, $(CMD))

# Generate object file names
OBJS 			:= $(SRCS:%.c=$(BUILD_DIR)/%.o)
# Gene			rate dependency file names
DEPS := $(OBJS:.o=.d)

# Default target
all:	$(NAME)

$(MLXLIB):
	@cd $(MLX42_PATH) && cmake -B build && cmake --build build -j4

# cc $(CFLAGS) $(OBJ) $(MLXLIB) $(HEADERS) -lm -o $(NAME)
$(NAME): $(LIBFT) | $(OBJS) $(MLXLIB)
	@$(COMPILER) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXLIB) $(HEADERS) -lm -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

# $(CC) $(CFLAGS) -c $< -o $@
# Compile .c files to .o files
$(BUILD_DIR)/%.o: %.c
	@$(MKDIR_P) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_DIR)

clean:
	$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_DIR) clean
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR)/ $(CUR_DIR)$(BUILD_DIR)/

fclean:	clean
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFT_DIR) no_print_fclean
	@$(RM) $(NAME) $(SRC_42_N) $(LINKED_LIST_N) $(GNL_N) $(FT_PRINTF_N) $(MISC_N)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:		fclean all

print-%:
	$(info $($*))

# Include the dependency files
-include $(DEPS)
# -include $(wildcard $(BUILD_DIR)/**/*.d)

.PHONY:	$(NAME) $(BUILD_DIR) $(LIBFT) all clean fclean re

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