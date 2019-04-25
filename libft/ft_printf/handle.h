/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 00:46:08 by onahiz            #+#    #+#             */
/*   Updated: 2019/04/25 00:50:29 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_H
# define HANDLE_H

# include <stdarg.h>
# include <locale.h>
# include "lib.h"

typedef	struct		s_param
{
	int				width;
	int				precision;
	unsigned int	err:1;
	unsigned int	null:1;
	unsigned int	minus:1;
	unsigned int	plus:1;
	unsigned int	space:1;
	unsigned int	hash:1;
	unsigned int	zero:1;
	unsigned int	ll:1;
	unsigned int	hh:1;
	unsigned int	l:1;
	unsigned int	h:1;
	unsigned int	j:1;
	unsigned int	z:1;
	char			f;
}					t_param;

typedef struct		s_buff
{
	char			*buff;
	int				i;
	int				ret;
}					t_buff;

int					is_fspec(char f);
int					is_flag(char f);
int					count_ac(char *f);
int					get_next_spec(char *f);
int					direct_print(char *f, int *i);
int					ft_putbuff(t_buff *b, int ret);
int					is_negative(t_param *arg, char **s, int *len);
int					buff_cpy(char *f, int pos, va_list ap, t_buff *b);
int					handler(char *f, va_list ap, char *cut, t_buff *b);
char				*convert_arg(char *f, va_list ap, t_param *arg, char *base);
char				*convert_b(char *f, t_param *arg, va_list ap, char *base);
char				*trim_arg2(t_param *arg, char *s, char c, int len);
char				*handle_plus_space(t_param *arg, char *s, int len);
char				*handle_precision(t_param *arg, char *s, int len);
char				*convert_uint(char *f, t_param *arg, va_list ap);
char				*convert_int(char *f, t_param *arg, va_list ap);
char				*handle_width(t_param *arg, char *s, int len);
char				*handle_hash(t_param *arg, char *s, int len);
char				*trim_arg(char *s, t_param *arg, int len);
char				*new_fspec(t_param *arg, char f);
char				get_sign(t_param *arg);
char				get_fill(t_param *arg);
char				*skip_flags(char *f);
char				*get_prefix(char c);
char				*get_base(char c);
char				*get_base(char f);
void				init_arg(t_param *arg);
void				buff_init(char *f, int pos, t_buff *b);
void				copy_arg_str(char *s, char *dst, int *i);
void				parse_flags(char *f, t_param *arg, va_list ap);

#endif
