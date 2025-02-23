NAME			:=	lib.a
# COMPILER		:=	cc
COMPILER		:=	gcc
RM				:=	rm -rf
PRINT_NO_DIR	:=	--no-print-directory

#		Compiler flags
CFLAGS			+=	-MMD -MP
# CFLAGS			+=	-Wall -Wextra
# # Werror cannot go together with fsanitize, because fsanitize won't work correctly.
# CFLAGS			+=	-Werror
CFLAGS			+=	-g
# CFLAGS			+=	-fsanitize=address
# CFLAGS			+=	-Wunused -Wuninitialized -Wunreachable-code
# OFLAGS are optimization flags that might have been passed from the parent Makefile.
CFLAGS			+=	$(OFLAGS)

ifeq ($(MAKECMDGOALS),malloc_wrap)
	CFLAGS	+= -D MALLOC_WRAP=true
	CFLAGS := $(filter-out -Ofast, $(CFLAGS))
	CFLAGS := $(filter-out -O3, $(CFLAGS))
	ifeq ($(shell uname -s),Linux)
		WRAP_MALLOC	:= -Wl,--wrap=malloc
	endif
endif

#		Build directory for objects and dependencies
BUILD_DIR		:=	.build/
INC_DIR			:=	include/
TESTER_DIR		:=	tester/


#		Source Directory
SRC_DIR			:=	src/

#		Source files by category
ALLOC			:=	calloc.c					deallocation.c					realloc.c
ARRAY			:=	2d_array.c					2d_array_utils.c				2d_shrink_array.c		\
					splitted.c					split.c							split_set.c
CNVRT			:=	str_to_number.c
DYNAR			:=	dynarr.c					dynarr_insert.c
G_N_L			:=	get_next_line.c				get_input_buff.c
LLIST			:=	linked_list.c				list_info.c						move_or_remove_nodes.c
MRKUP			:=	markup.c
MATH_			:=	sign.c						digit_counter.c
MEDIT			:=	mem_edit.c
MSRCH			:=	mem_search.c
FWRAP			:=	dynamic_symbols.c			linux_malloc_wrapper.c			mac_malloc_wrapper.c	\
					malloc_handlers.c			open_wrapper.c
PRNTF			:=	printf.c					printf_process_format.c			printf_char.c			\
					printf_count.c				printf_flags.c					printf_int.c			\
					printf_sort_spec.c			printf_str_count.c				printf_str.c			\
					printf_unsigned.c			printf_utils.c
PTCHR			:=	put_chars_fd.c
SCRTE			:=	itoa.c						str_dup.c						string_create.c			\
					strjoin.c					strjoin_set_null.c				strtrim.c
SEDIT			:=	cpy_safe.c					cpy.c str_edit.c				swap_values.c
SSRCH			:=	str_len.c					str_compare.c					str_null_check.c		\
					str_search.c				str_search_2.c					find_char.c				\
					find_char_not.c				ptr_null_check.c				skip_characters.c		\
 					str_len_comparing.c

#		Map prefixes to their directories
SRCS			:=	$(addprefix $(SRC_DIR)alloc_functions/, $(ALLOC)) 									\
					$(addprefix $(SRC_DIR)arrays_nested/, $(ARRAY)) 									\
					$(addprefix $(SRC_DIR)conversions/, $(CNVRT))										\
					$(addprefix $(SRC_DIR)dynamic_array/, $(DYNAR)) 									\
					$(addprefix $(SRC_DIR)get_next_line/, $(G_N_L)) 									\
					$(addprefix $(SRC_DIR)linked_list/, $(LLIST))										\
					$(addprefix $(SRC_DIR)terminal_markup/, $(MRKUP))									\
					$(addprefix $(SRC_DIR)math/, $(MATH_))							 					\
					$(addprefix $(SRC_DIR)memory_edit/, $(MEDIT)) 										\
					$(addprefix $(SRC_DIR)memory_search/, $(MSRCH))										\
					$(addprefix $(SRC_DIR)wrap_functions/, $(FWRAP))									\
					$(addprefix $(SRC_DIR)printf/, $(PRNTF)) 											\
					$(addprefix $(SRC_DIR)put_chars/, $(PTCHR))											\
					$(addprefix $(SRC_DIR)string_create/, $(SCRTE))										\
					$(addprefix $(SRC_DIR)string_edit/, $(SEDIT)) 										\
					$(addprefix $(SRC_DIR)string_search/, $(SSRCH))

#		Generate object file names
OBJS			:=	$(SRCS:%.c=$(BUILD_DIR)%.o)
#		Generate Dependency files
DEPS			:=	$(OBJS:.o=.d)
#		Header files
HEADERS_FILES	:=	libft.h						common_defs.h					ft_printf.h				\
					dynarr.h					is_ctype1.h						is_ctype2.h				\
					validate_ptr.h				terminal_markup.h				wrap_functions.h
HEADERS			:=	$(addprefix $(INC_DIR), $(HEADERS_FILES))

#		Remove these created files
DELETE			:=	*.out																				\
					.DS_Store																			\
					*.dSYM/

#		Default target
all: $(NAME)

#		Main target
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(CREATED)" $@ $(CUR_DIR)

#		Compile .c files to .o files
$(BUILD_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

#	For linux, -Wl,--wrap=malloc, add this where you create your program
malloc_wrap:	all

tester:
	@if [ ! -d "$(TESTER_DIR)" ]; then \
		git clone git@github.com:RJW-db/lib_tester.git tester; \
	fi

test:	tester
	@$(MAKE) $(PRINT_NO_DIR) -C $(TESTER_DIR) run

test_valgrind:	tester
	@$(MAKE) $(PRINT_NO_DIR) -C $(TESTER_DIR) valgrind

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

clean_tester:
	@$(RM) $(TESTER_DIR)

re: fclean all

print-%:
	$(info $($*))

#		Include dependencies
-include $(DEPS)

.PHONY: all malloc_wrap tester test clean no_print_clean fclean no_print_fclean clean_tester re print-%

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