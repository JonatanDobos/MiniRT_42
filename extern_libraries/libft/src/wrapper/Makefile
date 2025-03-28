NAME			:=	wrap.a
COMPILER		:=	gcc
RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

#		Compiler flags
CFLAGS			+=	-MMD -MP
CFLAGS			+=	-Wall -Wextra
CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code
#		Werror cannot go together with fsanitize, because fsanitize won't work correctly.
CFLAGS			+=	-Werror
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-g

#		Base Directories
SRC_DIR			:=	src/
INC_DIR			:=	include/
BUILD_DIR		:=	.build/

#		Source files by category
WRAP			:=	linux_malloc_wrapper.c		mac_malloc_wrapper.c			malloc_handlers.c		\
					open_wrapper.c				wrap_utils.c

#		Extra Sources
WRAP_SRCS		:=	$(addprefix $(SRC_DIR), $(WRAP))

#		Generate object file names
WRAP_OBJS		:=	$(WRAP_SRCS:%.c=$(BUILD_DIR)%.o)

#		Generate Dependency files
DEPS			:=	$(WRAP_OBJS:.o=.d)

#		Header files
HEADERS			:=	$(INC_DIR)wrapper.h

#		Remove these created files
DELETE			:=	*.out			**/*.out			.DS_Store										\
					**/.DS_Store	.dSYM/				**/.dSYM/

#		Default target
all: $(NAME)

#		Main target
$(NAME): $(WRAP_OBJS)
	@ar rcs $(NAME) $(WRAP_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

#		Compile .c files to .o files
$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

malloc:
	@$(MAKE) $(PRINT_NO_DIR) CFLAGS="$(CFLAGS) -D MALLOC_WRAP=true" all
	
clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME) $(DELETE)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re: fclean all

print-%:
	$(info $($*))

#		Include dependencies
-include $(DEPS)

.PHONY:	all clean fclean re print-%

# ----------------------------------- colors --------------------------------- #
BOLD			=	\033[1m
GREEN			=	\033[32m
MAGENTA			=	\033[35m
CYAN			=	\033[36m
RESET			=	\033[0m

R_MARK_UP		=	$(MAGENTA)$(BOLD)
CA_MARK_UP		=	$(GREEN)$(BOLD)

# ----------------------------------- messages ------------------------------- #
CUR_DIR			:=	$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED			:=	$(R_MARK_UP)REMOVED $(CYAN)%s$(MAGENTA) (%s) $(RESET)\n
CREATED			:=	$(CA_MARK_UP)CREATED $(CYAN)%s$(GREEN) (%s) $(RESET)\n