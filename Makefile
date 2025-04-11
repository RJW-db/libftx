NAME			:=	lib.a

#		Compile with every thread available
#		Get the number of logical processors (threads)
N_JOBS			:=	$(shell nproc)
#		(-j) Specify the number of jobs (commands) to run simultaneously
MULTI_THREADED	:=	-j$(N_JOBS)
#		MAKEFLAGS is a special variable that automatically applies the specified options (e.g., parallel execution)
#		to the current `Makefile` and all `make` invocations, including sub-make processes in subfolders.
#		By setting `-j$(N_JOBS)` here, both this `Makefile` and all sub-make processes will inherit the
#		multithreading configuration without requiring explicit passing.
MAKEFLAGS		+=	$(MULTI_THREADED)

#	Compiler and Flags
COMPILER		:=	gcc
CFLAGS			+=	-Wall -Wextra
CFLAGS			+=	-Werror
CFLAGS			+=	-Wunreachable-code -Wpedantic -Wconversion -Wshadow
CFLAGS			+=	-MMD -MP
# CFLAGS			+=	-g
#	Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-fsanitize=address

#	Utilities
PRINT_NO_DIR	:=	--no-print-directory
RM				:=	rm -rf

#		Base Directories
SRC_DIR			:=	src/
INC_DIR			:=	include/
BUILD_DIR		:=	.build/
DBL_DIR			:=	src/dbltoa/
DYN_DIR			:=	src/dynarr/
PRINTF_DIR		:=	src/printf/
WRAP_DIR		:=	src/wrapper/
TESTER_DIR		:=	tester/

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
WRAP			:=	linux_malloc_wrapper.c		mac_malloc_wrapper.c			malloc_handlers.c		\
					open_wrapper.c				wrap_utils.c

#		Map prefixes to their directories
#		Base sources
ALLOC_SRCS		:=	$(addprefix $(SRC_DIR)alloc_functions/, $(ALLOC))
ARRAY_SRCS		:=	$(addprefix $(SRC_DIR)arrays_nested/, $(ARRAY))
CNVRT_SRCS		:=	$(addprefix $(SRC_DIR)conversions/, $(CNVRT))
G_N_L_SRCS		:=	$(addprefix $(SRC_DIR)get_next_line/, $(G_N_L))
MRKUP_SRCS		:=	$(addprefix $(SRC_DIR)terminal_markup/, $(MRKUP))
MATH_SRCS		:=	$(addprefix $(SRC_DIR)math/, $(MATH_))
MEDIT_SRCS		:=	$(addprefix $(SRC_DIR)memory_edit/, $(MEDIT))
MSRCH_SRCS		:=	$(addprefix $(SRC_DIR)memory_search/, $(MSRCH))
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
DBL_OBJS		:=	$(patsubst %.c, %.o, $(addprefix $(DBL_DIR)$(BUILD_DIR)$(SRC_DIR), $(DBTOA)))
DYN_OBJS		:=	$(patsubst %.c, %.o, $(addprefix $(DYN_DIR)$(BUILD_DIR)$(SRC_DIR), $(DYNAR)))
PRT_OBJS		:=	$(patsubst %.c, %.o, $(addprefix $(PRINTF_DIR)$(BUILD_DIR)$(SRC_DIR), $(PRNTF)))
WRP_OBJS		:=	$(patsubst %.c, %.o, $(addprefix $(WRAP_DIR)$(BUILD_DIR)$(SRC_DIR), $(WRAP)))

#		All objects combined
ALL_OBJS		:=	$(BASE_OBJS) $(DBL_OBJS) $(DYN_OBJS) $(PRT_OBJS) $(LLT_OBJS)

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
$(NAME): $(BASE_OBJS)
	@ar rcs $(NAME) $(BASE_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

dbltoa_submodule:
	@git submodule update --init $(DBL_DIR)
	git submodule update --remote $(DBL_DIR)

dyn_submodule:
	@git submodule update --init $(DYN_DIR)
	git submodule update --remote $(DYN_DIR)

printf_submodule:
	@git submodule update --init $(PRINTF_DIR)
	git submodule update --remote $(PRINTF_DIR)

wrap_submodule:
	@git submodule update --init $(WRAP_DIR)
	git submodule update --remote $(WRAP_DIR)

all_submodules:
    @git submodule update --init --recursive
    @git submodule update --remote
#		If you made changes in submodule and restoring it.
#	cd src/dbltoa
#	git restore .
#	git reset --hard

base: $(BASE_OBJS)
	@ar rcs $(NAME) $(BASE_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

llist: $(LLT_OBJS)
	@ar rcs $(NAME) $(LLT_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

dbltoa:	dbltoa_submodule base
	@$(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) standalone
	@ar rcs $(NAME) $(DBL_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

dynarr:	dyn_submodule
	@$(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR)
	@ar rcs $(NAME) $(DYN_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

printf: printf_submodule
	@$(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR)
	@ar rcs $(NAME) $(PRT_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

wrap: wrap_submodule
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR)
	@ar rcs $(NAME) $(WRP_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

mwrap: wrap_submodule
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) malloc
	@ar rcs $(NAME) $(WRP_OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

clone_tester:
	@if [ ! -d "$(TESTER_DIR)" ]; then \
		git clone git@github.com:RJW-db/lib_tester.git tester; \
	fi

test:	all_submodules base clone_tester mwrap dbltoa dynarr printf all
	@$(MAKE) $(PRINT_NO_DIR) -C $(TESTER_DIR) run

test_valgrind:	all_submodules base clone_tester mwrap dbltoa dynarr printf all
	@$(MAKE) $(PRINT_NO_DIR) -C $(TESTER_DIR) valgrind

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@$(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) clean
	@$(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR) clean
	@$(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR) clean
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) clean
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

no_print_clean:
	@$(RM) $(BUILD_DIR) $(DELETE)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) fclean
	@$(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR) fclean
	@$(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR) fclean
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) fclean
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

clean_tester:
	@$(RM) $(TESTER_DIR)

allclean: fclean clean_tester

no_print_fclean:	no_print_clean
	@$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re: fclean all

print-%:
	$(info $($*))

#		Include dependencies
-include $(DEPS)

.PHONY: all init_submodules submodules_update submodules base llist dbltoa dynarr	\
		printf wrap mwrap clone_tester test test_valgrind clean no_print_clean		\
		fclean no_print_fclean clean_tester allclean re print-%

.NOTPARALLEL: init_submodules submodules_update submodules
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