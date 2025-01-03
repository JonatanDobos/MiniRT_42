NAME			=	libft.a

#	Flags
MKDIR_P			=	mkdir -p
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -g
CFLAGS			+=	-Werror
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code


COMPILER		=   cc
CFLAGS			+=	-Wall -Wextra
# Werror cannot go together with fsanitize, because fsanitize won't work correctly.
CFLAGS			+=	-Werror
# CFLAGS			+=	-fsanitize=address
CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code
CFLAGS			+=	-g3
RM				=	rm -rf
MKDIR_P			=	mkdir -p

#	Remove these created files
DELETE			=	*.out							\
					.DS_Store						\
					*.dSYM/

#	Libft source .c files
ALLOC_FUNCTIONS =	calloc.c						\
					deallocation.c					\
					realloc.c

ARRAYS_NESTED	=	2d_array.c						\
					2d_array_utils.c				\
					2d_shrink_array.c 				\
					splitted.c						\
					split.c							\
					split_set.c

ASCII			=	is_ascii.c						\
					is_space.c						\
					to_ascii.c

CONVERSIONS		=	str_to_number.c					\
					str_to_unsigned_number.c		\

GNL				=	get_next_line.c

LINKED_LIST		=	linked_list.c					\
					list_info.c						\
					move_or_remove_nodes.c

MATH			=	find_min_max.c					\
					sign.c							\
					digit_counter.c

MEMORY_EDIT		=	mem_edit.c

MEMORY_SEARCH	=	mem_search.c

PRINTF			=	printf.c						\
					printf_char.c					\
					printf_count.c					\
					printf_flags.c					\
					printf_int.c					\
					printf_sort_spec.c				\
					printf_str_count.c				\
					printf_str.c					\
					printf_unsigned.c				\
					printf_utils.c

PUT_CHARS		=	put_chars_fd.c

STRING_CREATE	=	itoa.c							\
					str_dup.c						\
					string_create.c					\
					strjoin.c						\
					strjoin_set_null.c				\
					strtrim.c

STRING_EDIT		=	cpy_safe.c						\
					cpy.c							\
					str_edit.c						\
					swap_values.c

STRING_SEARCH	=	str_len.c						\
					str_compare.c					\
					str_null_check.c				\
					str_null_and_terminator_check.c	\
					str_search.c					\
					str_search_2.c					\
					find_char.c						\
					find_char_not.c					\
					ptr_null_check.c				\
					skip_characters.c				\
					str_len_comparing.c

#	Directories .c
ALLOC_DIR		=	alloc_functions
ARRAY_DIR		=	arrays_nested
ASCII_DIR		=	ascii
CNVRT_DIR		=	conversions
GNL___DIR		=	get_next_line
LLIST_DIR		=	linked_list
MATH__DIR		=	math
MEDIT_DIR		=	memory_edit
MSRCH_DIR		=	memory_search
PRNTF_DIR		=	printf
PTCHR_DIR		=	put_chars
SCRTE_DIR		=	string_create
SEDIT_DIR		=	string_edit
SSRCH_DIR		=	string_search
DIRS			=	$(ALLOC_DIR) $(ARRAY_DIR) $(ASCII_DIR) $(CNVRT_DIR)	$(GNL___DIR)	\
					$(LLIST_DIR) $(MATH__DIR) $(MEDIT_DIR) $(MSRCH_DIR)	$(PRNTF_DIR)	\
					$(PTCHR_DIR) $(SCRTE_DIR) $(SEDIT_DIR) $(SSRCH_DIR)

#	Directories .o
OBJ_DIR			=	.objects

