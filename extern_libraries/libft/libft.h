/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:51:32 by rjw               #+#    #+#             */
/*   Updated: 2024/09/24 15:42:54 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

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

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

//	gnl(get_next_line) & ft_printf
# define MAX_FDS 1024
# define SPECIFIER "csdiupxX%"

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

# include <unistd.h>			//	write
# include <stdlib.h>			//	malloc
# include <stdarg.h>			//	ft_printf
# include <limits.h>			//	INT_MAX PATH_MAX, LLONG_MAX
# if defined(__linux__)
#  include <linux/limits.h>
# endif

# include <stdbool.h>
# include <stdint.h>			//	int32, uint32
# include <errno.h>
# include <stdio.h>				//	perror

//	Shorten normal datatype
typedef long long			t_ll;
//	Shorten unsigned datatypes
typedef unsigned char		t_uchar;
typedef unsigned long		t_ul;
typedef unsigned long long	t_ull;
//	Shorten const datatypes
typedef const bool			t_cbool;
typedef const char			t_cchr;
typedef const t_uchar		t_cuchr;
typedef const short			t_cshrt;
typedef const int8_t		t_cint8;
typedef const int16_t		t_cint16;
typedef const int32_t		t_cint32;
typedef const int64_t		t_cint64;
typedef const uint8_t		t_cuint8;
typedef const uint16_t		t_cuint16;
typedef const uint32_t		t_cuint32;
typedef const uint64_t		t_cuint64;
typedef const size_t		t_csize_t;
typedef const ssize_t		t_cssize_t;
typedef const long			t_cl;
typedef const t_ll			t_cll;
typedef const t_ul			t_cul;
typedef const t_ull			t_cull;
//	libft, linked lists
typedef struct s_list		t_lst;
//	ft_printf
typedef struct s_print		t_p;
typedef struct s_flags		t_fl;
//	Jumptables for ft_printf

struct s_list
{
	void			*content;
	struct s_list	*next;
};

struct s_print
{
	t_cchr	*fmt;
	short	spec;
	va_list	va;
	int		mal;
	char	*str;
	int		i;
	int		k;
	bool	count_or_str;
};

struct s_flags
{
	char	sp;
	bool	space;
	bool	plus;
	bool	dash;
	bool	zero;
	bool	hash;
	short	hsh;
	int		width;
	bool	dot;
	int		prec;
	int		f_len;
	int		ap_len;
	bool	minus;
	char	sign;
	long	nbr;
	char	*base;
	short	b_num;
	char	prefix[3];
	bool	stop;
	va_list	count;
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
char		**add_str_arr(char **arr, char *str);
char		**search_rm_2d_arr(char **arr, char *rm);
char		**find_rm_2d_arr(char ***arr, char *rm);
char		**find_rm_all_2d_arr(char ***arr, char *rm);
void		free_2d_arr(char ***arr);
void		print_2d_array(char **arr);
char		**splitted(char const *s, char c);
char		**split(char const *s, char c);
char		**split_set(char const *s, char *set);

//	ASCII Functions
int			ft_isspace(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

//	Conversions Functions
int			ft_atoi(t_cchr *nptr);
int			atoi_safe(t_cchr *nptr);
t_ll		ft_atoll(t_cchr *nptr);
t_ll		atoll_safe(t_cchr *nptr);

uint32_t	ato_ui(t_cchr *nptr);
uint32_t	ato_ui_safe(t_cchr *nptr);
t_ull		ato_ull(t_cchr *nptr);
t_ull		ato_ull_safe(t_cchr *nptr);

//	Get_Next_line
char		*gnl(int fd);
char		*gnl_fds(int fd);

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
size_t		find_min(size_t	n1, size_t n2);
size_t		find_max(size_t	n1, size_t n2);
short		sign(int n);
short		sign_d(double n);
uint16_t	digit_counter(t_ll n);

//	Memory Edits Functions
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

//	Memory Search Functions
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

//	Printf
int			ft_printf_fd(int fd, t_cchr *format, ...);
int			ft_printf(t_cchr *fmt, ...);
int			ft_format(t_p *p);

int			parse_format(t_p *c, t_fl *f, int i);
int			flag_check(t_p *c, t_fl *f);

int			spec_count_one(t_p *c, t_fl *f);
int			spec_count_two(t_p *c, t_fl *f);
void		spec_str_one(t_p *p, t_fl *f);
void		spec_str_two(t_p *p, t_fl *f);

int			unsigned_count(t_fl *f, t_ul n);
int			signed_count(int n);
int			signed_decimal_base(char *str, int n);
int			ft_ultoa_base(t_fl *f, t_ul n, char *str);

void		chr_bonus_count(t_p *c, t_fl *f);
void		chr_bonus_write(t_p *p, t_fl *f);
void		str_bonus_count(t_p *c, t_fl *f);
void		str_bonus_write(t_p *p, t_fl *f);
void		int_bonus_count(t_p *c, t_fl *f);
void		int_bonus_write(t_p *p, t_fl *f);
void		nbr_bonus_write(t_p *p, t_fl *f);
void		nbr_bonus_count(t_p *c, t_fl *f);

int			move_str(char *dst, t_cchr *src);
int			move_num_src(char *dst, t_cchr *src, int num);
int			move_num_chr(char *str, t_cchr c, int n);

//	Putchars Functions
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

//	String Create Functions
char		*ft_itoa(int n);
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
size_t		cpy_str(char *dst, t_cchr *src);
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
size_t		ft_strlcpy(char *dst, t_cchr *src, size_t size);
char		*charmove(char *dest, const char *src, size_t n);
char		*ft_strmapi(char const *s, char (*f)(uint32_t, char));
void		swap_str_values(void **s1, void **s2);
void		itoa_buff(char *dst, int n);

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
bool		dpstr0_ok(char **s1);
bool		dpstrs0_ok(char **s1, char **s2);
bool		dp_ptr_ok(void **p1);
bool		c_in_str(t_cint8 c, t_cchr *str);
bool		strcmp0(t_cchr *str, t_cchr *set_order);
size_t		strlmatch(t_cchr *s1, t_cchr *s2);
#endif
