/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:24:25 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/11 13:46:59 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_flags
{
	int				minus;
	int				plus;
	int				zero;
	int				space;
	int				hash;
	int				padding;
	int				precision;
	char			specifier;
}					t_flags;

typedef struct s_num
{
	unsigned long	num;
	int				is_negative;
}					t_num;

int					print_nchar(char c, int n);
size_t				num_len_base(long long num, int base_len);
void				set_flags(t_flags *flags);
int					get_number(const char **str);
int					write_padding_num(t_flags flags, t_num num, char *base,
						int len);
int					write_padding_str(t_flags flags, char *str, int len);
int					print_flags_unbase(t_flags flags, unsigned long num,
						char *base);
int					print_nbase(unsigned long num, char *base, t_flags flags);
int					print_flags_snbase(t_flags flags, long num, char *base);
int					print_flags_str(t_flags flags, va_list args);
int					ft_printf(const char *format, ...);

#endif