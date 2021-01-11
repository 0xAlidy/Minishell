/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:54:32 by alidy             #+#    #+#             */
/*   Updated: 2021/01/06 14:46:11 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 30
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct		s_gnl
{
	int				fd;
	char			*content;
	struct s_gnl	*next;

}					t_gnl;
typedef struct		s_flags
{
	int				zero;
	int				point;
	int				neg;
	int				width;
	int				precision;
	char			c;
}					t_flags;
t_gnl				*ft_lstnew(int fd, t_gnl **liste);
t_gnl				*recup_maillon(int fd, t_gnl **liste);
int					rm_lst(int fd, t_gnl **lst);
char				*ft_remove(char *current);
int					get_next_line(int fd, char **line);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_itoa(int n);
int					ft_intlen(int nb);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strjoin_free(char *s1, char *s2, int free);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *dest, const char *src, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_write_flags(int zero, int c, int flag, int nb);
void				ft_write_justify_flags
(int zero, char *numb, int size, int nb);
char				*ft_fstrjoin(char *s1, char *s2);
unsigned int		ft_longlen(unsigned int nb);
char				*ft_get_str_format
(const char *s, int *i, va_list list, t_flags *tab);
void				ft_parsing_flags(t_flags *tab, char *str);
t_flags				ft_init_struct(void);
int					ft_int_format(t_flags tab, int nb);
int					ft_char_format(t_flags tab, char c);
int					ft_str_format(t_flags tab, char *str);
int					ft_printf
(const char *format, ...) __attribute__((format(printf,1,2)));
char				*ft_itoa_base(int nb, char *base);
char				*ft_ullitoa_base(unsigned long long nb, char *base);
void				ft_strtoupper(char **str);
void				ft_write_space(int c);
int					ft_hexa_format(t_flags tab, char *nb);
int					ft_un_format(t_flags tab, unsigned int nb);

#endif
