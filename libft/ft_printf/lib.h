/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onahiz <onahiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 23:45:06 by onahiz            #+#    #+#             */
/*   Updated: 2018/11/26 21:42:51 by onahiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "../libft.h"

char		*ft_unitoa(wchar_t c, char *s);
char		*ft_unistrtoa(wchar_t *c, int max);
char		*ft_ltoa(long int n);
char		*ft_jtoa(intmax_t n);
char		*ft_htoa(short n);
char		*ft_ftoa(double f, int p);
char		*ft_ftoea(double f, int p, char c);
char		*ft_lltoa(long long int n);
char		*ft_hhtoa(signed char n);
char		*ft_utoa(unsigned int n);
char		*ft_ultoa(unsigned long int n);
char		*ft_ujtoa(uintmax_t n);
char		*ft_ztoa(size_t n);
char		*ft_uhtoa(unsigned short n);
char		*ft_ulltoa(unsigned long long int n);
char		*ft_convert_base(unsigned long long nbr, char *base_to);

#endif
