/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:22 by aboumall          #+#    #+#             */
/*   Updated: 2024/11/28 17:51:58 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == ' '
		|| c == '+');
}

int	valid_flags(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
	{
		if (str[i] == str[i + 1])
			return (0);
	}
	return (1);
}

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

int	get_number(char **str)
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

void	trait_flags(const char **str, va_list args, t_flags *flags)
{
	set_flags(flags);
	(*str)++;
	while (is_flag(*(*str)))
	{
		if (*(*str) == '-')
			flags->minus = 1;
		if (*(*str) == '0')
			flags->zero = 1;
		if (*(*str) == '.')
			flags->precision = 1;
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
	if (*(*str) == '.' && flags->precision == -1)
	{
		(*str)++;
		flags->precision = get_number(str);
	}
	flags->specifier = *(*str);
}

int     print_nchar(char c, size_t n)
{
        int     printed;

        printed = 0;
        while (n > 0)
        {
                printed += write(1, &c, 1);
                n--;       
        }
        return (printed);          
}

int     print_flags_str(t_flags flags, va_list args)
{
        const char      *str;
        int     printed;
        int     len;

        printed = 0;
        // str = va_arg(args, char *);
        str = "Hello World!";
        if (!str)
                return (0);
        len = ft_strlen(str);
        if (flags.precision >= 0)
                len = flags.precision;
        if (flags.padding > len)
        {
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
        printed += write(1, str, len);
        return (printed);
}

int     print_nbase(int num, char *base, t_flags flags)
{
        int     base_len;
        int     printed;

        base_len = ft_strlen(base);
        printed = 0;
        if (num < 0)
        {
                if (!flags.zero || flags.minus)
                        printed += print_nchar('-', 1);
		num = -num;
        }
        if (num >= base_len)
                printed += print_nbase(num / base_len, base, flags);
        printed += write(1, &base[num % base_len], 1);
        return (printed);
}

size_t  num_len_base(int num, int base_len)
{
        size_t  size;

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

int     print_flags_nbase(t_flags flags, va_list args, char *base)
{
        int     printed;
        int     len;
        int     num;

        printed = 0;
        // num = va_arg(args, int);
        num = 255;
        len = num_len_base(num, ft_strlen(base));
        if (flags.space && !(flags.padding > len))
                printed += print_nchar(' ', 1);
        if (flags.hash && (flags.specifier == 'x' || flags.specifier == 'X'))
                len += 2;
        if (flags.padding > len)
        {
                if (flags.minus)
                {
                        printed += print_nbase(num, base, flags);
                        printed += print_nchar(' ', flags.padding - len);
                        return (printed);
                }
                if (flags.zero)
                {
                        if (num < 0)
                                printed += print_nchar('-', 1);
                        printed += print_nchar('0', flags.padding - len);
                }
                else
                        printed += print_nchar(' ', flags.padding - len);
                printed += print_nbase(num, base, flags);
                return (printed);
        }
        printf("NUM [%d], BASE [%s]\n", num, base);
        printed += print_nbase(num, base, flags);
        return (printed);
}

int     print_flags(t_flags flags, va_list args)
{
        if (flags.specifier == 's')
                return (print_flags_str(flags, args));
        if (flags.specifier == 'd' || flags.specifier == 'i')
                return (print_flags_nbase(flags, args, "0123456789"));
        if (flags.specifier == 'x')
                return (print_flags_nbase(flags, args, "0123456789abcdef"));
        if (flags.specifier == 'X')
                return (print_flags_nbase(flags, args, "0123456789ABCDEF"));
}

int main() {
        // const char *format = "%X";
        // va_list args;

        // printf("Format à analyser : \"%s\"\n", format);

        // t_flags flags;
        
        // trait_flags(&format, args, &flags);
        // print_flags(flags, args);
        // printf("\n");

        // printf("Résultat de l'analyse des flags :\n");
        // printf("  minus      = %d\n", flags.minus);
        // printf("  zero       = %d\n", flags.zero);
        // printf("  precision  = %d\n", flags.precision);
        // printf("  hash       = %d\n", flags.hash);
        // printf("  space      = %d\n", flags.space);
        // printf("  plus       = %d\n", flags.plus);
        // printf("  padding      = %d\n", flags.padding);
        // printf("  specifier  = '%c'\n", flags.specifier);

        // printf("%10.3s<\n", "hello");
        // printf("% 010d<\n", 85);
        printf("%#x<\n", 255);

        // print_nbase(19558, "0123456789");

    return 0;
}