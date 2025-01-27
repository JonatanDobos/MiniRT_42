NAME			:=	miniRT

# Get the number of logical processors (threads)
N_JOBS			:=	$(shell nproc)
# N_JOBS			:=	1

# (-j) Specify the number of jobs (commands) to run simultaneously
MULTI_THREADED	:=	-j $(N_JOBS)

# MAKEFLAGS will automatically apply the specified options (e.g., parallel execution) when 'make' is invoked
MAKEFLAGS		+=	$(MULTI_THREADED)

# COMPILER		:=	cc
COMPILER		:=	gcc
RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

#		CFLAGS for testing
CFLAGS			 =	-MMD -MP
# CFLAGS			+=	-Wall -Wextra
# # Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-Werror
# CFLAGS			+=	-g -Og
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code

#		Temporary CFLAGS
CFLAGS			+=	-Wno-unused-result
#		Optimization flags
# Generate code optimized for the host machine's CPU
OFLAGS			 =	-march=native
# # Disable setting errno after math functions for better performance
# OFLAGS			+=	-fno-math-errno
# # This flag allows the compiler to use reciprocal approximations for division operations, which can improve performance but may reduce precision.
# OFLAGS			+=	-freciprocal-math
# # This flag allows the compiler to ignore the distinction between positive and negative zero, which can enable more aggressive optimizations.
# OFLAGS			+=	-fno-signed-zeros
# # This flag tells the compiler that floating-point operations cannot generate traps (such as overflow or division by zero), allowing for more aggressive optimizations.
# OFLAGS			+=	-fno-trapping-math

OFLAGS += -Ofast
OFLAGS += -O3
# ifeq ($(shell uname -s),Linux)
# 	ifeq ($(MAKECMDGOALS),malloc_wrap)
# 		WRAP_MALLOC	:= -Wl,--wrap=malloc
# 		OFLAGS := $(filter-out -Ofast, $(OFLAGS))
# 		OFLAGS := $(filter-out -O3, $(OFLAGS))
# 	endif
# endif

ifeq ($(MAKECMDGOALS),malloc_wrap)
	CFLAGS	+=	-D MALLOC_WRAP=true
	OFLAGS	:= 	$(filter-out -Ofast, $(OFLAGS))
	OFLAGS	:= 	$(filter-out -O3, $(OFLAGS))
	LIBWRAP :=	malloc_wrap
	ifeq ($(shell uname -s),Linux)
		WRAP_MALLOC	:= -Wl,--wrap=malloc
	endif
endif

#	macOS = Darwin
ifeq ($(shell uname -s), Darwin)
# GLFW := $(shell brew --prefix glfw)/lib
# LINKER_FLAGS += -L $(GLFW)
# CORE_COUNT = $(shell sysctl -n hw.ncpu)
	OFLAGS += -flto
else
# LINKER_FLAGS += -ldl
# CORE_COUNT = $(shell grep '^processor' /proc/cpuinfo | wc -l)
	# OFLAGS += -fsingle-precision-constant -flto=auto -fuse-linker-plugin
endif
CFLAGS += $(OFLAGS)

SCREEN_RES		:=	$(shell xrandr | grep '*' | uniq | awk '{print $$1}')
SCREEN_WIDTH	:=	$(shell echo $(SCREEN_RES) | cut -d 'x' -f 1)
SCREEN_HEIGHT	:=	$(shell echo $(SCREEN_RES) | cut -d 'x' -f 2)

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

PARSE			:=	parse_objects.c	parse_peripherals.c	parsing_utils.c	parsing.c string_utils.c _debug.c

MLX				:=	window_setup.c			keyhooks.c		loophooks.c	camera_move.c	camera_rotate.c

SCENE			:=	create.c				test.c

UTILS			:=	utils.c					math.c

ERROR			:=	error.c					print.c

DEBUG			:=	print_info.c

# plane.c										
# sphere.c										

#		Find all .c files in the specified directories
SRCP			:=	$(addprefix $(SRC_DIR), $(MAIN))			\
					$(addprefix $(SRC_DIR)parsing/, $(PARSE))	\
					$(addprefix $(SRC_DIR)error/, $(ERROR))		\
					$(addprefix $(SRC_DIR)mlx/, $(MLX))			\
					$(addprefix $(SRC_DIR)scene/, $(SCENE))		\
					$(addprefix $(SRC_DIR)utils/, $(UTILS))		\
					$(addprefix $(SRC_DIR)debug/, $(DEBUG))

#		Generate object file names
OBJS 			:=	$(SRCP:%.c=$(BUILD_DIR)%.o)
#		Generate Dependency files
DEPS			:=	$(OBJS:.o=.d)

#		HEADERS
INCS			:=	miniRT.h		parsing.h		RTerror.h			scene.h				RTmlx.h					utils.h			debug.h
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
	$(BUILD) $(WRAP_MALLOC) $(OBJS) $(LIBS) $(LINKER_FLAGS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(BUILD) $(INCLUDE_RT) -c $< -o $@

$(LIBFT_L):
	@$(MAKE) $(MULTI_THREADED) $(PRINT_NO_DIR) -C $(LIBFT_D) $(LIBWRAP) OFLAGS="$(OFLAGS)"

$(MLX42_L):
	@cmake $(MLX42_D) -B $(MLX42_D)/build && cmake --build $(MLX42_D)/build --parallel $(N_JOBS)
	# @printf "MLX is being built...\n"
	# @cmake $(MLX42_D) -B $(MLX42_D)/build > /dev/null 2>&1 && cmake --build $(MLX42_D)/build --parallel $(N_JOBS) > /dev/null 2>&1
	# @printf "\rMLX has been built!  \n"

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

malloc_wrap: all

test: all
	./$(NAME) ./test1.rt

test2: all
	./$(NAME) ./plane_sphere.rt

test3: all
	./$(NAME) ./sphere_behind_sphere.rt

test4: all
	./$(NAME) ./cylinder.rt

valgrind: all
	valgrind --leak-check=full -s ./$(NAME)

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

