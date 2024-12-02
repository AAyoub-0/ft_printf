/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:22 by aboumall          #+#    #+#             */
/*   Updated: 2024/12/02 15:13:02 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '.' || c == '#' || c == ' '
		|| c == '+');
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

void	trait_flags(const char **str, t_flags *flags)
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

int     print_nchar(char c, int n)
{
        int     printed;

        if (n < 0)
                return (0);
        printed = 0;
        while (printed < n)
                printed += write(1, &c, 1);   
        return (printed);          
}

int     print_flags_str(t_flags flags, va_list args)
{
        const char      *str;
        int     printed;
        int     len;

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

int     print_nbase(unsigned long num, char *base, t_flags flags)
{
        unsigned long     base_len;
        int     printed;
        
        base_len = ft_strlen(base);
        printed = 0;
        if (num >= base_len)
                printed += print_nbase(num / base_len, base, flags);
        printed += write(1, &base[num % base_len], 1);
        return (printed);
}

size_t  num_len_base(long long num, int base_len)
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

int     print_flags_unbase(t_flags flags, unsigned long num, char *base)
{
        int     printed;
        int     len;

        printed = 0;
        len = num_len_base(num, ft_strlen(base));
        if (flags.specifier == 'p' && num == 0)
        {
                ft_putstr_fd("(nil)", 1);
                return (5);               
        }
        if (flags.hash && (flags.specifier == 'x' || flags.specifier == 'X'))
                len += 2;
        if ((flags.hash && (flags.specifier == 'x')) || flags.specifier == 'p')
                printed += write(1, "0x", 2);
        else if (flags.hash && (flags.specifier == 'X'))
                printed += write(1, "0X", 2);
        if (flags.padding > len)
        {
                if (flags.minus)
                {
                        printed += print_nbase(num, base, flags);
                        printed += print_nchar(' ', flags.padding - len);
                        return (printed);
                }
                if (flags.zero)
                        printed += print_nchar('0', flags.padding - len);
                else
                        printed += print_nchar(' ', flags.padding - len);
                printed += print_nbase(num, base, flags);
                return (printed);
        }
        printed += print_nbase(num, base, flags);
        return (printed);
}

int     need_write_space(t_flags flags, int len)
{
        return (flags.space && (!(flags.padding > len) || (flags.minus && flags.padding > len)));
}

int     print_flags_snbase(t_flags flags, long num, char *base)
{
        int     printed;
        int     len;

        printed = 0;
        len = num_len_base(num, ft_strlen(base));
        if (need_write_space(flags, len))
                printed += print_nchar(' ', 1);
        if (!flags.zero && num < 0)
        {
                printed += print_nchar('-', 1);
                num = -num;
        }
        if (flags.padding > len)
        {
                if (flags.minus)
                {
                        printed += print_nbase((unsigned long)num, base, flags);
                        printed += print_nchar(' ', flags.padding - len - need_write_space(flags, len));
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
                printed += print_nbase((unsigned long)num, base, flags);
                return (printed);
        }
        printed += print_nbase((unsigned long)num, base, flags);
        return (printed);
}

int     print_flags(t_flags flags, va_list args)
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
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789"));
        if (flags.specifier == 'x')
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789abcdef"));
        if (flags.specifier == 'X')
                return (print_flags_unbase(flags, va_arg(args, unsigned int), "0123456789ABCDEF"));
        if (flags.specifier == 'p')
                return (print_flags_unbase(flags, (unsigned long)va_arg(args, void *), "0123456789abcdef"));
        return (0);
}

int     ft_printf(const char *format, ...)
{
        va_list args;
        t_flags flags;
        int     printed;

        va_start(args, format);
        printed = 0;
        while (*format)
        {
                if (*format == '%')
                {
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

// int main()
// {
//         int     ft_result;
//         int     result;
//         // char    world[] = "World"; 
//         // char    w = 'w';
//         // int     psn = 255;
//         // int     nsn = -255;
//         // unsigned int    pun = -255;
//         // unsigned int    sun = INT_MAX;

//         // puts("--------- Char test ----------\n");
//         // result = printf("Hello %corld\n", w);
//         // ft_result = ft_printf("Hello %corld\n", w);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- String test ----------\n");
//         // result = printf("Hello %s\n", world);
//         // ft_result = ft_printf("Hello %s\n", world);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Int test ----------\n");
//         // result = printf("Hello %d\n", INT_MIN);
//         // ft_result = ft_printf("Hello %d\n", INT_MIN);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %d\n", nsn);
//         // ft_result = ft_printf("Hello %d\n", nsn);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %u\n", pun);
//         // ft_result = ft_printf("Hello %u\n", pun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Unsigned Int test ----------\n");
//         // result = printf("Hello %u\n", sun);
//         // ft_result = ft_printf("Hello %u\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Hex test ----------\n");
//         // result = printf("Hello %x\n", sun);
//         // ft_result = ft_printf("Hello %x\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Pointers test ----------\n");
//         // result = printf("Hello %p<end\n", &sun);
//         // ft_result = ft_printf("Hello %p<end\n", &sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Pointers test ----------\n");
//         // result = printf("Hello %p<end\n", (void *)LONG_MAX);
//         // ft_result = ft_printf("Hello %p<end\n", LONG_MAX);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %10.5d<end\n", sun);
//         // ft_result = ft_printf("Hello %10.5d<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-10.5d<end\n", sun);
//         // ft_result = ft_printf("Hello %-10.5d<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %10.5u<end\n", sun);
//         // ft_result = ft_printf("Hello %10.5u<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-10.5u<end\n", sun);
//         // ft_result = ft_printf("Hello %-10.5u<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with multiple flags ----------\n");
//         // result = printf("Hello %-#50.5x<end\n", sun);
//         // ft_result = ft_printf("Hello %-#50.5x<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         // puts("--------- Test with invalid specifier ----------\n");
//         // result = printf("Hello %50-.5i<end\n", sun);
//         // ft_result = ft_printf("Hello %50-.5i<end\n", sun);
//         // printf("Result: %d\n", result);
//         // printf("Ft_Result: %d\n", ft_result);
//         // puts("------------------------------\n");

//         return (0);
// }