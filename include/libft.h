/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-brui <rde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/09 20:31:53 by rde-brui      #+#    #+#                 */
/*   Updated: 2025/04/13 15:47:32 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#define GNL get_next_line
/*
	BUFFER_SIZE minimum is 1, don't go lower than that.
	cc -D BUFFER_SIZE=42 <files>.c
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10240
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

//	error handling
# define CALLOC_ERR "ENOMEM, Cannot allocate memory ft_calloc()"
# define GNL_ERR "ENOMEM, Cannot allocate memory get_next_line()"
# define ITOA_ERR "ENOMEM, Cannot allocate memory ft_itoa()"
# define LSTNEW_ERR "ENOMEM, Cannot allocate memory ft_lstnew()"
# define SPLIT_ERR "ENOMEM, Cannot allocate memory split()"
# define SPLIT_SET_ERR "ENOMEM, Cannot allocate memory split_set()"
# define STRDUP_ERR "ENOMEM, Cannot allocate memory ft_strdup()"
# define STRMAPI_ERR "ENOMEM, Cannot allocate memory ft_strmapi()"
# define STRTRIM_ERR "ENOMEM, Cannot allocate memory ft_strtrim()"
# define STRJOIN_ERR "ENOMEM, Cannot allocate memory strjoin()"
# define JOIN_FREE_S1_ERR "ENOMEM, Cannot allocate memory strjoin_free_s1()"
# define JOIN_FREE_S1_NERR "ENOMEM, Cannot allocate memory strjoin_free_s1_n()"
# define JOIN_FREE_S2_ERR "ENOMEM, Cannot allocate memory strjoin_free_s2()"
# define JOIN_FREE_S2_NERR "ENOMEM, Cannot allocate memory strjoin_free_s2_n()"
# define JOIN_FREE_ALL_ERR "ENOMEM, Cannot allocate memory strjoin_free_all()"
# define JOIN_FRE_ALL_NERR "ENOMEM, Cannot allocate memory strjoin_free_all_n()"
# define SUBSTR_ERR "ENOMEM, Cannot allocate memory ft_substr()"

# include <common_defs.h>
# include <is_ctype1.h>
# include <is_ctype2.h>
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
void		*ft_realloc(void **ptr, t_csize_t new_size, t_csize_t old_size);
void		*ft_calloc(size_t nmemb, size_t size);

//	Nested Arrays Functions
size_t		count_arr_2d(char **arr);
char		**cpy_2d_array(char **arr);
char		**expand_2d_array(char ***arr, size_t add_rows);
char		**add_str_arr(char **arr, char *str);
char		**search_rm_2d_arr(char **arr, char *rm);
char		**find_rm_2d_arr(char ***arr, char *rm);
char		**find_rm_all_2d_arr(char ***arr, char *rm);
void		free_2d_arr(char ***arr);
void		print_2d_array(char **arr);
char		**splitted(char const *s, char c);
char		**split(char const *s, char c);
char		**split_set(char const *s, char *set);

//	Conversions Functions
int32_t		atoi32(t_cchr *nptr);
int64_t		atoi64(t_cchr *nptr);
int64_t		atoi_base(const char *nbr_str, char *base, bool *is_neg);
uint64_t	atui64(t_cchr *nptr);

//	Get_Next_line
char		*get_next_line(int fd);
char		*get_next_line_fds(int fd);
ssize_t		get_user_input(char *buff, ssize_t buff_size, char *msg, bool mute);

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
int8_t		sign(int n);
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
void		ft_putendl_fd(t_cchr *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putnbr_nl_fd(int n, int fd);
void		ft_putstr_fd(t_cchr *s, int fd);

//	String Create Functions
char		*ft_itoa(int n);
char		*nbr_to_str(int64_t n);
char		*itoa_base(int64_t n, const char *base);
char		*int_to_str(char *dst, uint8_t len, int64_t n, const char *base);

char		*ft_strdup(t_cchr *s);
char		*strdup_safe(t_cchr *s);
char		*strdup_len(t_cchr *s, size_t size);
char		*strdup_len_free(char **s, size_t size);
char		*ft_substr(char const *s, uint32_t start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*strjoin_parts(char const *s1, char const *s2, size_t s2_len);
char		*strjoin_free_s1(char *s1, t_cchr *s2);
char		*strjoin_free_s2(t_cchr *s1, char *s2);
char		*strjoin_free_all(char *s1, char *s2);
char		*strjoin_free_s1_n(char **s1, t_cchr *s2);
char		*strjoin_free_s2_n(t_cchr *s1, char **s2);
char		*strjoin_free_all_n(char **s1, char **s2);
char		*ft_strtrim(char const *s1, char const *set);

//	String Edit Functions
int			to_lower(int c);
int			to_upper(int c);
char		*str_decapitalize(char *str);
char		*str_capitalize(char *str);
size_t		cpy_str(char *dst, t_cchr *src);
size_t		cpy_str0(char *dst, t_cchr *src);
size_t		cpy_num_char(char *dst, t_cchr c, size_t n);
size_t		cpy_num(char *dst, t_cchr *src, size_t num);
size_t		cpy_srcs(char *dst, t_cchr *s1, t_cchr *s2, t_cchr *s3);
size_t		cpy_till_char(char *dst, t_cchr *src, t_cchr chr);
size_t		cpy_num_s(char *dst, t_cchr *src, size_t num);
size_t		cpy_srcs_s(char *dst, t_cchr *s1, t_cchr *s2, t_cchr *s3);
size_t		cpy_str_s(char *dst, t_cchr *src);
size_t		cpy_till_char_s(char *dst, t_cchr *src, t_cchr chr);
void		ft_striteri(char *s, void (*f)(uint32_t, char*));
size_t		ft_strlcat(char *dst, t_cchr *src, size_t size);
char		*ft_strncpy(char *dst, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, t_cchr *src, size_t size);
char		*charmove(char *dest, const char *src, size_t n);
void		extract_substr(const char *s, uint32_t start, size_t ln, char *buf);
char		*ft_strmapi(char const *s, char (*f)(uint32_t, char));
void		swap_ptr(void **s1, void **s2);
uint8_t		nbr_to_buff(char *dst, int64_t n);
size_t		int64_base(int64_t n, const char *base, char *buff, size_t b_len);

//	String Manipulation Functions
char		*ft_strchr(t_cchr *s, int c);
char		*ft_strrchr(t_cchr *s, int c);
size_t		ft_strlen(t_cchr *str);
size_t		strlen_safe(t_cchr *str);
size_t		strlen_chr(t_cchr *str, t_cchr chr);
size_t		strlen_set(t_cchr *str, t_cchr *set);
int			ft_strcmp(t_cchr *s1, t_cchr *s2);
int			ft_strncmp(t_cchr *s1, t_cchr *s2, size_t n);
int			strncmp_safe(t_cchr *s1, t_cchr *s2, size_t n);
char		*ft_strnstr(t_cchr *big, t_cchr *little, size_t len);
size_t		find_set_not(t_cchr *str, char *set);
size_t		find_char_not(t_cchr *str, t_cchr s1);
size_t		find_char2_not(t_cchr *str, t_cchr s1, t_cchr s2);
size_t		find_char3_not(t_cchr *str, t_cchr s1, t_cchr s2, t_cchr s3);
size_t		find_set(t_cchr *str, char *set);
size_t		find_char(t_cchr *str, t_cchr c1);
size_t		find_char2(t_cchr *str, t_cchr c1, t_cchr c2);
size_t		find_char3(t_cchr *str, t_cchr c1, t_cchr c2, t_cchr c3);
char		*smallest_str(char *s1, char *s2);
char		*biggest_str(char *s1, char *s2);
size_t		smallest_str_len(t_cchr *s1, t_cchr *s2);
size_t		biggest_str_len(t_cchr *s1, t_cchr *s2);
size_t		skip_alpha(t_cchr *str);
size_t		skip_digits(t_cchr *str);
size_t		skip_signed_digits(t_cchr *str);
size_t		skip_spaces(t_cchr *str);
bool		strs_ok(t_cchr *s1, t_cchr *s2);
bool		dpstr_ok(char **s1);
bool		dpstrs_ok(char **s1, char **s2);

bool		str0_ok(t_cchr *s1);
bool		strs0_ok(t_cchr *s1, t_cchr *s2);
bool		dpstr0_ok(t_cchr **s1);
bool		dpstrs0_ok(t_cchr **s1, t_cchr **s2);
bool		dp_ptr_ok(void **p1);
bool		c_in_str(int32_t c, t_cchr *str);
bool		strcmp0(t_cchr *str, t_cchr *set_order);
size_t		strlmatch(t_cchr *s1, t_cchr *s2);
#endif
