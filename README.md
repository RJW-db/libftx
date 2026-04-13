# libftx
**libftx** is a *modular* C library extending the classic **Libft** project from the **42 / Codam** curriculum. Originally a *personal continuation* of **libft**, it now incorporates additional modules for *flexible, modern* C development built as a learning project to master **advanced Git workflows** (submodules), **GitHub Actions** **CI/CD**, and robust **DevOps** practices in a real-world C library.

At its core, **libftx** provides the *foundational functions* from the original **libft** (standard library reimplementations + utilities). On top of that, it integrates several *core projects and self-developed submodules*:


- [**ft_printf**](https://github.com/RJW-db/printf): A reimplementation of the standard `printf()` function with extended formatting and custom output handlers.
- [**get_next_line**](https://github.com/RJW-db/get_next_line): Line-by-line reader for file descriptors (with bonus support for multiple fds, if enabled).
- [**dynarr**](https://github.com/RJW-db/dynarr): A dynamic array implementation for safe and efficient data management in C.
- [**dbltoa**](https://github.com/RJW-db/dbltoa): A floating-point to ASCII conversion module designed for lightweight number formatting.
- [**wrapper**](https://github.com/RJW-db/wrapper): A set of function wrappers and helpers to simplify common libc usage and improve error handling.

All components compile together into a single static library called **libftx.a**, which can be linked to any C project.

The library follows **42’s** conventions but includes a few practical deviations for real-world use (modular builds, optional hardening flags, and submodule-based components).


## Table of Contents
- [Usage](#usage)
  - [Integration](#integration)
- [Libft](#libft)
- [Libftx Extensions](#libftx-extensions)
- [Submodules](#submodules)
  - [ft_printf](https://github.com/RJW-db/printf)
  - [get_next_line](https://github.com/RJW-db/get_next_line)
  - [wrapper](https://github.com/RJW-db/wrapper)
  - [dynarr](https://github.com/RJW-db/dynarr)
  - [dbltoa](https://github.com/RJW-db/dbltoa)

## Usage
**libftx** uses parallel builds (`-j`), full 42 flags + security hardening, and auto-submodule management.

> **Note for macOS users:**
> By default, macOS does **not** include the `flock` utility required for safe parallel builds. To build in parallel, first install `flock` (e.g., with `brew install flock`).
> Otherwise, run `make -j1` to disable parallelism and avoid build errors.

### Build Targets
| Command | Arguments | Functionality |
|---------|-----------|---------------|
| `make` | `all` / *(none)* | Builds **libftx.a** (core functions only) |
| `make` | `libftx` | **Full build**: core + all submodules |
| `make` | `ft_printf` | Builds ft_printf submodule |
| `make` | `get_next_line` | Builds get_next_line submodule |
| `make` | `wrap` | Wrapper (malloc wrap **OFF**) |
| `make` | `mwrap` | Wrapper (malloc wrap **ON**) |
| `make` | `dynarr` | Builds dynarr submodule |
| `make` | `dbltoa` | Builds dbltoa submodule |


### Debug Modes (pair with build targets)
Pair with **any build target**. Example: `make libftx debug`
| Command | Example | Flags |
|---------|---------|-------|
| `valgrind` | `make libftx valgrind` | Debug symbols + frame pointers |
| `debug` | `make mwrap debug` | Sanitizers + max debug info |

### Management
| Command | Functionality |
|---------|---------------|
| `submodules` | Ensures submodules + headers ready |
| `submodules_init` | Initializes git submodules |
| `headers` | Copies submodule headers to `include/` |
| `verify` | Lists `libftx.a` content object files |
| `help` | Shows all targets |


### Clean Targets
| Command | Functionality |
|---------|---------------|
| `clean` | Removes `.build/` artifacts |
| `cleandep` | Cleans submodules dependencies |
| `fclean` | **Full clean**: library + headers + submodules |
| `re` | Rebuild from scratch |


<details>
<summary>Build combinations (Click to expand)</summary>

`debug` must always be paired with a build target, it only appends flags, it does not build on its own.

```sh
make libftx debug           # full build + sanitizers + debug symbols
make printf valgrind        # ft_printf only + debug flags
make mwrap gnl valgrind     # malloc wrapper + get_next_line + debug flags
make dbltoa dynarr debug    # dbltoa + dynarr + sanitizers
```

</details>


### Integration
Build and link the static library:
```sh
cc -I include main.c libftx.a -o demo
```



## Libft
**Core foundation** reimplementing **42 Libft**: 100% mandatory + bonus.  
Organized by category: alloc, arrays, conversions, lists, math, memory, strings.

<details>
<summary>Full Functions + 42 Rules (Click to expand)</summary>

### Part 1: Libc Functions (22)
`isalpha, isdigit, isalnum, isascii, isprint, strlen, memset, bzero, memcpy, memmove, strlcpy, strlcat, toupper, tolower, strchr, strrchr, strncmp, memchr, memcmp, strnstr, atoi, calloc, strdup`

### Part 2: Additional (11)
`ft_substr, ft_strjoin, ft_strtrim, ft_split, ft_itoa, ft_strmapi, ft_striteri, ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd`

### Part 3: Bonus Lists (10)
```
typedef struct s_list {
  void *content;
  struct s_list *next;
} t_list;
```

ft_lstnew, ft_lstadd_front, ft_lstsize, ft_lstlast, ft_lstadd_back, ft_lstdelone, ft_lstclear, ft_lstiter, ft_lstmap


### 42 Compliance
- **Norminette**: All files pass (bonus files included, 0 if norm error)
- **Stability**: No segfault/bus error/double free (except undefined behavior)
- **Memory**: All heap allocations properly freed (no leaks tolerated)
- **Makefile**: `$(NAME), all, clean, fclean, re` with `-Wall -Wextra -Werror`, no unnecessary relinking
- **Bonus**: Separate `_bonus.c/h` files + `bonus` rule (evaluated separately)

</details>

## Libftx Extensions
Custom extensions and advanced utilities built on top of Libft.

<details>
<summary>Custom Extensions (Click to expand)</summary>

#### Array/2D Array Utilities
`count_arr_2d, add_str_arr, print_2d_array, cpy_2d_array, expand_2d_array, free_2d_arr, search_rm_2d_arr, find_rm_2d_arr, find_rm_all_2d_arr, split_set, splitted`

#### String Creation
`itoa_base, int64_base, nbr_to_str, nbr_to_buff, int_to_str, strdup_safe, strdup_len, strdup_len_free, strdup_size_free, strjoin_free_s1_n, strjoin_free_s2_n, strjoin_free_all_n, strjoin_free_s1, strjoin_free_s2, strjoin_free_all, strjoin_parts`

#### String Edit/Copy
`to_lower, to_upper, str_decapitalize, str_capitalize, cpy_str, cpy_str0, cpy_srcs, cpy_num, cpy_num_char, cpy_till_char, cpy_till_char_s, swap_ptr`

#### String Search/Compare/Length
`find_set_not, find_char_not, find_char2_not, find_char3_not, find_set, find_char, find_char2, find_char3, dp_ptr_ok, skip_alpha, skip_digits, skip_signed_digits, skip_spaces, strncmp_safe, str_check_all, smallest_str, biggest_str, smallest_str_len, biggest_str_len, strlen_safe, strlen_chr, strlen_set, strs_ok, dpstr_ok, dpstrs_ok, c_in_str, strcmp0, strlmatch`

#### String to Number Conversion
`atoi32, atoi64, atui64, atoi_base`

#### Math Utilities
`digit_counter, digit_ucounter, sign_i, sign_d, abs_int64`

#### Terminal Markup Utilities
`markup, print_full_width`

</details>

## Submodules
<details>
<summary>Developer: Add/Update Submodules (Click to expand)</summary>

### Add single submodule
Adding a submodule
```sh
git submodule add <repository-url> <path/to/submodule>
git submodule update --init --recursive
git commit -m "add new submodule"
```

### Update single submodule

```sh
git submodule update --remote --merge src/dbltoa
git add src/dbltoa
git commit -m "update dbltoa submodule to latest"
git push
```

### Update submodules
```sh
git submodule update --remote --merge
git add -A
git commit -m "update submodules"
git push
```
</details>
