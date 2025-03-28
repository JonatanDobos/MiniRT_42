NAME			:=	libft.a
# COMPILER		:=	cc
COMPILER		:=	gcc
RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

#		Compile with every thread available
#		Get the number of logical processors (threads)
N_JOBS			:=	$(shell nproc)

#		(-j) Specify the number of jobs (commands) to run simultaneously
MULTI_THREADED	:=	-j $(N_JOBS)
#		MAKEFLAGS will automatically apply the specified options (e.g., parallel execution) when 'make' is invoked
MAKEFLAGS		+=	$(MULTI_THREADED)

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
ALLOC			:=	calloc.c					deallocation.c					realloc.c
ARRAY			:=	2d_array.c					2d_array_utils.c				2d_shrink_array.c		\
					splitted.c					split.c							split_set.c
CNVRT			:=	str_to_number.c				str_to_number_base.c
G_N_L			:=	get_next_line.c				get_input_buff.c
LLIST			:=	linked_list.c				list_info.c						move_or_remove_nodes.c
MRKUP			:=	markup.c
MATH_			:=	math_utils.c				digit_counter.c
MEDIT			:=	mem_edit.c
MSRCH			:=	mem_search.c
PTCHR			:=	put_chars_fd.c
SCRTE			:=	itoa.c						itoa_base.c						str_dup.c				\
					string_create.c				strjoin.c						strjoin_set_null.c		\
					strtrim.c
SEDIT			:=	cpy_safe.c					cpy.c							strcpy.c				\
					str_edit.c					swap_values.c
SSRCH			:=	str_len.c					str_compare.c					str_null_check.c		\
					str_search.c				str_search_2.c					find_char.c				\
					find_char_not.c				ptr_null_check.c				skip_characters.c		\
 					str_len_comparing.c
DBTOA			:=	dbltoa.c					fraction_conversion.c			fraction_operations.c	\
					ft_binary_to_decimal.c		scientific_notation.c			double_to_string.c		\
					precision_process.c			precision_set.c					utils_dbl.c				\
					ft_addition.c				ft_subtraction.c				ft_multiply.c			\
					ft_division.c
DYNAR			:=	dynarr.c					dynarr_insert.c					dynarr_utils.c
PRNTF			:=	printf.c					printf_process_format.c			printf_char.c			\
					printf_count.c				printf_flags.c					printf_int.c			\
					printf_sort_spec.c			printf_str_count.c				printf_str.c			\
					printf_unsigned.c			printf_utils.c

#		Map prefixes to their directories
#		Base sources
ALLOC_SRCS		:=	$(addprefix $(SRC_DIR)alloc_functions/, $(ALLOC))
ARRAY_SRCS		:=	$(addprefix $(SRC_DIR)arrays_nested/, $(ARRAY))
CNVRT_SRCS		:=	$(addprefix $(SRC_DIR)conversions/, $(CNVRT))
DBL_SRCS		:=	$(addprefix $(SRC_DIR)dbltoa/, $(DBTOA))
DYN_SRCS		:=	$(addprefix $(SRC_DIR)dynarr/, $(DYNAR))
G_N_L_SRCS		:=	$(addprefix $(SRC_DIR)get_next_line/, $(G_N_L))
MRKUP_SRCS		:=	$(addprefix $(SRC_DIR)terminal_markup/, $(MRKUP))
MATH_SRCS		:=	$(addprefix $(SRC_DIR)math/, $(MATH_))
MEDIT_SRCS		:=	$(addprefix $(SRC_DIR)memory_edit/, $(MEDIT))
MSRCH_SRCS		:=	$(addprefix $(SRC_DIR)memory_search/, $(MSRCH))
PRINTF_SRCS		:=	$(addprefix $(SRC_DIR)printf/, $(PRNTF))
PTCHR_SRCS		:=	$(addprefix $(SRC_DIR)put_chars/, $(PTCHR))
SCRTE_SRCS		:=	$(addprefix $(SRC_DIR)string_create/, $(SCRTE))
SEDIT_SRCS		:=	$(addprefix $(SRC_DIR)string_edit/, $(SEDIT))
SSRCH_SRCS		:=	$(addprefix $(SRC_DIR)string_search/, $(SSRCH))

BASE_SRCS		:=	$(ALLOC_SRCS)	$(ARRAY_SRCS)	$(CNVRT_SRCS)	$(G_N_L_SRCS)	$(MRKUP_SRCS)		\
					$(MATH_SRCS)	$(MEDIT_SRCS)	$(MSRCH_SRCS)	$(PTCHR_SRCS)	$(SCRTE_SRCS)		\
					$(SEDIT_SRCS)	$(SSRCH_SRCS)

#		Generate object file names
BASE_OBJS		:=	$(BASE_SRCS:%.c=$(BUILD_DIR)%.o)
LLT_OBJS		:=	$(LLT_SRCS:%.c=$(BUILD_DIR)%.o)
DBL_OBJS		:=	$(DBL_SRCS:%.c=$(BUILD_DIR)%.o)
DYN_OBJS		:=	$(DYN_SRCS:%.c=$(BUILD_DIR)%.o)
PRT_OBJS		:=	$(PRINTF_SRCS:%.c=$(BUILD_DIR)%.o)

#		All objects combined
ALL_OBJS		:=	$(BASE_OBJS) $(DBL_OBJS) $(DYN_OBJS) $(PRT_OBJS)

#		Generate Dependency files
DEPS			:=	$(ALL_OBJS:.o=.d)

#		Header files
HEADERS_FILES	:=	libft.h						common_defs.h					ft_printf.h				\
					dbltoa.h					dynarr.h						is_ctype1.h				\
					is_ctype2.h					validate_ptr.h					terminal_markup.h		\
					wrapper.h

HEADERS			:=	$(addprefix $(INC_DIR), $(HEADERS_FILES))

#		Remove these created files
DELETE			:=	*.out			**/*.out			.DS_Store										\
					**/.DS_Store	.dSYM/				**/.dSYM/

#		Default target
all: $(NAME)

#		Main target
$(NAME): $(ALL_OBJS)
	@ar rcs $(NAME) $(ALL_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

no_print_clean:
	@$(RM) $(BUILD_DIR) $(DELETE)

fclean: clean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

no_print_fclean:	no_print_clean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re: fclean all

print-%:
	$(info $($*))

#		Include dependencies
-include $(DEPS)

.PHONY: all clean no_print_clean fclean no_print_fclean re print-%

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