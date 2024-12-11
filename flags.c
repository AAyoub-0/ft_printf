/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:22:42 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/11 13:46:54 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->precision = -1;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->padding = 0;
	flags->specifier = 0;
}

int	get_number(const char **str)
{
	int	result;

	result = 0;
	while (*(*str) && ft_isdigit(*(*str)))
	{
		result = result * 10 + (*(*str) - '0');
		(*str)++;
	}
	return (result);
}

int	write_padding_str(t_flags flags, char *str, int len)
{
	int	printed;

	printed = 0;
	if (flags.minus)
	{
		printed += write(1, str, len);
		printed += print_nchar(' ', flags.padding - len);
		return (printed);
	}
	printed += print_nchar(' ', flags.padding - len);
	printed += write(1, str, len);
	return (printed);
}

int	trait_padding_precision(t_flags flags, int len, int is_negative,
		int hash_padding)
{
	int	printed;

	printed = 0;
	if (flags.padding && !flags.precision && !flags.zero)
		printed += print_nchar(' ', flags.padding - len);
	if (flags.padding && flags.precision && flags.padding > flags.precision
		&& flags.padding > len)
		printed += print_nchar(' ', flags.padding - flags.precision
				- hash_padding - is_negative);
	if (flags.hash && (flags.specifier == 'x' || flags.specifier == 'X'))
		len += 2;
	if ((flags.hash && (flags.specifier == 'x')) || flags.specifier == 'p')
		printed += write(1, "0x", 2);
	if (flags.hash && (flags.specifier == 'X'))
		printed += write(1, "0X", 2);
	if (is_negative)
		printed += print_nchar('-', 1);
	if (flags.zero && flags.padding && !flags.precision)
		printed += print_nchar('0', flags.padding - len);
	if (flags.precision)
		printed += print_nchar('0', flags.precision - len + hash_padding
				+ is_negative);
	return (printed);
}

int	write_padding_num(t_flags flags, t_num tnum, char *base, int len)
{
	int		printed;
	int		hash_padding;
	size_t	padding_len;

	printed = 0;
	hash_padding = 0;
	if (flags.hash)
		hash_padding = 2;
	if (flags.zero && flags.precision)
		padding_len = flags.padding - len - flags.precision;
	else
		padding_len = flags.padding - len;
	if (flags.minus)
	{
		printed += print_nbase(tnum.num, base, flags);
		printed += print_nchar(' ', padding_len);
		return (printed);
	}
	printed += trait_padding_precision(flags, len, tnum.is_negative,
			hash_padding);
	printed += print_nbase(tnum.num, base, flags);
	return (printed);
}
