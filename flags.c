/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:22:42 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/04 13:48:53 by aboumall         ###   ########.fr       */
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

int     write_padding_str(t_flags flags, char *str, int len)
{
        int     printed;

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

int     need_write_space(t_flags flags, int len)
{
        return (flags.space && (!(flags.padding > len) || (flags.minus && flags.padding > len)));
}

int    write_padding_num(t_flags flags, unsigned long num, char *base, int len)
{
        int     printed;
        size_t  padding_len;
        
        printed = 0;
        if (flags.precision != 'i' || flags.precision != 'd')
                padding_len = flags.padding - len - need_write_space(flags, len);
        else
                padding_len = flags.padding - len;
        if (flags.minus)
        {
                printed += print_nbase(num, base, flags);
                printed += print_nchar(' ', padding_len);
                return (printed);
        }
        if (flags.zero)
                printed += print_nchar('0', flags.padding - len);
        else
                printed += print_nchar(' ', flags.padding - len);
        printed += print_nbase(num, base, flags);
        return (printed);
}