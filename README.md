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



<details>
<summary>Updating Nested Submodules in parent projects</summary>

This section assumes you have **three separate working trees** on disk:[web:33][web:63]

```sh
1. ft_printf/                          # the ft_printf repository by itself
2. libftx/                             # the libftx repository by itself, containing ft_printf as submodule
3. my_shell_app/                       # your app repository, containing libftx as submodule
```

That means you are **not** doing everything from one folder tree. You update the real child repository first, then go into the parent repository that includes it, and finally into the top-level project that includes that parent.[web:41][web:63][web:70]

Example layout:

```sh
~/code/ft_printf
~/code/libftx
└── src/ft_printf
~/code/my_shell_app
└── extern_library/libftx
    └── src/ft_printf
```

The update order is always:

```sh
ft_printf repo -> libftx repo -> my_shell_app repo
```

## Why this order is required

Git submodules store a **specific commit pointer** in the parent repository. So if `ft_printf` gets a new commit in its own repository, `libftx` still points to the old `ft_printf` commit until you update and commit that pointer inside the `libftx` working tree. Then `my_shell_app` still points to the old `libftx` commit until you update and commit that pointer inside the `my_shell_app` working tree.[web:9][web:12][web:53]

So the process is:

```sh
1. Create or pull the new ft_printf commit in the standalone ft_printf repo.
2. Update libftx so its src/ft_printf submodule points to that new commit.
3. Commit that change in libftx.
4. Update my_shell_app so its extern_library/libftx submodule points to the new libftx commit.
5. Commit that change in my_shell_app.
```

## Step 1 — Update ft_printf in its own repository

First go to the standalone `ft_printf` repository, not the copy nested inside another project.[web:33][web:63]

```sh
cd ~/code/ft_printf
git checkout main
git pull origin main
```

If you made changes locally in `ft_printf`, then commit and push them there first:[web:63][web:70]

```sh
git add .
git commit -m "Improve formatting logic"
git push origin main
```

At this point, `ft_printf` has the new commit that the other repositories must move to.[web:63][web:69]

## Step 2 — Update libftx to point to the new ft_printf commit

Now switch to the standalone `libftx` working tree.[web:33][web:63]

```sh
cd ~/code/libftx
```

Go into its `ft_printf` submodule and move it to the desired commit, usually the latest on `main`.[web:69][web:15]

```sh
cd src/ft_printf
git checkout main
git pull origin main
```

Then go back to the root of `libftx` and commit the updated submodule pointer:[web:12][web:53][web:63]

```sh
cd ../..
git add src/ft_printf
git commit -m "Update ft_printf submodule to latest"
git push origin main
```

Now the `libftx` repository itself has a new commit that points to the new `ft_printf` commit.[web:9][web:53]

## Step 3 — Update my_shell_app to point to the new libftx commit

Now switch to the standalone `my_shell_app` working tree.[web:33][web:63]

```sh
cd ~/code/my_shell_app
```

Go into its `libftx` submodule and pull the new `libftx` commit.[web:69][web:15]

```sh
cd extern_library/libftx
git checkout main
git pull origin main
```

If you also want the nested `ft_printf` inside that checked-out `libftx` tree to match what `libftx` now expects, initialize/update recursively:[web:15][web:1]

```sh
git submodule update --init --recursive
```

Then go back to the root of `my_shell_app` and commit the updated `libftx` pointer:[web:12][web:53][web:63]

```sh
cd ../..
git add extern_library/libftx
git commit -m "Update libftx submodule to latest"
git push origin main
```

Now `my_shell_app` points to the new `libftx` commit, and that `libftx` commit points to the new `ft_printf` commit.[web:9][web:12][web:53]

## Full real-world sequence

```sh
# 1) update ft_printf itself
cd ~/code/ft_printf
git checkout main
git pull origin main
# or make changes:
# git add .
# git commit -m "Improve formatting logic"
# git push origin main

# 2) update libftx to use that new ft_printf commit
cd ~/code/libftx/src/ft_printf
git checkout main
git pull origin main

cd ../..
git add src/ft_printf
git commit -m "Update ft_printf submodule to latest"
git push origin main

# 3) update my_shell_app to use that new libftx commit
cd ~/code/my_shell_app/extern_library/libftx
git checkout main
git pull origin main
git submodule update --init --recursive

cd ../..
git add extern_library/libftx
git commit -m "Update libftx submodule to latest"
git push origin main
```

## Mental model

Think of it like three linked snapshots:[web:9][web:63]

```sh
ft_printf has its own commits
libftx stores "which ft_printf commit to use"
my_shell_app stores "which libftx commit to use"
```

So when `ft_printf` changes, you do **not** update `my_shell_app` directly first. You must first make `libftx` point to the new `ft_printf`, and only then make `my_shell_app` point to the new `libftx`.[web:41][web:53][web:70]

## Short version

If you have three separate folder trees, the 