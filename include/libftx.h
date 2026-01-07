/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftx.hy                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/05/09 15:57:54 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTX_H
# define LIBFTX_H

/*
	BUFF_SIZE minimum is 1, don't go lower than that.
	cc -D BUFF_SIZE=42 <files>.c
*/
# ifndef BUFF_SIZE
#  define BUFF_SIZE 10240
# endif
# ifndef KILOBYTE
#  define KILOBYTE 1024
# endif

# if defined(__APPLE__) || defined(__MACH__)
#  include <limits.h>
#  define MAX_FD OPEN_MAX
# elif defined(__linux__) || defined(__FreeBSD__)
#  define MAX_FD 1024
# elif defined(_WIN32)
#  define MAX_FD 512
# else
#  define MAX_FD 256
# endif

//	'\0'
# define TERM 1

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>			//	int32, uint32
# include <unistd.h>			//	ssize_t STDOUT_FILENO
# if defined(__linux__)
#  include <linux/limits.h>
# endif

# include <is_ctype1.h>
# include <is_ctype2.h>
# include <safe_write.h>
# include <validate_ptr.h>

enum	e_return
{
	ERROR = -1,
	SUCCESS,
	FAILURE
};

typedef struct s_list		t_lst;

struct s_list
{
	void			*content;
	struct s_list	*next;
};

//	Alloc Functions
void		*free_ptr(void **ptr);
void		*free_str(char **str);
void		*ft_realloc(void **ptr, size_t new_size, size_t old_size);
void		*ft_calloc(size_t nmemb, size_t size);

//	Nested Arrays Functions
size_t		count_arr_2d(char **arr);
char		**cpy_2d_array(char **arr);
char		**expand_2d_array(char ***arr, size_t add_rows);
char		**add_str_arr(char **arr, const char *str);
char		**search_rm_2d_arr(char **arr, const char *rm);
char		**find_rm_2d_arr(char ***arr, const char *rm);
char		**find_rm_all_2d_arr(char ***arr, const char *rm);
void		free_2d_arr(char ***arr);
void		print_2d_array(char **arr);
char		**splitted(char const *s, char c);
char		**split(char const *s, char c);
char		**split_set(const char *s, const char *set);

//	Conversions Functions
int32_t		atoi32(const char *nptr);
int64_t		atoi64(const char *nptr);
int64_t		atoi_base(const char *nbr_str, const char *base, bool *is_neg);
uint64_t	atui64(const char *nptr);

//	Linked List Functions
void		ft_lstadd_back(t_lst **lst, t_lst *new);
void		ft_lstadd_front(t_lst **lst, t_lst *new);
void		ft_lstclear(t_lst **lst, void (*del)(void*));
void		ft_lstdelone(t_lst *lst, void (*del)(void*));
void		ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst		*ft_lstlast(t_lst *lst);
t_lst		*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *));
t_lst		*ft_lstnew(void *content);
int			ft_lstsize(t_lst *lst);

//	Math Functions
int8_t		sign_i(int n);
int8_t		sign_d(double n);
uint64_t	abs_int64(int64_t n);
uint8_t		digit_counter(int64_t n, uint8_t base_len);
uint8_t		digit_ucounter(uint64_t n, uint8_t base_len);

//	Memory Edits Functions
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
bool		swap_values(void *a, void *b, size_t size);

//	Memory Search Functions
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

//	Putchars Functions
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr_nl_fd(int n, int fd);
void		ft_putstr_fd(const char *s, int fd);

//	String Create Functions
char		*ft_itoa(int n);
char		*nbr_to_str(int64_t n);
char		*itoa_base(int64_t n, const char *base);
char		*int_to_str(char *dst, uint8_t len, int64_t n, const char *base);

char		*ft_strdup(const char *s);
char		*strdup_safe(const char *s);
char		*strdup_len(const char *s, size_t size);
char		*strdup_len_free(char **s, size_t size);
char		*ft_substr(char const *s, uint32_t start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*strjoin_parts(char const *s1, char const *s2, size_t s2_len);
char		*strjoin_free_s1(char *s1, const char *s2);
char		*strjoin_free_s2(const char *s1, char *s2);
char		*strjoin_free_all(char *s1, char *s2);
char		*strjoin_free_s1_n(char **s1, const char *s2);
char		*strjoin_free_s2_n(const char *s1, char **s2);
char		*strjoin_free_all_n(char **s1, char **s2);
char		*ft_strtrim(char const *s1, char const *set);

//	String Edit Functions
int			to_lower(int c);
int			to_upper(int c);
char		*str_decapitalize(char *str);
char		*str_capitalize(char *str);
size_t		cpy_str(char *dst, const char *src);
size_t		cpy_str0(char *dst, const char *src);
size_t		cpy_num_char(char *dst, const char c, size_t n);
size_t		cpy_num(char *dst, const char *src, size_t num);
size_t		cpy_srcs(char *dst, const char *s1, const char *s2, const char *s3);
size_t		cpy_till_char(char *dst, const char *src, const char chr);
size_t		cpy_num_s(char *dst, const char *src, size_t num);
size_t		cpy_srcs_s(char *dst, const char *s1, const char *s2, const char *s3);
size_t		cpy_str_s(char *dst, const char *src);
size_t		cpy_till_char_s(char *dst, const char *src, const char chr);
void		ft_striteri(char *s, void (*f)(uint32_t, char*));
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strncpy(char *dst, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		extract_substr(const char *s, uint32_t start, size_t ln, char *buf);
char		*ft_strmapi(char const *s, char (*f)(uint32_t, char));
void		swap_ptr(void **s1, void **s2);
uint8_t		nbr_to_buff(char *dst, int64_t n);
size_t		int64_base(int64_t n, const char *base, char *buff, size_t b_len);

//	String Manipulation Functions
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlen(const char *str);
size_t		strlen_safe(const char *str);
size_t		strlen_chr(const char *str, const char chr);
size_t		strlen_set(const char *str, const char *set);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			strncmp_safe(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
size_t		find_set_not(const char *str, const char *set);
size_t		find_char_not(const char *str, char s1);
size_t		find_char2_not(const char *str, char s1, char s2);
size_t		find_char3_not(const char *str, char s1, char s2, char s3);
size_t		find_set(const char *str, const char *set);
size_t		find_char(const char *str, char c1);
size_t		find_char2(const char *str, char c1, char c2);
size_t		find_char3(const char *str, char c1, char c2, char c3);
char		*smallest_str(char *s1, char *s2);
char		*biggest_str(char *s1, char *s2);
size_t		smallest_str_len(const char *s1, const char *s2);
size_t		biggest_str_len(const char *s1, const char *s2);
size_t		skip_alpha(const char *str);
size_t		skip_digits(const char *str);
size_t		skip_signed_digits(const char *str);
size_t		skip_spaces(const char *str);
bool		strs_ok(const char *s1, const char *s2);
bool		dpstr_ok(char **s1);
bool		dpstrs_ok(char **s1, char **s2);

bool		str0_ok(const char *s1);
bool		strs0_ok(const char *s1, const char *s2);
bool		dpstr0_ok(const char **s1);
bool		dpstrs0_ok(const char **s1, const char **s2);
bool		dp_ptr_ok(void **p1);
bool		c_in_str(int32_t c, const char *str);
bool		strcmp0(const char *str, const char *set_order);
size_t		strlmatch(const char *s1, const char *s2);
#endif
