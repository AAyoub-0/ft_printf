/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:22 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/18 18:17:28 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	num_len_base(long long num, int base_len)
{
	size_t	size;

	size = 0;
	if (num < 0)
	{
		size++;
		num = -num;
	}
	while (num > 0)
	{
		num = num / base_len;
		size++;
	}
	return (size);
}

int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == ' '
		|| c == '+');
}

void	trait_flags(const char **str, t_flags *flags)
{
	set_flags(flags);
	while (is_flag(*(*str)))
	{
		if (*(*str) == '-')
			flags->minus = 1;
		if (*(*str) == '0')
			flags->zero = 1;
		if (*(*str) == '.')
			flags->precision = get_number(str);
		if (*(*str) == '#')
			flags->hash = 1;
		if (*(*str) == ' ')
			flags->space = 1;
		if (*(*str) == '+')
			flags->plus = 1;
		(*str)++;
	}
	if (ft_isdigit(*(*str)))
		flags->padding = get_number(str);
	if (*(*str) == '.')
	{
		(*str)++;
		flags->precision = get_number(str);
	}
	flags->specifier = *(*str);
}

int	print_flags(t_flags flags, va_list args)
{
	if (flags.specifier == '%')
		return (print_nchar('%', 1));
	if (flags.specifier == 'c')
		return (print_nchar((char)va_arg(args, int), 1));
	if (flags.specifier == 's')
		return (print_flags_str(flags, args));
	if (flags.specifier == 'd' || flags.specifier == 'i')
		return (print_flags_snbase(flags, va_arg(args, int), "0123456789"));
	if (flags.specifier == 'u')
		return (print_flags_unbase(flags, va_arg(args, unsigned int),
				"0123456789"));
	if (flags.specifier == 'x')
		return (print_flags_unbase(flags, va_arg(args, unsigned int),
				"0123456789abcdef"));
	if (flags.specifier == 'X')
		return (print_flags_unbase(flags, va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	if (flags.specifier == 'p')
		return (print_flags_unbase(flags, (unsigned long)va_arg(args, void *),
				"0123456789abcdef"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		printed;

        if (!format)
                return (-1);
	va_start(args, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			trait_flags(&format, &flags);
			printed += print_flags(flags, args);
		}
		else
			printed += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (printed);
}
