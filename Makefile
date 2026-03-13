NAME			:=	libftx.a

MAKEFLAGS		+=	-j
COMPILER		:=	cc

BASE_FLAGS		:=	-std=c99 -Wall -Wextra -Werror

PEDANTIC		:=	-Wpedantic -pedantic-errors -Wundef -Wstrict-prototypes
WARNINGS		:=	-Wshadow -Wconversion -Wsign-conversion			\
					-Wformat=2 -Wuninitialized -Wunreachable-code

CAST_WARNINGS	:=	-Wbad-function-cast
ifeq ($(shell $(COMPILER) --version | grep -c "gcc"),1)
CAST_WARNINGS += -Wcast-function-type
endif

DEPFLAGS		:=	-MMD -MP

OPTIMIZATION	:=	-O2
SECURITY		:=	-fstack-protector-strong
ifeq ($(shell uname -s),Linux)
SECURITY		+=	-D_FORTIFY_SOURCE=2
FSANITIZE		:=	leak,
endif

SANITIZERS		:=	-fsanitize=$(FSANITIZE)address,undefined,null,integer-divide-by-zero,signed-integer-overflow,bounds,alignment
DEBUG_FLAGS		:=	-fno-omit-frame-pointer

CFLAGS			:=	$(BASE_FLAGS) $(PEDANTIC) $(WARNINGS) $(CAST_WARNINGS) \
					$(DEPFLAGS) $(OPTIMIZATION) $(SECURITY)

ifneq ($(filter valgrind,$(MAKECMDGOALS)),)
CFLAGS			+=	-g $(DEBUG_FLAGS)
else ifneq ($(filter debug,$(MAKECMDGOALS)),)
CFLAGS			+=	-g3 $(SANITIZERS) $(DEBUG_FLAGS) -fno-sanitize-recover=all
endif

ifneq ($(filter malloc,$(MAKECMDGOALS)),)
CFLAGS			+=	-D MALLOC_WRAP=true
endif

PRINT_NO_DIR	:=	--no-print-directory
RM				:=	rm -rf

# Locking for parallel-safe ar/ranlib
AR_LOCK			:=	.build/ar.lock
AR				:=	flock $(AR_LOCK) ar rcs
RANLIB			:=	flock $(AR_LOCK) ranlib
BUILD			:=	@mkdir -p .build

SRC_DIR			:=	src
INC_DIR			:=	include
BUILD_DIR		:=	.build
PRINTF_DIR		:=	src/printf
GNL_DIR			:=	src/get_next_line
WRAP_DIR		:=	src/wrapper
DYN_DIR			:=	src/dynarr
DBL_DIR			:=	src/dbltoa

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
SEDIT			:=	capitalizations.c			cpy_safe.c						cpy.c					\
					strcpy.c					str_edit.c						swap_values.c
SSRCH			:=	str_len.c					str_compare.c					str_null_check.c		\
					str_search.c				str_search_2.c					find_char.c				\
					find_char_not.c				ptr_null_check.c				skip_characters.c		\
					str_len_comparing.c			str_ctype.c

# Generate source file paths
ALLOC_SRCS		:=	$(addprefix $(SRC_DIR)/alloc_functions/, $(ALLOC))
ARRAY_SRCS		:=	$(addprefix $(SRC_DIR)/arrays_nested/, $(ARRAY))
CNVRT_SRCS		:=	$(addprefix $(SRC_DIR)/conversions/, $(CNVRT))
LLIST_SRCS		:=	$(addprefix $(SRC_DIR)/linked_list/, $(LLIST))
MRKUP_SRCS		:=	$(addprefix $(SRC_DIR)/terminal_markup/, $(MRKUP))
MATH_SRCS		:=	$(addprefix $(SRC_DIR)/math/, $(MATH_))
MEDIT_SRCS		:=	$(addprefix $(SRC_DIR)/memory_edit/, $(MEDIT))
MSRCH_SRCS		:=	$(addprefix $(SRC_DIR)/memory_search/, $(MSRCH))
PTCHR_SRCS		:=	$(addprefix $(SRC_DIR)/put_chars/, $(PTCHR))
SCRTE_SRCS		:=	$(addprefix $(SRC_DIR)/string_create/, $(SCRTE))
SEDIT_SRCS		:=	$(addprefix $(SRC_DIR)/string_edit/, $(SEDIT))
SSRCH_SRCS		:=	$(addprefix $(SRC_DIR)/string_search/, $(SSRCH))