#	Obj_files
ALLOC_O			=	$(patsubst $(ALLOC_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(ALLOC_DIR)/, $(ALLOC_FUNCTIONS)))
ARRAY_O			=	$(patsubst $(ARRAY_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(ARRAY_DIR)/, $(ARRAYS_NESTED)))
ASCII_O			=	$(patsubst $(ASCII_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(ASCII_DIR)/, $(ASCII)))
CNVRT_O			=	$(patsubst $(CNVRT_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(CNVRT_DIR)/, $(CONVERSIONS)))
GNL___O			=	$(patsubst $(GNL___DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(GNL___DIR)/, $(GNL)))
LLIST_O			=	$(patsubst $(LLIST_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(LLIST_DIR)/, $(LINKED_LIST)))
MATH__O			=	$(patsubst $(MATH__DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(MATH__DIR)/, $(MATH)))
MEDIT_O			=	$(patsubst $(MEDIT_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(MEDIT_DIR)/, $(MEMORY_EDIT)))
MSRCH_O			=	$(patsubst $(MSRCH_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(MSRCH_DIR)/, $(MEMORY_SEARCH)))
PRNTF_O			=	$(patsubst $(PRNTF_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(PRNTF_DIR)/, $(PRINTF)))
PTCHR_O			=	$(patsubst $(PTCHR_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(PTCHR_DIR)/, $(PUT_CHARS)))
SCRTE_O			=	$(patsubst $(SCRTE_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SCRTE_DIR)/, $(STRING_CREATE)))
SEDIT_O			=	$(patsubst $(SEDIT_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SEDIT_DIR)/, $(STRING_EDIT)))
SSRCH_O			=	$(patsubst $(SSRCH_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SSRCH_DIR)/, $(STRING_SEARCH)))
OBJS			=	$(ALLOC_O) $(ARRAY_O) $(ASCII_O) $(CNVRT_O) $(GNL___O)	\
					$(LLIST_O) $(MATH__O) $(MEDIT_O) $(MSRCH_O) $(PRNTF_O)	\
					$(PTCHR_O) $(SCRTE_O) $(SEDIT_O) $(SSRCH_O)

#	Necessary added functions to libraries, I = Included
ISTR_LEN		=	$(SSRCH_O)
I_FREE_STR		=	$(filter $(OBJ_DIR)/deallocation.o, $(ALLOC_O)) $(OBJ_DIR)/deallocation.o
I_STR_EDIT		=	$(filter $(OBJ_DIR)/str_edit.o, $(SEDIT_O)) $(OBJ_DIR)/str_edit.o
I_MEM_EDIT		=	$(filter $(OBJ_DIR)/mem_edit.o, $(MEDIT_O)) $(OBJ_DIR)/mem_edit.o
I_MIN_MAX		=	$(filter $(OBJ_DIR)/find_min_max.o, $(MATH__O)) $(OBJ_DIR)/find_min_max.o
I_PUTCHAR		=	$(filter $(OBJ_DIR)/put_chars_fd.o, $(PTCHR_O)) $(OBJ_DIR)/put_chars_fd.o
I_FIND			=	$(filter $(OBJ_DIR)/find_char.o, $(SSRCH_O)) $(OBJ_DIR)/find_char.o
I_FIND_NOT		=	$(filter $(OBJ_DIR)/find_char_not.o, $(SSRCH_O)) $(OBJ_DIR)/find_char_not.o
I_COPY			=	$(I_FIND)																		\
					$(filter $(OBJ_DIR)/cpy.o, $(SEDIT_O)) $(OBJ_DIR)/cpy.o
IFT_STRDUP		=	$(I_STR_EDIT) $(ISTR_LEN) $(I_FREE_STR)											\
					$(filter $(OBJ_DIR)/str_dup.o, $(ALLOC_O)) $(OBJ_DIR)/str_dup.o

I_ALLOC_O		=	$(I_FREE_STR) $(I_MIN_MAX) $(I_MEM_EDIT)
I_ARRAY_O		=	$(IFT_STRDUP) $(I_PUTCHAR) $(IPRINTF_O)
IGNL___O		=	$(ISTR_LEN)	$(I_FREE_STR)
IPRINTF_O		=	$(ISTR_LEN)	$(I_COPY)
ICREATE_O		=	$(ISTR_LEN)	$(I_FREE_STR) $(IFT_STRDUP)
ISTR_ED_O		=	$(ISTR_LEN)

ISEARCH_O		=	$(ISTR_LEN)

