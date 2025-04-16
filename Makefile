NAME			:=	miniRT

#	Get the number of logical processors (threads)
OS				:=	$(shell uname -s)
ifeq ($(OS), Linux)
	N_JOBS		:=	$(shell nproc)
else ifeq ($(OS), Darwin)
	N_JOBS		:=	$(shell sysctl -n hw.logicalcpu)
else
	N_JOBS		:=	1
endif

#	(-j) Specify the number of jobs (commands) to run simultaneously
MULTI_THREADED	:=	-j $(N_JOBS)

#	MAKEFLAGS will automatically apply the specified options (e.g., parallel execution) when 'make' is invoked
MAKEFLAGS		+=	$(MULTI_THREADED)

RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

#		CFLAGS for testing
COMPILER		:=	gcc
CFLAGS			+=	-Wall -Wextra
# CFLAGS			+=	-Werror
CFLAGS			+=	-MMD -MP
CFLAGS			+=	-g
#		Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-fsanitize=address

#		Sets MINIRT_THREADS to 2 if N_JOBS (logical processors) is greater than 1, otherwise sets it to 1.
MINIRT_THREADS	:=	$(if $(filter-out 1,$(N_JOBS)),2,1)

#		Temporary CFLAGS
CFLAGS			+=	-pthread -D THREADS=$(MINIRT_THREADS)
CFLAGS			+=	-Wno-unused-result
#		Optimization flags
OFLAGS			+=	-Ofast
# OFLAGS += -O3
# 		Generate code optimized for the host machine's CPU
OFLAGS			 =	-march=native
#		Disable setting errno after math functions for better performance
OFLAGS			+=	-fno-math-errno
#		This flag allows the compiler to use reciprocal approximations for division operations, which can improve performance but may reduce precision.
OFLAGS			+=	-freciprocal-math
#		This flag allows the compiler to ignore the distinction between positive and negative zero, which can enable more aggressive optimizations.
OFLAGS			+=	-fno-signed-zeros
#		This flag tells the compiler that floating-point operations cannot generate traps (such as overflow or division by zero), allowing for more aggressive optimizations.
OFLAGS			+=	-fno-trapping-math

ifeq ($(OS), Linux)
	SCREEN_RES	:=	$(shell xrandr | grep '*' | uniq | awk '{print $$1}')
	OFLAG		+=	-fsingle-precision-constant -flto=auto -fuse-linker-plugin
else ifeq ($(OS), Darwin)  # macOS
	SCREEN_RES	:=	$(shell system_profiler SPDisplaysDataType 2>/dev/null | grep Resolution | head -n 1 | awk '{print $$2"x"$$4}')
	OFLAGS		+=	-flto
endif
SCREEN_WIDTH	:=	$(shell echo $(SCREEN_RES) | cut -d 'x' -f 1)
SCREEN_HEIGHT	:=	$(shell echo $(SCREEN_RES) | cut -d 'x' -f 2)
CFLAGS			+=	$(OFLAGS)
CFLAGS			+=	-D SCREEN_WIDTH=$(SCREEN_WIDTH) -D SCREEN_HEIGHT=$(SCREEN_HEIGHT)

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
PARSE			:=	parse/parsing.c				parse/parse_utils.c												\
					line_validate/line_val.c	line_validate/number_check.c									\
					init_input/parse_objects.c	init_input/init_primitives.c
THREADING		:=	handling/thread_setup.c		handling/thread_terminate.c										\
					routine/routine.c			routine/utils_thread.c			routine/read_scene.c
MLX				:=	setup/window_setup.c		setup/window_setup2.c											\
					hooks/hooks.c				hooks/loop_hooks.c				hooks/mouse_hook.c				\
					hooks/loop_move_hooks.c																		\
					transform/cam/camera_move.c	transform/cam/camera_rotate.c									\
					transform/obj/obj_move.c	transform/obj/obj_rotate.c		transform/obj/obj_modification.c\
					print/print_objs.c			print/print_primitives.c
SCENE			:=	set_filename.c				create_rt_file.c				scene_elements.c				\
					geometric_primitives.c
RENDER			:=	rendering/render.c			rendering/trace_ray.c											\
					rendering/set_pixel.c		rendering/upscale_manager.c 									\
					intersect/obj_intersect.c	intersect/cylinder.c			intersect/lighting.c
MATH_VEC		:=	vec/vec_arithmetic.c		vec/vec_geometry.c				vec/vec_transform.c				\
					math/clamp.c
SETUP_CLEAN		:=	init.c						cleanup.c
ERROR			:=	error.c						print.c

#		Find all .c files in the specified directories
SRCP			:=	$(addprefix $(SRC_DIR), $(MAIN))															\
					$(addprefix $(SRC_DIR)parsing/, $(PARSE))													\
					$(addprefix $(SRC_DIR)threads/, $(THREADING))												\
					$(addprefix $(SRC_DIR)mlx/, $(MLX))															\
					$(addprefix $(SRC_DIR)create_scene_file/, $(SCENE))											\
					$(addprefix $(SRC_DIR)render/, $(RENDER))													\
					$(addprefix $(SRC_DIR)math_vector/, $(MATH_VEC))											\
					$(addprefix $(SRC_DIR)setup_cleanup/, $(SETUP_CLEAN))										\
					$(addprefix $(SRC_DIR)error/, $(ERROR))

#		Generate object file names
OBJS 			:=	$(SRCP:%.c=$(BUILD_DIR)%.o)
#		Generate Dependency files
DEPS			:=	$(OBJS:.o=.d)

#		HEADERS
INCS			:=	miniRT.h			parsing.h			threadsRT.h			scene.h				RTmlx.h		\
					render.h			setup_clean.h		mathRT.h			RTerror.h
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
DELETE			:=	*.out			**/*.out			.DS_Store												\
					**/.DS_Store	.dSYM/				**/.dSYM/

#		RECIPES
all:	$(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(BUILD) $(OBJS) $(LIBS) $(LINKER_FLAGS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(BUILD) $(INCLUDE_RT) -c $< -o $@

$(LIBFT_L):
	@$(MAKE) $(MULTI_THREADED) $(PRINT_NO_DIR) -C $(LIBFT_D)

$(MLX42_L):
	@cmake $(MLX42_D) -B $(MLX42_D)/build && cmake --build $(MLX42_D)/build --parallel $(N_JOBS)

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

re:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) all

single_thread:
	@$(MAKE) $(PRINT_NO_DIR) MINIRT_THREADS=1	

malloc_wrap: all

test: all
	./$(NAME) ./scenes/test.rt

test2: all
	./$(NAME) ./scenes/plane_sphere.rt

test3: all
	./$(NAME) ./scenes/sphere_behind_sphere.rt

test4: all
	./$(NAME) ./scenes/cylinder.rt

test5: all
	./$(NAME) ./scenes/resizing.rt

white: all
	./$(NAME) ./scenes/white.rt

valrind: all
	./$(NAME) ./scenes/test1.rt

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
