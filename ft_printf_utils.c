/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:24:44 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/11 13:46:46 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nchar(char c, int n)
{
	int	printed;

	if (n < 0)
		return (0);
	printed = 0;
	while (printed < n)
		printed += write(1, &c, 1);
	return (printed);
}

int	print_nbase(unsigned long num, char *base, t_flags flags)
{
	unsigned long	base_len;
	int				printed;

	base_len = ft_strlen(base);
	printed = 0;
	if (num >= base_len)
		printed += print_nbase(num / base_len, base, flags);
	printed += write(1, &base[num % base_len], 1);
	return (printed);
}

int	print_flags_str(t_flags flags, va_list args)
{
	char	*str;
	int		printed;
	int		len;

	printed = 0;
	str = va_arg(args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	len = ft_strlen(str);
	if (flags.precision >= 0)
		len = flags.precision;
	if (flags.padding > len)
		write_padding_str(flags, str, len);
	else
		printed += write(1, str, len);
	return (printed);
}

int	print_flags_unbase(t_flags flags, unsigned long num, char *base)
{
	int		printed;
	int		len;
	t_num	tnum;

	printed = 0;
	tnum.num = num;
	tnum.is_negative = 0;
	len = num_len_base(num, ft_strlen(base));
	if (flags.specifier == 'p' && num == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	if (flags.padding > len || flags.precision)
		printed += write_padding_num(flags, tnum, base, len);
	else
		printed += print_nbase(num, base, flags);
	return (printed);
}

int	print_flags_snbase(t_flags flags, long num, char *base)
{
	int		printed;
	int		len;
	t_num	tnum;

	printed = 0;
	tnum.is_negative = 0;
	len = num_len_base(num, ft_strlen(base));
	if ((flags.space && (!(flags.padding > len) || (flags.minus
					&& flags.padding > len))))
		printed += print_nchar(' ', 1);
	if (num < 0)
	{
		num = -num;
		tnum.is_negative = 1;
	}
	tnum.num = num;
	if (flags.padding > len || flags.precision)
		printed += write_padding_num(flags, tnum, base, len);
	else
		printed += print_nbase(num, base, flags);
	return (printed);
}