# Macro to handle adding to the archive and printing messages
define add_to_archive
	@if [ -f $(NAME) ]; then \
		NEEDS_UPDATE=false; \
		for obj in $(1); do \
			if [ $$obj -nt $(NAME) ]; then \
				NEEDS_UPDATE=true; \
				break; \
			fi; \
		done; \
		if [ $$NEEDS_UPDATE = true ]; then \
			ar rcs $(NAME) $(1); \
			printf "$(ADDED)" $(2) $(NAME); \
		fi; \
	else \
		ar rcs $(NAME) $(1); \
		printf "$(CREATED)" $(NAME) $(CUR_DIR); \
	fi
endef

all:	objects_mkdir $(NAME)

#	Main target: dependency
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

#	Object targets: dependencies
$(OBJ_DIR)/%.o: $(ALLOC_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ARRAY_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ASCII_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CNVRT_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL___DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LLIST_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MATH__DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MEDIT_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MSRCH_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PRNTF_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PTCHR_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SCRTE_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SEDIT_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SSRCH_DIR)/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

#	instruction targets: dependencies
alloc: objects_mkdir $(ALLOC_O) $(I_ALLOC_O)
	$(call add_to_archive, $(ALLOC_O) $(I_ALLOC_O), $(ALLOC_DIR))

array: objects_mkdir $(ARRAY_O) $(I_ARRAY_O)
	$(call add_to_archive, $(ARRAY_O) $(I_ARRAY_O), $(ARRAY_DIR))

ascii: objects_mkdir $(ASCII_O)
	$(call add_to_archive, $(ASCII_O), $(ASCII_DIR))

convert: objects_mkdir $(CNVRT_O)
	$(call add_to_archive, $(CNVRT_O), $(CNVRT_DIR))

gnl: objects_mkdir $(GNL___O) $(IGNL___O)
	$(call add_to_archive, $(GNL___O) $(IGNL___O), $(GNL___DIR))

list: objects_mkdir $(LLIST_O)
	$(call add_to_archive, $(LLIST_O), $(LLIST_DIR))

math: objects_mkdir $(MATH__O)
	$(call add_to_archive, $(MATH__O), $(MATH__DIR))

medit: objects_mkdir $(MEDIT_O)
	$(call add_to_archive, $(MEDIT_O), $(MEDIT_DIR))

msearch: objects_mkdir $(MSRCH_O)
	$(call add_to_archive, $(MSRCH_O), $(MSRCH_DIR))

printf: objects_mkdir $(PRNTF_O) $(IPRINTF_O)
	$(call add_to_archive, $(PRNTF_O) $(IPRINTF_O), $(PRNTF_DIR))

putchar: objects_mkdir $(PTCHR_O)
	$(call add_to_archive, $(PTCHR_O), $(PTCHR_DIR))

screate: objects_mkdir $(SCRTE_O) $(ICREATE_O)
	$(call add_to_archive, $(SCRTE_O) $(ICREATE_O), $(SCRTE_DIR))

sedit: objects_mkdir $(SEDIT_O) $(ISTR_ED_O)
	$(call add_to_archive, $(SEDIT_O) $(ISTR_ED_O), $(SEDIT_DIR))

ssearch: objects_mkdir $(SSRCH_O) $(ISEARCH_O)
	$(call add_to_archive, $(SSRCH_O) $(ISEARCH_O), $(SSRCH_DIR))

objects_mkdir:
	@$(MKDIR_P) $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR) $(DELETE)
	@printf "$(REMOVED)" $(OBJ_DIR)/ $(CUR_DIR)$(OBJ_DIR)/

no_print_clean:
	@$(RM) $(BUILD_DIR) $(DELETE)

fclean:				clean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

no_print_fclean:	no_print_clean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:		fclean all

f:		all

.PHONY:	all alloc array ascii convert gnl list math medit msearch printf putchar	\
		screate sedit ssearch objects_mkdir clean fclean re f

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
ADDED := $(CA_MARK_UP)ADDED $(CYAN)%s$(GREEN) to $(CYAN)%s $(RESET)\n