BASE_SRCS		:=	$(ALLOC_SRCS)	$(ARRAY_SRCS)	$(CNVRT_SRCS)	$(LLIST_SRCS)	\
					$(MRKUP_SRCS)	$(MATH_SRCS)	$(MEDIT_SRCS)	$(MSRCH_SRCS)	\
					$(PTCHR_SRCS)	$(SCRTE_SRCS)	$(SEDIT_SRCS)	$(SSRCH_SRCS)

BASE_OBJS		:=	$(BASE_SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(BASE_OBJS:.o=.d)

INCLUDES		:=	-I $(INC_DIR)				\
					-I $(DBL_DIR)/include		\
					-I $(DYN_DIR)/include		\
					-I $(GNL_DIR)/include		\
					-I $(PRINTF_DIR)/include	\
					-I $(WRAP_DIR)/include

# Submodule headers
PRINTF_HEADER	:=	$(PRINTF_DIR)/include/ft_printf.h
GNL_HEADER		:=	$(GNL_DIR)/include/get_next_line.h
WRAP_HEADER		:=	$(WRAP_DIR)/include/wrapper.h
DYNARR_HEADER	:=	$(DYN_DIR)/include/dynarr.h
DBLTOA_HEADER	:=	$(DBL_DIR)/include/dbltoa.h

SUB_HEADERS_SRC	:=	$(PRINTF_HEADER) $(GNL_HEADER) $(WRAP_HEADER) $(DYNARR_HEADER) $(DBLTOA_HEADER)
SUB_HEADERS_DST	:=	$(addprefix $(INC_DIR)/, $(notdir $(SUB_HEADERS_SRC)))

SUBMODULES_CMD	:=																											\
	@if [ ! -e "$(PRINTF_DIR)/.git" ] || [ ! -e "$(GNL_DIR)/.git" ] ||														\
		[ ! -e "$(WRAP_DIR)/.git" ] || [ ! -e "$(DYN_DIR)/.git" ] ||														\
		[ ! -e "$(DBL_DIR)/.git" ]; then																					\
		git submodule update --init --recursive;																			\
		git submodule foreach 'git checkout $$(git config -f $$toplevel/.gitmodules submodule.$$name.branch || echo main)';	\
		git submodule update --remote --merge;																				\
	fi

DELETE			:=	*.out			**/*.out		.DS_Store	\
					**/.DS_Store	.dSYM/			**/.dSYM/

all: submodules $(NAME)			## Build the main library

$(NAME): $(BASE_OBJS) | submodules
	@mkdir -p $(@D)
	$(AR) $@ $(BASE_OBJS)
	$(RANLIB) $@
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(BUILD_DIR)/%.o: %.c | submodules
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

help:							## List all available make targets and their descriptions
	@awk '/^[a-zA-Z_%-]+:.*##/{printf "  %-16s %s\n", $$1, substr($$0, index($$0,"##")+3)}' $(MAKEFILE_LIST)

submodules_init:				## Initialize submodules if needed
	$(SUBMODULES_CMD)

headers: | submodules_init		## Copy submodule headers if changed
	@for hdr in $(SUB_HEADERS_SRC); do \
		dst="$(INC_DIR)/$$(basename $$hdr)"; \
		if [ -f "$$hdr" ] && { [ ! -f "$$dst" ] || ! cmp -s "$$hdr" "$$dst"; }; then \
			cp "$$hdr" "$$dst"; \
			printf "$(COPIED)" "$$dst" "$$hdr"; \
		fi; \
	done

submodules: headers				## Ensure submodules and headers are ready before building components
	$(BUILD)

libftx:							## Build all components (meta-target)
	@$(MAKE) $(PRINT_NO_DIR) all $(filter debug valgrind,$(MAKECMDGOALS))
	@$(MAKE) $(PRINT_NO_DIR) printf $(filter debug valgrind,$(MAKECMDGOALS))
	@$(MAKE) $(PRINT_NO_DIR) gnl $(filter debug valgrind,$(MAKECMDGOALS))
	@$(MAKE) $(PRINT_NO_DIR) mwrap $(filter debug valgrind,$(MAKECMDGOALS))
	@$(MAKE) $(PRINT_NO_DIR) dynarr $(filter debug valgrind,$(MAKECMDGOALS))
	@$(MAKE) $(PRINT_NO_DIR) dbltoa $(filter debug valgrind,$(MAKECMDGOALS))

printf: submodules				## Build printf submodule (depends on submodules)
	@$(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR) COMPILER=$(COMPILER) $(filter debug valgrind,$(MAKECMDGOALS))
	$(AR) $(NAME) $(PRINTF_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

gnl: submodules					## Build get_next_line submodule (depends on submodules)
	@$(MAKE) $(PRINT_NO_DIR) -C $(GNL_DIR) COMPILER=$(COMPILER) $(filter debug valgrind,$(MAKECMDGOALS))
	$(AR) $(NAME) $(GNL_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

wrap: submodules				## Build wrap submodule (depends on submodules)
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) COMPILER=$(COMPILER) $(filter debug valgrind,$(MAKECMDGOALS))
	$(AR) $(NAME) $(WRAP_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

mwrap: submodules				## Build malloc wrapper (depends on submodules)
	@$(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) COMPILER=$(COMPILER) malloc $(firstword $(filter debug valgrind,$(MAKECMDGOALS)) all)
	$(AR) $(NAME) $(WRAP_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

dynarr: submodules				## Build dynarr submodule (depends on submodules)
	@$(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR) COMPILER=$(COMPILER) $(filter debug valgrind,$(MAKECMDGOALS))
	$(AR) $(NAME) $(DYN_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

dbltoa: all						## Build dbltoa submodule (depends on all)
	@$(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) COMPILER=$(COMPILER) CLONE_LIBFTX= submodule $(filter debug valgrind,$(MAKECMDGOALS))
	$(AR) $(NAME) $(DBL_DIR)/.build/src/*.o
	$(RANLIB) $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

clean:							## Remove build artifacts (depends on submodules)
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)/

cleandep:						## Clean dependencies in all submodules
	@[ ! -e "$(GNL_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(GNL_DIR) clean
	@[ ! -e "$(PRINTF_DIR)/.git" ] || $(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR) clean
	@[ ! -e "$(WRAP_DIR)/.git"   ] || $(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) clean
	@[ ! -e "$(DYN_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR) clean
	@[ ! -e "$(DBL_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) clean

fclean: clean					## Full clean including library and submodule headers (depends on clean)
	@$(RM) $(NAME)
	@for hdr in $(SUB_HEADERS_DST); do \
		[ -e "$$hdr" ] && $(RM) "$$hdr" && printf "$(REMOVED)" "$$hdr" "$(CUR_DIR)" || true; \
	done
	@[ ! -e "$(PRINTF_DIR)/.git" ] || $(MAKE) $(PRINT_NO_DIR) -C $(PRINTF_DIR) fclean
	@[ ! -e "$(GNL_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(GNL_DIR) fclean
	@[ ! -e "$(WRAP_DIR)/.git"   ] || $(MAKE) $(PRINT_NO_DIR) -C $(WRAP_DIR) fclean
	@[ ! -e "$(DYN_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(DYN_DIR) fclean
	@[ ! -e "$(DBL_DIR)/.git"    ] || $(MAKE) $(PRINT_NO_DIR) -C $(DBL_DIR) fclean
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:								## Rebuild from scratch (depends on fclean, all)
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) all

valgrind:						## Append to any target for Valgrind checks: make all valgrind

debug:							## Append to any target for sanitizers: make all debug

verify:							## Verify library contents (for debugging)
	@ar t $(NAME) | sort

print-%:						## Print value of a variable
	@$(info $($*))

-include $(DEPS)

.PHONY: all help submodules_init headers submodules	\
		libftx printf gnl wrap mwrap dynarr dbltoa	\
		clean cleandep fclean re					\
		valgrind debug verify print-*

# Terminal markup
BOLD			:=	\033[1m
GREEN			:=	\033[32m
MAGENTA			:=	\033[35m
CYAN			:=	\033[36m
RESET			:=	\033[0m

R_MARK_UP		:=	$(MAGENTA)$(BOLD)
CA_MARK_UP		:=	$(GREEN)$(BOLD)

CUR_DIR			:=	$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED			:=	$(R_MARK_UP)REMOVED $(CYAN)%s$(MAGENTA) (%s) $(RESET)\n
CREATED			:=	$(CA_MARK_UP)CREATED $(CYAN)%s$(GREEN) (%s) $(RESET)\n
COPIED			:=	$(CA_MARK_UP)COPIED $(CYAN)%s$(GREEN) (← %s) $(RESET)\n
